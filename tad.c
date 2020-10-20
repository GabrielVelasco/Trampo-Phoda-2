#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tad.h"
#define max_veic 10
#define max_box 5
/* A ideia eh criar uma fila estatica/sequencial com contador para os veiculos, de acordo com o enunciado,
e eu preferi criar uma fila dinamica para os da lista de espera, pois podem se ter indefinidos veiculos na espera.
E entao intercalar as funcoes para que ao remover da fila comum se inserir o primeiro da fila de espera e assim por diante.
*/

struct veiculo{
char placa[10];
};

struct boxes{
struct veiculo veic[max_veic];
int ini,cont_veic;
};

struct Fila{
struct boxes box[max_box];
int ini,cont_box;
};

struct espera{
struct veiculo veic_esp;
struct espera* prox;
};

struct fila_de_espera{
struct espera* ini;
struct espera* fim;
};

fila cria_fila(){
fila f;
f = (fila) malloc(sizeof(struct Fila));
if(f != NULL){
  f->ini = 0;
  f->cont_box = 0;
  for(int i = 0;i < max_box;i++){
    f->box[i].ini = 0;
    f->box[i].cont_veic = 0;
  }
 }
 return f;
}

int fila_vazia(fila f){
if(f->cont_box == 0)
    return 1;
return 0;
}

int fila_cheia(fila f){
int i,c = 0;
for(i = 0;i < max_box;i++){
    if(f->box[i].cont_veic == max_veic)
        c = c + 1; //conta cada box que esta cheio
   }
 if(c == max_box)
    return 1; // se todos estiverem cheios retorna 1
 return 0;
}

int insere(fila f, char placa[10]){
 if(fila_cheia(f)){
 //inserir na fila de espera
 return 0;
}
 int tamanho[2],i; //procurar pelo box com menos carros e inserir nele
 tamanho[0] = f->box[0].cont_veic; //tamanho[0] = quantos carros, tamanho[1] = qual box esta mais vazio
 for(i = 0;i < max_box;i++){
 if(tamanho[0] > f->box[i].cont_veic){
   tamanho[0] = f->box[i].cont_veic;
   tamanho[1] = i;
  }
 } //ao fim desse loop sera encontrado o box com menor qntd de veiculos
strcpy(f->box[tamanho[1]].veic[(f->box[tamanho[1]].ini + f->box[tamanho[1]].cont_veic)%max_veic].placa,placa);
f->cont_box++;
f->box[tamanho[1]].cont_veic++;
//insercao e contabilizacao feita
return 1; //sucesso
}


/*
int insere(fila f, char placa[10]){
if(fila_cheia(f))
    return 0;

 strcpy(f->box[(f->ini + f->cont_box)%max_box].veic[( f->box[(f->ini + f->cont_box)%max_box].ini + f->box[(f->ini + f->cont_box)%max_box].cont_veic )].placa,placa );
 f->cont_box++;
 f->box[(f->ini + f->cont_box)%max_box].cont_veic++;

 return 1;
}
*/
//strcpy(f->box[(f->ini + f->cont_box)%max_box].veic[( f->box[(f->ini + f->cont_box)%max_box].ini + f->box[(f->ini + f->cont_box)%max_box].cont_veic )].placa,placa );

int remover(fila f, char placa[10]){
 if(fila_vazia(f))
    return 0;
 int i,j;
 for(i = 0;i<max_box;i++){
    for(j=0;j<max_veic;j++){
        if(strcmp(f->box[i].veic[j].placa,placa) == 0)
                  break;
   }
  }
    if(i == max_box && j == max_veic)
    return 0;

    fila aux = f;
    int x,y;

    for(y = 0,x = i;x < f->box[i].cont_veic;y++,x++)
        f->box[i].veic[y] = aux->box[i].veic[x];
    for(x = 0; y < max_veic && x < j; y++,x++ )
       f->box[i].veic[y] = aux->box[i].veic[x];
    //verificar se existe veiculos na lista de espera, inserir o primeiro e o remover da fila.
    return 1;
}



