#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const TAM_MAX_INSTRUCAO = 30;
char memoria[100][30];

//********* VARIAVEIS DE CONTROLE ***********
int iniciouCarregamentoDasInstrucoes = 0;
int contadorDeInstrucoes = 0;

char* instrucao;
int op1;


//********** REGISTRADORES ******************

int A; // Acumulador
int B; //: Uso geral
int M1; //: Multiplicador
int M2; //: Multiplicando
int D1; //: Divisor
int D2; //: Dividendo
int R; //: Resto da divisão
int C; //: Carry out (1: houve carry – 2: não houve carry)
int Z; //: Resultado zero(-1: resultado negativo; 0: resultado igual a zero; 1: resultado positivo)
int PC; //: Program Counter
char* IR; //: Instruction Register
int MAR; //: Memory Address Register
char* MBR; //: Memory Buffer Register

struct Registrador {
    char* nome;
    char* valor;
} ;

struct Registrador registradores[13];


void criaRegistradores(){
    registradores[0].nome = "A";
    registradores[1].nome = "B";
    registradores[2].nome = "M1";
    registradores[3].nome = "M2";
    registradores[4].nome = "D1";
    registradores[5].nome = "D2";
    registradores[6].nome = "R";
    registradores[7].nome = "C";
    registradores[8].nome = "Z";
    registradores[9].nome = "PC";
    registradores[10].nome = "IR";
    registradores[11].nome = "MAR";
    registradores[12].nome = "MBR";
}

// *************** IMPRIMEM A SITUAÇÃO DA MEMÓRIA EM TELA ****************************
void mostraMemoria(){
    printf("\n\n>>>>>>>>>>>>MEMORIA<<<<<<<<<<<<!!!\n\n");
    int i;
    for(i = 0; i<100;i++)
        printf("%d>> %s\n", i, memoria[i]);
}

//************** IMPRIME A SITUAÇÃO DOS REGISTRADORES ******************
void mostraRegistradores(){
    printf("\n\n>>>>>>>>>>>>>>>> REGISTRADORES <<<<<<<<<<<<<<<\n\n");
    printf("A: %d\n",A); // Acumulador
    printf("B: %d\n",B); //: Uso geral
    printf("M1: %d\n",M1); //: Multiplicador
    printf("M2: %d\n",M2); //: Multiplicando
    printf("D1: %d\n",D1); //: Divisor
    printf("D2: %d\n",D2); //: Dividendo
    printf("R: %d\n",R); //: Resto da divisão
    printf("C: %d\n",C); //: Carry out (1: houve carry – 2: não houve carry)
    printf("Z: %d\n",Z); //: Resultado zero(-1: resultado negativo; 0: resultado igual a zero; 1: resultado positivo)
    printf("PC: %d\n",PC); //: Program Counter
    printf("IR: %s\n",IR); //: Instruction Register
    printf("MAR: %d\n",MAR); //: Memory Address Register
    printf("MBR: %s\n",MBR); //: Memory Buffer Register
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

void buscaInstrucao(){
    MAR = PC;
    MBR = memoria[MAR];
    IR = MBR;
    PC++;
}

void decodificaInstrucao(){
    char *token = strtok(IR," ,\t");
    instrucao = token;
}

void calculaOp1(char* nomeRegistrador){
    int i = 0;
    while(strcmp(nomeRegistrador, registradores[i].nome) || i < 13)
        i++;

    op1 = i;
}

void calculaOp2(char* posicaoMemoria){
    op2 = hexaToInt(posicaoMemoria);
    MAR = op2;
}

void calculaEnderecoOperando(){
    char* op1 = strtok(NULL," ,\t");
    char* op2 = strtok(NULL," ,\t");

    calculaOp1(op1);
    calculaOp2(op2);
}

void buscaOperando(){
 // colocar o valor de OP2 no registrador B
}

void executaPrograma(){
    buscaInstrucao();
    decodificaInstrucao();
    calculaEnderecoOperando();
    buscaOperando();
}

int main() {
    criaRegistradores();
    carregaArquivo();

    printf("O Programa foi carregado e está pronto para ser executado.");

    executaPrograma();

    //mostraMemoria();
    mostraRegistradores();

    return 0;
}

