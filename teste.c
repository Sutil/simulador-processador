#include <string.h>
#include <stdio.h>

char palavra[] = "a string,of ,,tokens";


void split(char string[])
{

        char *token = strtok(string," ,"); /*There are two delimiters here*/
        int count = 0;
        while (token != NULL){
                printf("The token is:  %s\n", token);
                token = strtok(NULL," ,");
        }

}


void main(void){
    printf("%d", strcmp("testa", "teste"));

}
