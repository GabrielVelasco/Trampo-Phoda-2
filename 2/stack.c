#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "stack.h"

struct node{
    int key; /// se 1 node armazena int, 0 armazena char.
    void* data;
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

int _push(Stack *S, char data, float f_data, int key){
    /// se key == 1, vou add um float no node
    /// se nao, vou add um char
    Stack node = (Stack) malloc(sizeof(struct node));
    _alloc_check(node, "Error while allocating!");

    node->key = key;
    if(key){
        float* p = (float*) malloc(sizeof(float));
        _alloc_check(p, "Error while allocating float pointer!");
        *p = f_data;
        node->data = p;
    }else{
        char* p = (char*) malloc(sizeof(int));
        _alloc_check(p, "Error while allocating char pointer!");
        *p = data;
        node->data = p;
    }
    //node->data = data;
    node->next = *S; // add no comeco (topo da stack)
    *S = node; // aponta p/ comeco(topo da stack)

    return 1;
}

int _pop(Stack *S, char *c_data, float *f_data){
    if(_empty_stack(*S)) return 0;

    Stack tmp = *S;
    if(tmp->key){
        /// node armazena um float
        *f_data = *((float*)tmp->data);
    }else{
        /// node armazena um char
        *c_data = *((char*)tmp->data);
    }
    //*data = tmp->data;
    *S = tmp->next;
    free(tmp->data);
    free(tmp);

    return 1;
}

int _get_top(Stack *S, char *data){
    if(_empty_stack(*S)) return 0;

    *data = *((char*)(*S)->data);
    return 1;
}

int _preced_op(char op){
    /// calcula precedencia dos operadores
    if(op == '^') return 3;
    else if(op == '*' || op == '/') return 2;
    else if(op == '+' || op == '-') return 1;
    else return 0;
}

void _clean(Stack *S){
    Stack tmp = NULL; /// aponta para topo da stack
    while(*S != NULL){
        tmp = *S; /// aponta para topo da stack, node a ser deletado
        *S = (*S)->next; /// aponta para o node de baixo (novo topo)
        free(tmp->data);
        free(tmp);
    }
}

int _is_valid(Stack *S, char exp[]){
    /// return 1 se exp valida
    /// return 0 se exp tem erro de precedencia
    /// return -1 se exp tem erro de ordem
    char data;
    float tmp;
    for(int i = 0; exp[i] != '\0'; i++){
        /// se exp[i] for abertura vou empilha-lo SE stack estiver vazia OU
        /// se a precedencia (valor do caractere '(', '[' ou '{' na tabela ascii) 
        /// de exp[i] for <= a precedencia de data (elemento do topo da stack)
        /// caso contrario tenho erro de precedencia
        if(exp[i] == '(' || exp[i] == '[' || exp[i] == '{'){
            if(!_get_top(S, &data) || exp[i] <= data)
                _push(S, exp[i], 0, 0);
            else{
                return 0;
            }

        }else if(exp[i] == ')'){
            /// se exp[i] == fechamento, desempilhar elemento do topo (data)
            /// se data (elemento do topo) != abertura, ou se stack estiver vazia, tenho um erro de ordem
            /// obs. abertura e fechamento de que ser do mesmo tipo.
            if(!_pop(S, &data, &tmp) || data != '('){
                return -1;
            }

        }else if(exp[i] == ']'){
            if(!_pop(S, &data, &tmp) || data != '['){
                return -1;
            }

        }else if(exp[i] == '}'){
            if(!_pop(S, &data, &tmp) || data != '{'){
                return -1;
            }
        }
    }

    if(_empty_stack(*S)) /// ao final se stack vazia == exp eh valida
        return 1;
    else
        return -1;
}

void _infix_to_post(Stack *S, char exp[]){
    /// eh garantido que a expressao aqui eh valida dado a sequencia de execucao das funcoes
    /// propostas no ex2.
    char ans[50], data; /// ans guarda exp pos-fixa
    int j = 0;
    float tmp;
    for(int i = 0; exp[i] != '\0'; i++){
        if(exp[i] == '(' || exp[i] == '[' || exp[i] == '{')
            _push(S, exp[i], 0, 0);

        else if(exp[i] == '^'){
            while(_get_top(S, &data) && (_preced_op(data) >= _preced_op(exp[i]))){
                ans[j] = data;
                j++;
                _pop(S, &data, &tmp);
            }
            _push(S, exp[i], 0, 0);
        
        }else if(exp[i] == '*' || exp[i] == '/'){
            while(_get_top(S, &data) && (_preced_op(data) >= _preced_op(exp[i]))){
                ans[j] = data;
                j++;
                _pop(S, &data, &tmp);
            }
            _push(S, exp[i], 0, 0);
        
        }else if(exp[i] == '-' || exp[i] == '+'){
            while(_get_top(S, &data) && (_preced_op(data) >= _preced_op(exp[i]))){
                ans[j] = data;
                j++;
                _pop(S, &data, &tmp);
            }
            _push(S, exp[i], 0, 0);

        }else if(exp[i] == ')' || exp[i] == ']' || exp[i] == '}'){
            while(_get_top(S, &data) && (data != '(' && data != '[' && data != '{')){
                ans[j] = data;
                j++;
                _pop(S, &data, &tmp);
            }
            if(data == '(' || data == '[' || data == '{')
                _pop(S, &data, &tmp);
        
        }else{
            /// exp[i] eh operando
            ans[j] = exp[i];
            j++;
        }
    }

    while(_pop(S, &data, &tmp)){
        ans[j] = data;
        j++;
    }
    ans[j] = '\0';
    strcpy(exp, ans);
}

int _solve_post_fix(Stack *S, char pos[], float *r){
    /// return 0 se estiver faltando operandos, -1 se estiver faltando operadores, 1 sucesso.
    /// expressao tem que estar na forma pos-fixa e os operandos tem
    /// que ser digitos (0,1,...,9).
    char op;
    float x1, x2;
    for(int i = 0; pos[i] != '\0'; i++){
        if(isdigit(pos[i])){
            _push(S, '0', (int)(pos[i]-'0'), 1);
        
        }else{
            /// pos[i] == operador
            op = pos[i];
            if(!_pop(S, &op, &x2) || !_pop(S, &op, &x1))
                return 0;
            
            if(op == '+')
                *r = x1 + x2;
            else if(op == '-')
                *r = x1 - x2;
            else if(op == '*')
                *r = x1 * x2;
            else if(op == '/'){
                if(x2 == 0) 
                    return 2; /// nao pode divisao por 0
                *r = x1 / x2;
            }
            else if(op == '^')
                *r = pow(x1, x2);

            _push(S, '0', *r, 1);
        }
    }

    _pop(S, &op, r);
    if(_empty_stack(*S))
        return 1;
    else
        return -1;
}

void _print(Stack node){
    /// node == ponteiro para o topo da stack
    if(_empty_stack(node))
        _empty_msg();
    while(node != NULL){
        /// se key == 1, node armazena um float, informar funcao print que sera printado
        /// um float.
        if(node->key)
            _print_elem('0', *((float*)node->data), 1);
        else
            _print_elem(*((char*)node->data), 0, 0);
        node = node->next;
    }
}