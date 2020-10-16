typedef struct pilha *Pilha;

Pilha cria_pila();
int pilha_cheia(Pilha);
int pilha_vazia(Pilha);
int push(Pilha, int);
int pop(Pilha, int*);
int ver_topo(Pilha, int*);
int esvazia(Pilha );
int binario(Pilha, int);
int octal(Pilha, int)
int hexa(Pilha, int);

