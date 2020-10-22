typedef struct pilha *Pilha;

Pilha cria_pilha();
int pilha_cheia(Pilha);
int pilha_vazia(Pilha);
//int push(Pilha, int);
//int pop(Pilha, int*);
//int ver_topo(Pilha, int*);
int esvazia(Pilha );
int binario(Pilha p, char decim[34]);
int octal(Pilha p, char decim[34]);
int hexa(Pilha p, char decim[34]);
void imprime(Pilha p);
