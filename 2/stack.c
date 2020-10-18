#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

struct node{
    char data;
    struct node* next;

};

void _alloc_check(const void* p, char msg[]){
    if(p == NULL){
        perror(msg);
        exit(EXIT_FAILURE);
    }
}

Stack _create_stack(){ return NULL; }

int _empty_stack(Stack S){
    if(S == NULL) return 1;
    else return 0;
}

int _push(Stack *S, char data){
    Stack node = (Stack) malloc(sizeof(struct node));
    _alloc_check(node, "Error while allocating!");

    node->data = data;
    node->next = *S; // add no comeco (topo da stack)
    *S = node; // aponta p/ comeco(topo da stack)

    return 1;
}

int _pop(Stack *S, char *data){
    if(_empty_stack(*S)) return 0;

    Stack tmp = *S;
    *data = tmp->data;
    *S = tmp->next;
    free(tmp);

    return 1;
}

int _get_top(Stack *S, char *data){
    if(_empty_stack(*S)) return 0;

    *data = (*S)->data;
    return 1;
}

int _preced_par(char data){
    /// calcula precedencia dos delimitadores de escopo
    if(data == '(') return 3;
    else if(data == '[') return 2;
    else if(data == '{') return 1;
    else return 0;
}

int _preced_op(char op){
    /// calcula precedencia dos operadores
    
}

void _clean(Stack *S){
    Stack tmp = NULL; /// aponta para topo da stack
    while(*S != NULL){
        tmp = *S; /// aponta para topo da stack
        *S = (*S)->next; /// aponta para o node de baixo (novo topo)
        free(tmp);
    }
}

int _is_valid(Stack *S, char exp[]){
    /// return 1 se exp valida
    /// return 0 se exp tem erro de precedencia
    /// return -1 se exp tem erro de ordem
    char data;
    for(int i = 0; exp[i] != '\0'; i++){
        /// no decorrer da exp a precedencia tem q ir "aumentando", logo
        /// se exp[i] for abertura vou empilhar exp[i] se stack estiver vazia OU
        /// precedencia de exp[i] for >= a precedencia de data (elemento do topo da stack)
        /// caso contrario tenho erro de precedencia
        if(exp[i] == '(' || exp[i] == '[' || exp[i] == '{'){
            if(!_get_top(S, &data) || _preced_par(exp[i]) >= _preced_par(data))
                _push(S, exp[i]);
            else{
                return 0;
            }

        }else if(exp[i] == ')'){
            if(!_pop(S, &data) || data != '('){
                return -1;
            }

        }else if(exp[i] == ']'){
            if(!_pop(S, &data) || data != '['){
                return -1;
            }

        }else if(exp[i] == '}'){
            if(!_pop(S, &data) || data != '{'){
                return -1;
            }
        }
    }

    if(_empty_stack(*S)) /// ao final se stack vazia == exp eh valida
        return 1;
    else
        return -1;
}

int _infix_to_post(){

}

void _print(Stack S){
    while(S != NULL){
        printf("[%c] ", S->data);
        S = S->next;
    }
    printf("\n");
}