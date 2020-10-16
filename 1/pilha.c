#include <stdio.h>
#include <stdlib.h>
#include "libery/pilha.h"
#define maximo 20
struct pilha
{
    int info[maximo];
    int topo;

};

Pilha cria_pila()
{
    Pilha p;
    p=(Pilha)malloc(sizeof(struct pilha));
    if(p!=NULL)
    {
        p->topo=-1;
    }
    return p;
}

int pilha_cheia(Pilha p)
{
    return (p->topo ==maximo-1);
}
int pilha_vazia(Pilha p)
{
    return (p->topo==-1);
}

int push(Pilha p, int n)
{
    if(p==NULL || pilha_cheia(p)==1)
        return 0;
    p->topo++;
    p->info[p->topo]=n;
    return 1;
}
int pop(Pilha p, int* n)
{
    if(p==NULL || pilha_vazia(p)==1)
        return 0;
    *n=p->info[p->topo];
    p->topo--;
    return 1;
}
int ver_topo(Pilha p, int* n)
{
    if(p==NULL || pilha_vazia(p)==1)
        return 0;
    *n=p->info[p->topo];
    return 1;

}
int esvazia(Pilha p)
{
    if(pilha_vazia(p)==1)
    {
        return 0;
    }
    p->topo=-1;
    return 1;
}
int binario(Pilha p, int decimal)
{
    if(p==NULL|| pilha_vazia(p)==1)
        return 0;

    int resto;
    while(decimal>2)
    {
        resto= decima%2;
        push(p,resto);
        decimal= decimal/2;
    }
    if(decimal==2)
    {
        decimal=0;
    }
    push(p,decimal);

    return 1;
}
int octal(Pilha p, int decimal)
{
    if(p==NULL|| pilha_vazia(p)==1)
        return 0;

    int resto;
    while(decimal>8)
    {
        resto= decima%8;
        push(p,resto);
        decimal= decimal/8;
    }
    if(decimal==8)
    {
        decimal=0;
    }
    push(p,decimal);

    return 1;
}

int hexa(Pilha p, int decimal)
{
    if(p==NULL|| pilha_vazia(p)==1)
        return 0;

    int resto;
    while(decimal>16)
    {
        resto= decima%16;
        push(p,resto);
        decimal= decimal/16;
    }
    if(decimal==16)
    {
        decimal=0;
    }
    push(p,decimal);

    return 1;
}
