#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tad.h"
#define max_veic 10
#define max_box 2 //o sexto box eh a fila de espera

struct Fila{
char placa[max_veic][10];
int ini,cont_veic;
};

fila cria_fila(){
fila f;
f = (fila) malloc(sizeof(struct Fila));
if(f != NULL){
  f->ini = 0;
  f->cont_veic = 0;
 }
 return f;
}

int fila_vazia(fila f){
if(f->cont_veic == 0)
    return 1;
return 0;
}

int tamanho(fila f){
return (f->ini +  f->cont_veic)%max_veic;
}

int fila_cheia(fila f){
if(f->cont_veic == max_veic)
    return 1;
 return 0;
}

int insere(fila f,char placa[10]){
if(fila_cheia(f))
return 0; //fila esta cheia, se a de espera estiver espaco inserir nela

strcpy(f->placa[(f->ini + f->cont_veic)%max_veic],placa);//insercao

f->cont_veic++;//contabilizacao

return 1;
}

void insere_da_espera(fila f,fila esp){
insere(f,esp->placa[0]);
}


int remove_ini(fila f){ //remove o primeiro elemento da fila, sera usada na fila de espera
if(fila_vazia(f))
    return 0;
f->ini = (f->ini+1)%max_veic; //incremento circular na variavel inicio para remover
return 1;
}


int remover(fila f,char placa[10]){
if(fila_vazia(f))
  return 0;
int i,g = 0;
fila aux = cria_fila();
if(aux == NULL) return 0;

for(i = f->ini;i < f->cont_veic;i++){ //procura a placa que deve ser removida
  if(strcmp(f->placa[i],placa) != 0){
    insere(aux,f->placa[i]);
    g++;
   }
  else{
    g++;
    while(g--)
    remove_ini(f);
    int j;
    for(j = 0; j < i;j++){
        insere(f,aux->placa[j]);
    }
    f->cont_veic--;
    free(aux);
    break;
  }
}
if(i == max_veic){
    f = aux;
    return 0; //placa nao encontrada
}
 return 1; //sucesso
}


void visualizar(fila f){
if(fila_vazia(f))
    printf(" Vazio\n");
else{
 int i;
  for(i = f->ini; i < f->cont_veic; i++)
    printf("Placa: [ %s ]\n",f->placa[i]);
  }
 }
/*
int remover(fila f,char placa[10]){
if(fila_vazia(f))
  return 0;
int i;
for(i = 0;i < max_veic;i++){ //procura a placa que deve ser removida
  if(strcmp(f->placa[i],placa) == 0){
   break;
  }
}
if(i == max_veic)
    return 0; //placa nao encontrada

  fila aux = f;
  int j,g;
  for(j = f->ini,g = i+1; g < f->cont_veic; g++,j++)
    strcpy(f->placa[j],aux->placa[g]); //remove os elementos do inicio e a placa desejada
   for(g = aux->ini; j < f->cont_veic-1; g++,j++)
    strcpy(f->placa[j],aux->placa[g]); //atribui os elementos do inicio no fim da fila(de acordo como o enunciado pede)
    //sucesso
   f->cont_veic--;
   return 1;
}
*/
