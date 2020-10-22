#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"

struct node{
	char nome[15], orgao[15];
	int idade, grau; 
	struct node* next;

};

struct node_doadores{
	char nome[15];
	char orgao_benef[10][70]; /// orgao_benef[i] == "orgao doou para benef"
	struct node_doadores* next;

};

void _alloc_check(const void* p, const void* msg){
	if(p == NULL){
		perror(msg);
		exit(EXIT_FAILURE);
	}
}

Queue _create_list(){
	return NULL; // inicializa lista sem nenhum node
}

Qu_don _create_list_d(){
	return NULL; // inicializa lista sem nenhum node
}

int _is_empty(const void *qu){
	// qu == ponteiro para ultimo node
	if(qu == NULL)
		return 1;
	else
		return 0;
}

int _is_available(Queue *qu, char orgao[]){
	/// qu == fila de disponibilidade
	/// se orgao estiver na fila de disponibilidade, paciente ja eh transplantado
	/// e orgao eh deletado da fila de disponibilidade
	if(_is_empty(*qu)) return 0;

	Queue tmp = *qu, tmp2;
	while(tmp->next != *qu){
		if(strcmp(tmp->next->orgao, orgao) == 0){
			tmp2 = tmp->next; /// node sera deletado
			tmp->next = tmp2->next;
			free(tmp2);

			return 1;
		}
		tmp = tmp->next;
	}

	if(tmp->next == *qu && strcmp(tmp->next->orgao, orgao) == 0){
		/// ultimo node vai ser deletado
		if(tmp->next == tmp){
			/// unico node presente na fila
			*qu = NULL; /// fila fica vazia
			free(tmp);
		}else{
			tmp->next = (*qu)->next;
			*qu = tmp; /// novo ultimo node
			free(tmp->next); /// libera antigo ultimo node
		}

		return 1;
	}

}

int _push_patient(Queue *qu, char nome[], char orgao[], int idade, int grau){
	// cria o node e atribui
	Queue node = (Queue) malloc(sizeof(struct node));
	_alloc_check(node, "Error while allocating node, func _push!");

	strcpy(node->nome, nome);
	strcpy(node->orgao, orgao);
	node->idade = idade;
	node->grau = grau;

	// qu == ponteiro para ultimo node
	if(_is_empty(*qu)){
		// node será o primeiro e ultimo
		node->next = node;
		*qu = node;
	
	}else if(grau <= (*qu)->grau){
		/// ordem descendente de grau, logo node instanciado vai na ultima pos.
		node->next = (*qu)->next; // node aponta p/ primeiro
		(*qu)->next = node;
		*qu = node;
	
	}else{
		/// percorrer fila
		Queue tmp = *qu;
		while(tmp->next != *qu && tmp->next->grau > grau){
			tmp = tmp->next;
		}
		if(tmp->next->grau == grau){
			/// se grau for igual, ordena por ordem de chegada.
			tmp = tmp->next;
			// node->next = tmp->next->next;
			// tmp->next->next = node;
		
		}
		node->next = tmp->next;
		tmp->next = node;
	}

	return 1;
}

int _push_back(Queue *qu, char orgao[]){
	/// add orgao na fila de disponibilidade
	Queue node = (Queue) malloc(sizeof(struct node));
	_alloc_check(node, "Error while allocating node, func _push_back!");
	strcpy(node->orgao, orgao);

	if(_is_empty(*qu)){
		// node será o primeiro e ultimo
		node->next = node;
		*qu = node;
	
	}else{
		node->next = (*qu)->next; // node aponta p/ primeiro
		(*qu)->next = node;
		*qu = node; /// novo ultimo node
	}

	return 1;
}

int _push_back_donator(Qu_don *qu, char nome[], char arr_str[][70], int j){
	/// add doador na fila de doadores
	Qu_don node = (Qu_don) malloc(sizeof(struct node_doadores));
	_alloc_check(node, "Error while allocating node, func _push_donator!");

	strcpy(node->nome, nome);
	/// copia cada orgao doado e beneficiado
	int i = 0;
	for(i = 0; i < j; i++){
		strcpy(node->orgao_benef[i], arr_str[i]);
	}
	strcpy(node->orgao_benef[i], "##");

	if(_is_empty(*qu)){
		// node será o primeiro e ultimo
		node->next = node;
		*qu = node;
	
	}else{
		node->next = (*qu)->next; // node aponta p/ primeiro
		(*qu)->next = node;
		*qu = node; /// novo ultimo node
	}

	return 1;
}

