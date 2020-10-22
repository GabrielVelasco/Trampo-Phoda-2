#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "queue.h"

/*
	pacientes[0] = fila de pacientes esperando por coracao
	pacientes[1] = fila de pacientes esperando por figado
	pacientes[2] = fila de pacientes esperando por rins
	pacientes[3] = fila de pacientes esperando por cornea
	pacientes[4] = fila de pacientes esperando por pulmao.

	- Inicializar todas as filas, paci[0] ... paci[4]

	- Inserir paciente:
		Entrar com os dados (nome, ...), identificar o orgao e seu respectivo indice no array pacientes[]
		ex; se orgao == coracao, logo sera adicionado em pacientes[0] de acordo com a ordenacao.

		if(orgao == coracao) i = 0, _push(pacientes[i], string nome, string coracao, int idade, int grau)
	
	- Cadastro doador:
		Entrar com os dados (nome, orgaos doados e beneficiado), para cada orgao ler um nome de beneficiado.
		O beneficiado de cada orgao sai da sua respectiva fila de espera.
		Add opcao para imprimir lista doadores (todos os dados).
		Se um doador doa um orgao em que sua respectiva fila de espera esta vazia, o orgao vai para uma fila
		de disponibilidade.
		ex; Fulano doa coracao, se _size(pacientes[0]) == 0, _push(disp, coracao)

*/

void _print_node(char nome[], char orgao[], int idade, int grau, int cont){
	printf("%d - Nome: %s, Orgao: %s, Idade: %d, Grau: %d.\n", cont, nome, orgao, idade, grau);
}

void _print_don_node(char nome[], char orgao_benef[][70]){
	printf("Doador: %s\n", nome);
	for(int i = 0; strcmp(orgao_benef[i], "##") != 0; i++){
		printf("%s\n", orgao_benef[i]);
	}
	printf("\n");
}

int main(){
	Queue pacientes[5], disp;
	Qu_don don;
	char nome[70], orgao[70], benef[70];
	char arr_str[10][70]; 
	int idade, grau, opc, ch = 0, idx;

	while(1){
		printf("\n-------MENU-----------\n");
		printf("[0] Inicializar filas\n");
		printf("[1] Inserir pacientes\n");
		printf("[2] Inserir doador\n");
		printf("[3] Printar listas\n");
		// printf("[6] Consult\n");
		// printf("[Any] Quit\n");
		printf("\nChoose an option: ");
		scanf("%d", &opc);

		int j = 0;
		switch(opc){
			case 0:
				for(int i = 0; i < 5; i++)
					pacientes[i] = _create_list();
				disp = _create_list();
				don = _create_list_d();
				printf("\nListas criadas.\n");

				break;

			case 1:
				printf("\n-Inserir paciente-\n");
				printf("Digite o nome: ");
				scanf(" %[^\n]", nome);

				printf("\nOrgao a ser transplantado: ");
				scanf(" %[^\n]", orgao);

				printf("\nIdade do paciente: ");
				scanf("%d", &idade);

				printf("\nGrau de gravidade: ");
				scanf("%d", &grau);

				if(strcmp(orgao, "coracao") == 0){
					idx = 0;
					/// verifica se tem o orgao na fila de disponibilidade
					if(_is_available(&disp, orgao)){
						printf("Havia '%s' na lista de disponibilidade, paciente foi transplantado.\n", orgao);
					
					/// add paciente na fila de espera
					}else{
						if(_push_patient(&pacientes[idx], nome, orgao, idade, grau))
							printf("'%s' inserido na fila de espera para '%s'.\n", nome, orgao);
					}
				}

				break;

			case 2:
				printf("\n-Inserir doador-\n");
				printf("Digite o nome do doador: ");
				scanf(" %[^\n]", nome);

				while(1){
					printf("Digite o orgao doado por '%s' ('0' para sair): ", nome);
					scanf(" %[^\n]", orgao);
					if(strcmp(orgao, "0") == 0)
						break;
					int piv = 0;
					printf("Nome do paciente que recebera '%s': ", orgao);
					scanf(" %[^\n]", benef);
					if(_pop_name(&pacientes[0], benef)){
						printf("'%s' foi transplantado!\n", benef);
					}else{
						/// fila para tal orgao esta vaizia, orgao doado vai para
						/// fila de disponibilidade
						if(_push_back(&disp, orgao)){
							printf("Fila para '%s' esta vazia, o mesmo fica a disposicao.\n", orgao);
							piv = 1;
						}
					}
					/// concatenar str(orgao + benef) == str orgao == "orgao doou para benef"
					/// arr_str[i] = orgao
					if(piv){
						strcat(orgao, " foi para fila de disponibilidade.");
					}else{
						strcat(orgao, " doou para "); /// orgao == "orgao doou para "
						strcat(orgao, benef); /// aqui, orgao == "orgao doou para benef"
					}
					strcpy(arr_str[j], orgao);
					j++;
				}
				/// aqui ja tenho os dados do doador, logo add na fila
				if(_push_back_donator(&don, nome, arr_str, j))
					printf("'%s' adicionado a fila de doadores.\n", nome);

				break;

			case 3:
				printf("\nFila de espera coracao:\n");
				if(!_print_patient(&pacientes[0]))
					printf("Vazia!\n");
				printf("\n");

				printf("\nFila de doadores:\n");
				if(!_print_donator(&don))
					printf("Vazia!\n");
				printf("\n");

				break;

			default:
				ch = 2;
		}

		if(!ch) ch = 1;
		if(ch == 2) break;
	}

	return 0;
}