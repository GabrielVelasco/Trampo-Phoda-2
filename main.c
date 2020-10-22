#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pilha.h"

int main()
{
    Pilha p;
    char num[34];
    int op;
    p = cria_pilha();
    if(p == NULL){
        printf("Erro na alocacao de memoria para pilha\n");
        return 0;
    }
    printf("1-Binario           2-Octal\n");
    printf("3-Hexadecimal       4-Imprimir\n");
    printf("5-Esvaziar\n");
    printf("Ao digitar numero negativo o programa terminara\n");

    while(1){
         printf("Digite uma opcao\n");
         scanf("%d",&op);
         if(op < 4){
         printf("Digite um numero:\n");
         setbuf(stdin,NULL);
         gets(num);
         if(num < 0){
            printf("Fim\n");
            return 0;
         }
        }
         switch (op){
            case 1:
              if(binario(p,num))
                printf("Sucesso na conversao e insercao em binario\n");
              else
                printf("Falha na conversao e insercao em binario\n");
             break;
//-------------------------------------------------------------------------------------
            case 2:
                if(octal(p,num))
                    printf("Sucesso na conversao e insercao em octal\n");
                else
                    printf("Falha na conversao e insercao em octal\n");
               break;
//-------------------------------------------------------------------------------------
            case 3:
                if(hexa(p,num))
                    printf("Sucesso na conversao e insercao em hexadecimal\n");
                else
                    printf("Falha na conversao e insercao em hexadecimal\n");
                break;
//--------------------------------------------------------------------------------------
            case 4:
                imprime(p);
                break;
//--------------------------------------------------------------------------------------
            case 5:
                if(esvazia(p))
                    printf("Pilha esvaziada com sucesso\n");
                else
                    printf("Falha, ja estava vazia\n");
                break;
          }
        }
    return 0;
}