int _pop_name(Queue *qu, char nome[]){
	/// remover elemento da fila por nome, 'nome' ja foi transplantado
	if(_is_empty(*qu))	return 0; /// orgao vai para fila de disponibilidade

	Queue tmp = *qu, tmp2;
	while(tmp->next != *qu){
		if(strcmp(tmp->next->nome, nome) == 0){
			tmp2 = tmp->next; /// node sera deletado
			tmp->next = tmp2->next;
			free(tmp2);

			return 1;
		}
		tmp = tmp->next;
	}

	if(tmp->next == *qu && strcmp(tmp->next->nome, nome) == 0){
		/// ultimo node vai ser deletado
		if(tmp->next == tmp){
			/// unico node presente na fila
			*qu = NULL; /// fila fica vazia
			free(tmp);
		}else{
			tmp->next = (*qu)->next;
			*qu = tmp; /// novo ultimo node
			free(tmp->next); /// libera antigo ultimo node
		}

		return 1;
	}

	/// beneficiado n existe na fila, logo orgao vai para o primeiro da fila
	if(_pop_front(qu, nome))
		return 1;
	
	perror("Error at _pop func!");
	exit(EXIT_FAILURE);
}

int _pop_front(Queue *qu, char nome[]){
	if(_is_empty(*qu)) return 0;

	Queue tmp = (*qu)->next; // aponta p/ node a ser removido
	strcpy(nome, tmp->nome); /// copia nome do paciente transplantado

	if(*qu == (*qu)->next)
		*qu = NULL; // fila com um unico node
	else
		(*qu)->next = tmp->next;
	
	free(tmp);

	return 1;
}

int _print_patient(Queue *qu){
	if(_is_empty(*qu)) return 0;
	int cont = 1;
	Queue tmp = (*qu)->next;
	while(tmp != *qu){
		_print_node(tmp->nome, tmp->orgao, tmp->idade, tmp->grau, cont);
		tmp = tmp->next;
		cont ++;
	}
	_print_node(tmp->nome, tmp->orgao, tmp->idade, tmp->grau, cont);
}

int _print_donator(Qu_don *qu){
	if(_is_empty(*qu)) return 0;
	Qu_don tmp = (*qu)->next;
	while(tmp != *qu){
		_print_don_node(tmp->nome, tmp->orgao_benef);
		tmp = tmp->next;
	}
	_print_don_node(tmp->nome, tmp->orgao_benef);
}


// int insertBegi(List *lst, int elem){
// 	List node = (List) malloc(sizeof(struct node));
// 	if( node == NULL ) return 0;
// 	node->num = elem;

// 	if( emptyList(*lst) ){
// 		// node será o primeiro e ultimo
// 		node->next = node;
// 		*lst = node;
// 	}else{
// 		node->next = (*lst)->next; // node passa a ser o primeiro
// 		(*lst)->next = node;
// 	}

// 	return 1;
// }

// int _pop_back(Queue *qu, char orgao[]){
// 	if( _is_empty(*qu) ) return 0;

// 	List tmp = *lst; // aponta p/ node a ser removido (*lst)
// 	*elem = tmp->num; // informacao do elemento removido

// 	if( *lst == (*lst)->next ){
// 		*lst = NULL;
// 	}else{
// 		// move lst p/ o novo ultimo node (atual penultimo)
// 		while( (*lst)->next != tmp ) 
// 			(*lst) = (*lst)->next;

// 		(*lst)->next = tmp->next; // novo ultimo node aponta para o primeiro
// 	}

// 	free(tmp);
// 	return 1;
// }

// int getElem(List lstk, int idx, int *elem){
// 	if( (emptyList(lst)) || (idx >= getSize(lst)) ) return 0; // pos n existe

// 	List tmp = lst->next; // aponta p/ primeiro node
// 	while(idx --)
// 		tmp = tmp->next;

// 	*elem = tmp->num;
// 	return 1;
// }

// int getSize(List lst){
// 	if( emptyList(lst) ) return 0;
// 	List tmp = lst->next; // aponta p/ primeiro node

// 	int size = 1;
// 	while( tmp != lst ){
// 		tmp = tmp->next;
// 		size ++;
// 	}

// 	return size;
// }