#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pilha.h"
#define maximo 20

struct pilha
{
    int info[maximo][33];
    int topo;
};

Pilha cria_pilha()
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
/*
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
*/
int esvazia(Pilha p){
    if(pilha_vazia(p)==1)
    {
        return 0;
    }
    p->topo=-1;
    return 1;
}
int binario(Pilha p, char decim[34])
{
    if(p==NULL)
        return 0;
    p->topo = p->topo + 1;
    int decimal = atoi(decim);
    int teste = decimal;
    int tamanho = 0;
    while(teste > 2){
       teste = teste/2;
       tamanho++;
    }
    p->info[p->topo][tamanho + 1] = -1;
    while(decimal >= 2)
    {
        p->info[p->topo][tamanho] = decimal%2;
        decimal = decimal / 2;
        tamanho = tamanho - 1;
    }
    if(decimal < 2){
        p->info[p->topo][0] = decimal;
    }
    return 1;
}
int octal(Pilha p, char decim[34])
{
     if(p==NULL)
        return 0;
    p->topo++;
    int decimal = atoi(decim);
    int teste = decimal;
    int tamanho = 0;
    while(teste > 8){
       teste = teste/8;
       tamanho++;
    }
    p->info[p->topo][tamanho + 1] = -1;
    while(decimal>=8)
    {
        p->info[p->topo][tamanho] = decimal%8;
        decimal = decimal / 8;
        tamanho = tamanho - 1;
    }
 /*   if(decimal==8)
    {
        p->info[p->topo][0] = 0;
    }*/
    if(decimal < 8){
        p->info[p->topo][0] = decimal;
    }

    return 1;
}

int hexa(Pilha p, char decim[34])
{
    if(p==NULL)
    return 0;
    p->topo++;
    int decimal = atoi(decim);
    int teste = decimal;
    int tamanho = 0;
    while(teste > 16){
       teste = teste/16;
       tamanho++;
    }
    p->info[p->topo][tamanho + 1] = -1;
    while(decimal>=16)
    {
        p->info[p->topo][tamanho] = decimal%16;
        decimal = decimal / 16;
        tamanho = tamanho - 1;
    }
 /*   if(decimal==16)
    {
        p->info[p->topo][0] = 0;
    }*/
    if(decimal < 16){
        p->info[p->topo][0] = decimal;
    }

    return 1;
}
/*
int imprimePilha(Pilha p){
        if(pilha_vazia(p)==1)
        {
            printf("A pilha esta vazia\n");
            return 0;
        }
      Pilha aux = cria_pilha();

        int n;
        while(pop(p, &n) == 1){
            push(aux, n);
            printf("%d", n);
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
           // printf("\n");
        }
        while(pop(aux, &n) == 1){
            push(p, n);
        }
            return 1;
    }
*/
void imprime(Pilha p){
if(pilha_vazia(p)){
    printf("A pilha esta vazia\n");
}
else{
 int i,j,numero;
 if(p->topo == 0) p->topo++;
  for(i = 0;i < p->topo;i++){
        for(j = 0; p->info[i][j] != -1;j++){
            numero = p->info[i][j];
        switch(numero){
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
            printf("%d",numero);
           }
         }
           printf("\n");
      }
   }
}

