#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const TAM_MAX_INSTRUCAO = 30;
char memoria[100][30];

//********* VARIAVEIS DE CONTROLE ***********
int iniciouCarregamentoDasInstrucoes = 0;
int contadorDeInstrucoes = 0;

//********** REGISTRADORES ******************
int PC;

// *************** IMPRIMEM A SITUAÇÃO DA MEMÓRIA EM TELA ****************************
void mostraMemoria(){
    printf("\n\n>>>>>>>>>>>>MEMORIA<<<<<<<<<<<<!!!\n\n");
    int i;
    for(i = 0; i<100;i++)
        printf("%d>> %s\n", i, memoria[i]);
}

int hexaToInt(char* hexa){
    int retorno;
    sscanf(hexa, "%x", &retorno);
    return retorno;
}

void insereNaMemoria(int posicao, char* valor){
    if(posicao < 0 || posicao > 99)
        printf("Posição %d da mémoria não existe. Usando intervalo de 0 a 100!!!", posicao);

    strcpy(memoria[posicao], valor);
}


//**********************CARREGAMENTO DO ARQUIVO *********************************
void carregaLiteral(char linha[]){
    if(strcmp("\n", linha) == 0)
        return;

    char *token = strtok(linha," ,\t");
    char *valor = token;
    token = strtok(NULL," ,\t");

    int posicao = hexaToInt(token);

    strcpy(memoria[posicao], valor);
}

void inicializaContadorDeInstrucoes(char linha[]){
     contadorDeInstrucoes = hexaToInt(linha);
     PC = contadorDeInstrucoes;
     iniciouCarregamentoDasInstrucoes = 1;
}

void carregaInstrucoes(char linha[]){
    if(!iniciouCarregamentoDasInstrucoes)
        inicializaContadorDeInstrucoes(linha);
    else{
        insereNaMemoria(contadorDeInstrucoes, linha);
        contadorDeInstrucoes++;
    }
}

void carregaArquivo(){
	char url[]="programa.txt";
	char linha[TAM_MAX_INSTRUCAO];
	FILE *arq;
	int literaisCarregados = 0;

	arq = fopen(url, "r");
	if(arq == NULL)
	    printf("Erro, nao foi possivel abrir o arquivo\n");
	else
	    while((fgets(linha, TAM_MAX_INSTRUCAO, arq)) != NULL){

            if(strcmp("0x0A\n", linha) == 0)
                literaisCarregados = 1;

            if(literaisCarregados)
                carregaInstrucoes(linha);
            else
                carregaLiteral(linha);
	    }
	fclose(arq);
}

//************************** FIM CARREGAMENTO DO ARQUIVO*********************

int main() {
    mostraMemoria();
    carregaArquivo();
    mostraMemoria();
    printf("O Programa foi carregado e está pronto para ser executado.");

    return 0;
}

