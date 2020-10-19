#include <stdio.h>
#include <stdlib.h>
#include "lib/deque.h"
void imprime(Deque d)
{
    int i;
    for(i=0; ; i++)
    {
        int n;
        if(get_elemento(d,i,&n)==0)
        {
            break;

        }
        printf("%d\n",n);
    }

}

int main()
{
    Deque deque;
    int numero,op,criou=0,insere,remove;
    while(1)
    {
        printf("1- criar deque\n");
        printf("2- inserir elemento no deque\n");
        printf("3- remove elemento no deque\n");
        printf("4- imprimir deque\n");
        printf("5 - destruir deque\n");
        printf("6 - sair\n");
        printf("qual a opcao voce deseja ");
        scanf("%d",&op);

        switch(op)
        {

        case 1:
            if(criou==1)
                printf("o deque ja foi criado para cria-lo novamente libere ele primeiramente na op 5\n");


            if(criou==0)
            {
                deque=cria_deque();
                if(deque!=NULL)
                {
                    printf("deque criando sucesso\n");
                    criou=1;
                }
                else
                {
                    printf("nao foi possivel criar o deque\n");
                }

            }
            break;
        case 2:
            if(criou==1)
            {
                printf("diga o numero\n");
                scanf("%d",&numero);

                if(deque_cheio(deque)==1)
                    printf("o deque esta cheio\n");

                printf("onde voce quer inserir 1 inicio 2 final\n");
                scanf("%d",&insere);
                if(insere==1)
                {
                    if(insere_inicio(deque,numero)==1)
                        printf("inserido com sucesso no inicio");
                    else
                        printf("erro ao inserir\n");


                }
                if(insere==2)
                {
                    if(insere_final(deque,numero)==1)
                        printf("inserido com sucesso no final");
                    else
                        printf("erro ao inserir\n");


                }

            }
            else
            {
                printf("deque nao foi criado\n");
            }
            break;
        case 3:
            if(criou==1)
            {
                if(deque_vazio(deque)==1)
                    printf("o deque esta vazio\n");
                else
                {
                    printf("onde voce quer remover 1 inicio 2 final\n");
                    scanf("%d",&remove);


                }
                if(remove==1)
                {


                    if(remove_inicio(deque)==1)
                        printf("removido com sucesso no inicio");
                    else
                        printf("erro ao remover\n");


                }
                if(remove==2)
                {
                    if(deque_vazio(deque)==1)
                        printf("o deque esta vazio\n");
                    if(remove_final(deque)==1)
                        printf("removido com sucesso no final");
                    else
                        printf("erro ao remover\n");


                }

            }
            else
            {
                printf("deque nao foi criado\n");
            }
            break;

        case 4:
            if(criou==1)
            {
                if(deque_vazio(deque)==1){
                        printf("\nnao ha elemento no deque\n");

                }else{

                printf("IMPRIMINDO\n");
                imprime(deque);
                }



            }
            else
            {
                printf("deque nao foi criado\n");
            }
            break;
        case 5:

            if(criou==1)
            {
                if( libera_deque(deque)==1)
                    criou=0;
            }
            else
            {
                printf("deque nao foi criado\n");
            }
            break;
        case 6:
            printf("saindo\n");
            return 0;
            break;
        default:
            printf("opcao invalida digite uma op de 1 a 6\n");
        } //switch



    }

    return 0;
}
