#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tad.h"
#define max_veic 10
#define max_box 6 //o sexto box eh a fila de espera

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
return f->cont_veic;
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
f->cont_veic--; //diminui 1 no contador, pois 1 veiculo saiu da fila
return 1;
}


int remover(fila f,char placa[10]){
if(fila_vazia(f))
  return 0;
int i;
for(i = 0;i < max_veic;i++){ //procura a placa que deve ser removida
  if(strcmp(f->placa[i],placa) == 0)
   break;
  }
if(i == max_veic)
    return 0; //placa nao encontrada

  fila aux = f;
  int j,g;
  for(j = f->ini,g = i+1; g < f->cont_veic; g++,f++)
    strcpy(f->placa[j],aux->placa[g]); //remove os elementos do inicio e a placa desejada
  for(g = aux->ini; j < f->cont_veic; g++,j++)
    strcpy(f->placa[j],aux->placa[g]); //atribui os elementos do inicio no fim da fila(de acordo como o enunciado pede)
    //sucesso
   f->cont_veic--;
   return 1;
}

void visualizar(fila f){
if(fila_vazia(f))
    printf("O box esta vazio\n");
else{
 int i;
  for(i = f->ini; i < f->cont_veic; i++)
    printf("Placa: [ %s ]\n",f->placa[i]);
  }
 }



//strcpy(f->box[(f->ini + f->cont_box)%max_box].veic[( f->box[(f->ini + f->cont_box)%max_box].ini + f->box[(f->ini + f->cont_box)%max_box].cont_veic )].placa,placa );
/*
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
 }
//ao fim desse loop sera encontrado o box com menor qntd de veiculos
//strcpy(f->box[tamanho[1]].veic[(f->box[tamanho[1]].ini + f->box[tamanho[1]].cont_veic)%max_veic].placa,placa);
strcpy(f->box[tamanho[1]].veic[tamanho[0]].placa,placa);
f->cont_box++;
f->box[tamanho[1]].cont_veic++;
//insercao e contabilizacao feita
return 1; //sucesso
}
*/

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
/*
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
*/
