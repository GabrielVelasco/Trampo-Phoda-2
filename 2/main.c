#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include "stack.h"

/*
    Para entender melhor o funcionamento das funoces _solve_post_fix()
    _infix_to_post() e _is_valid() recomendo ver o video sobre pilha do prof.
    Entendi que o usuario realizaria uma sequencia de 3 passos, validacao, conversao
    e avaliacao/resolucao da expressao de entrada, caso o usuario queira mudar
    fazer apenas uma coisa ou outra basta mudar o app atentando-se que uma 
    funcao as vezes vai depender da outra, ex; _solve..() depende da _infix_to..().

    Como eh usado a math.h caso for compilar no terminal tem que linkar
    usando: gcc -o exec main.c stack.c -lm

    Na parte da resolucao da expressao eh pedido os valores dos literais de 0 a 9
    este processo poderia ser feito dentro da funcao _solve_post_fix().
    
*/

void _print_elem(char c_data, float f_data, int key){
    if(key)
        printf("[%.2f] ", f_data);
    else
        printf("[%c] ", c_data);
}

void _empty_msg(){
    printf("Stack is empty!\n");
}

void _get_value(char exp[]){
    for(int i = 0; exp[i] != '\0'; i++){
        if(exp[i] >= 'A' && exp[i] <= 'J'){
            getchar();
            printf("Digite valor de [%c] (0 a 9): ", exp[i]);
            scanf("%c", &exp[i]);
        }
    }
}

int main(){
    int ch = 0;
    float r;
    char exp[50] = {0}; /// inicializa com strlen == 0
    Stack S = _create_stack(); // S aponta para o TOPO da stack

    while(1){
        printf("\nDigite uma expressao infixa ou '0' para sair: ");
        scanf("%s", exp);
        if(exp[0] == '0')
            break;
        ch = _is_valid(&S, exp);
        if(ch == 1){
            printf("Expressao valida, convertendo para pos-fixa...\n");
            _infix_to_post(&S, exp);

            printf("\nPost-fix: %s\n", exp);
            printf("\nAtribuir valores:\n");
            _get_value(exp);

            ch = _solve_post_fix(&S, exp, &r);
            if(ch == 1){
                printf("Resultado: %.2f\n", r);
            }else if(ch == 0){
                printf("Numero de operandos nao eh adequado!\n");
            }else if(ch == -1){
                printf("Numero de operadores nao eh adequado!\n");
            }else if(ch == 2)
                printf("Nao pode dividir por 0!\n");

        }else if(ch == 0)
            printf("Erro de precedencia!\n");
        else if(ch == -1)
            printf("Erro de ordem!\n");


        _clean(&S);
    }

    return 0;
}