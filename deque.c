#include <stdio.h>
#include <stdlib.h>
#include "lib/deque.h"
#define maximo 10
struct deque
{
    int inicio,fim,contador;
    int no[maximo];

};
Deque cria_deque()
{
    Deque deque;
    deque=(Deque)malloc(sizeof(struct deque));
    if(deque!=NULL)
    {
        deque->inicio=0;
        deque->fim=0;
        deque->contador=0;
    }
    return deque;
}
int libera_deque(Deque deque)
{
    free(deque);
}
int deque_vazio(Deque deque)
{
    if(deque==NULL)
        return -1;

    return (deque->contador==0);
}

int deque_cheio(Deque deque)
{
    if(deque==NULL)
        return -1;
    return (deque->contador==maximo);
}

int insere_inicio(Deque deque,int numero)
{
    if(deque==NULL || deque_cheio(deque)==1)
        return 0;
    deque->inicio--;
    if(deque->inicio<0)
    {
        deque->inicio=maximo-1;
    }
    deque->no[deque->inicio]=numero;
    deque->contador++;
    return 1;
}
int insere_final(Deque deque,int numero)
{
    if(deque==NULL || deque_cheio(deque)==1)
        return 0;
    deque->no[deque->fim]=numero;
    deque->fim=(deque->fim+1)%maximo;
    deque->contador++;
    return 1;

}

int remove_inicio(Deque deque)
{
    if(deque==NULL || deque_vazio(deque)==1)
        return 0;
    deque->inicio=(deque->inicio+1)%maximo;
    deque->contador--;
    return 1;
}
int remove_final(Deque deque)
{
    if(deque==NULL || deque_vazio(deque)==1)
        return 0;
    deque->fim--;
    if(deque->fim<0)
        deque->fim=maximo-1;
    deque->contador--;
    return 1;

}

int get_elemento(Deque deque, int pos, int *n)
{
    if(deque==NULL || deque_vazio(deque)==1){
        return 0;
    }
    if(pos>=0)
    *n=deque->no[pos];

}


