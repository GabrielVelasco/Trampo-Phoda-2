#include <stdio.h>
#include <stdlib.h>
#include "libery/pilha.h"


int imprimePilha(Pilha p){
        if(pilha_vazia(p)==1)
        {
            printf("A pilha esta vazia\n");
            return 0;
        }
      Pilha aux = cria_pilha();

        int i,n;
        while(pop(p, &n) == 1){
            push(aux, n);
            printf("%d\n", n);
            switch (n){
        case 10:
            printf("A");
            break;
        case 11:
            printf("B");
            break;
        case 12:
            printf("C");
            break;
        case 13:
            printf("D");
            break;
        case 14:
            printf("E");
            break;
        case 15:
            printf("F");
            break;
        default:
            printf("%d",n);
            }
        }
        while(pop(aux, &n) == 1){
            push(p, n);
        }
            return 1;
    }
int main()
{


    return 0;
}
