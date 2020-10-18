#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

int main(){
    int opc, ch = 0, data;
    Stack S = _create_stack(); // S aponta para o TOPO da stack

    char exp[50];
    while(1){
        scanf("%s", exp);
        printf("\nEXP: %s\n", exp);
        ch = _is_valid(&S, exp);
        if(ch == 1)
            printf("Expressao valida!\n");
        else if(ch == -1)
            printf("Erro de ordem!\n");
        else
            printf("Erro de precedencia!\n");

        _clean(&S);
    }

    // while(1){
    //     printf("\n======================MENU=========================================\n");
    //     printf("[0] Create Stack\n");
    //     printf("[1] Push top\n");
    //     printf("[2] Pop top\n");
    //     printf("[3] Print stack\n");
    //     printf("[4] Get top\n");
    //     printf("\nChoose an option: ");
    //     scanf("%d", &opc);


    //     switch(opc){
    //         case 0:
    //             S = _create_stack(); // cria lista vazia (sem nodes)
    //             printf("\nStack created\n");
    //             break;

    //         case 1:
    //             printf("\nPush Back, enter a data:\n");
    //             scanf("%d", &data);
    //             if(_push(&S, data))
    //                 printf("Success!\n");
    //             else
    //                 printf("Something went wrong!\n");
    //             break;

    //         case 2:
    //             if(_pop(&S, &data))
    //                 printf("%d removed!\n", data);
    //             else
    //                 printf("Something went wrong!\n");
    //             break;

    //         case 3:
    //             if(!ch || _empty_stack(S))
    //                 printf("Empty stack or not initialized yet\n");
    //             else
    //                 _print(S);
    //             break;

    //         case 4:
    //             if(_get_top(S, &data))
    //                 printf("Top: %d\n", data);
    //             else
    //                 printf("Error while consulting Top!\n");
    //             break;

    //         default:
    //             ch = 2;

    //             break;
    //     }

    //     if(!ch) ch = 1;
    //     if(ch == 2) break;
    // }

    return 0;
}