#ifndef ArvoreAVL_c
#define ArvoreAVL_c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "prototipos.h" //inclui os Protótipos
#include "grafo_alternativo.c"


void cadastraNovaPessoa(ArvAVL * raiz, int * id, Grafo *g){
    
    printf("\n=== CADASTRANDO PESSOA ===\n");

    pessoa *x;

    char cpf[12];
    printf("Digite o CPF:");
    fflush(stdin); scanf("%s", &cpf);
    
    if (consulta_ArvAVL(raiz, cpf)){
        printf("\nErro: o cpf %s já está cadastrado.", cpf);
        printf("Cadastro não efetuado.\n");
        return;
    }

    char nome[200];
    printf("Digite o PRIMEIRO nome:");
    fflush(stdin); gets(nome);

    char sobrenome[200];
    printf("Digite o sobrenome:");
    fflush(stdin); gets(sobrenome);


    x = (pessoa *) malloc(sizeof(pessoa));
     
    x->id = ++(*id);
    strcpy(x->cpf, cpf);
    strcpy(x->nome, nome);
    strcpy(x->sobrenome, sobrenome);

    insere_ArvAVL(raiz, x);
    g->adj = insereNoGrafo(g->adj, x);

    printf("===---  Pessoa cadastrada  ---===\n");
}


void excluirCadastro(ArvAVL *raiz, Grafo *g){

    pessoa *x;
    char cpf[12];
    printf("Digite o cpf:");
    fflush(stdin); scanf("%s", &cpf);

    // printf("\n\nTeste:\n:\n:%d\n:\n", consulta_ArvAVL(raiz, cpf));

    if ( ! (consulta_ArvAVL(raiz, cpf)) ){
        printf("Erro: o cpf '%s' não foi encontrado.", cpf);
        return;

    } else {
        x = localizaArvAVL(raiz, cpf);
    }

    removeDoGrafo(g->adj, x);
    remove_ArvAVL(raiz, x);
    printf("\nCadastro Excluido\n");

}


ArvAVL* cria_ArvAVL(){
    
    ArvAVL* raiz = (ArvAVL*) malloc(sizeof(ArvAVL));

    if(raiz != NULL)
        *raiz = NULL;

    // retorna o enderço do ponteiro criado 
    return raiz;
}


void libera_NO(struct NoArv* no){
    if(no == NULL)
        return;
    libera_NO(no->esq);
    libera_NO(no->dir);
    free(no->uma_pessoa);
    free(no);
    no = NULL;
}


void libera_ArvAVL(ArvAVL* raiz){
    if(raiz == NULL)
        return;
    libera_NO(*raiz);//libera cada nó
    free(raiz);//libera a raiz
}


int altura_NO(struct NoArv* no){
    // se caso o nó passado for NULl volta -1, indicando nó vazio
    if(no == NULL)
        return -1;
    else
    // retorna altura do nó
    return no->altura;
}


int fatorBalanceamento_NO(struct NoArv* no){
    // usa labs para colocar em módulo o cáculo de FB
    return labs(altura_NO(no->esq) - altura_NO(no->dir));
}


int maior(int x, int y){
    if(x > y)
        return x;
    else
        return y;
}


int estaVazia_ArvAVL(ArvAVL *raiz){
    if(raiz == NULL)
        return 1;
    if(*raiz == NULL)
        return 1;
    return 0;
}


int totalNO_ArvAVL(ArvAVL *raiz){
    if (raiz == NULL)
        return 0;
    if (*raiz == NULL)
        return 0;
    
    // (*raiz)->esq retorna o endereço dentro dentro de esq, 
    // &(*raiz)->esq retorna o endereço para esq
    int alt_esq = totalNO_ArvAVL(&((*raiz)->esq));
    int alt_dir = totalNO_ArvAVL(&((*raiz)->dir));
    return(alt_esq + alt_dir + 1);
}


int altura_ArvAVL(ArvAVL *raiz){
    if (raiz == NULL)
        return 0;
    if (*raiz == NULL)
        return 0;
    int alt_esq = altura_ArvAVL(&((*raiz)->esq));
    int alt_dir = altura_ArvAVL(&((*raiz)->dir));
    if (alt_esq > alt_dir)
        return (alt_esq + 1);
    else
        return(alt_dir + 1);
}


void preOrdem_ArvAVL(ArvAVL *raiz){
    if(raiz == NULL)
        return;
    if(*raiz != NULL){
        //printf("%d\n",(*raiz)->x.cpf);
        //printf("No %d: %d\n",(*raiz)->x.cpf,fatorBalanceamento_NO(*raiz));
        // printf("No %d: %d\n",(*raiz)->x.cpf,altura_NO(*raiz));
        mostrarPessoa((*raiz)->uma_pessoa, 1);
        preOrdem_ArvAVL(&((*raiz)->esq));
        preOrdem_ArvAVL(&((*raiz)->dir));
    }
}


void mostrarPessoa(pessoa *x, int tipo){

    if (tipo == 1){
        printf("\n------------------------------------------");
        printf("\nId: %d", x->id);
        printf("\nCPF: %s", x->cpf);
        printf("\nNome: %s", x->nome);
        printf("\nSobrenome: %s", x->sobrenome);
        printf("\n------------------------------------------\n");

    } else if (tipo == 2){
        printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
        printf("\nId: %d", x->id);
        printf("\nCPF: %s", x->cpf);
        printf("\nNome: %s", x->nome);
        printf("\nSobrenome: %s", x->sobrenome);
        printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    }
}


void emOrdem_ArvAVL(ArvAVL *raiz){
    if(raiz == NULL)
        return;
    if(*raiz != NULL){
        emOrdem_ArvAVL(&((*raiz)->esq));
        //printf("%d\n",(*raiz)->x.cpf);
        // printf("No %d: H(%d) fb(%d)\n",(*raiz)->x.cpf,altura_NO(*raiz),fatorBalanceamento_NO(*raiz));
        mostrarPessoa((*raiz)->uma_pessoa, 1);
        emOrdem_ArvAVL(&((*raiz)->dir));
    }
}


void posOrdem_ArvAVL(ArvAVL *raiz){
    if(raiz == NULL)
        return;
    if(*raiz != NULL){
        posOrdem_ArvAVL(&((*raiz)->esq));
        posOrdem_ArvAVL(&((*raiz)->dir));
        // printf("%d\n",(*raiz)->x.cpf);
        mostrarPessoa((*raiz)->uma_pessoa, 1);
    }
}


int consulta_ArvAVL(ArvAVL *raiz, char cpf[12]){
    if(raiz == NULL)
        return 0;

    struct NoArv* atual = *raiz;
    while(atual != NULL){
        
        if(strcmp(cpf, atual->uma_pessoa->cpf) ==  0){
            return 1;
        }
        if(strcmp(cpf, atual->uma_pessoa->cpf) == 1)
            atual = atual->dir;
        else
            atual = atual->esq;
    }
    return 0;
}


pessoa * localizaArvAVL(ArvAVL *raiz, char cpf[12]){
    
    /*
    uma das melhores funções recursivas que já fiz
    */
    
    if (raiz == NULL){
        return NULL;
    }

    if (strcmp(cpf, (*raiz)->uma_pessoa->cpf) == -1){
        return localizaArvAVL(&(*raiz)->esq, cpf);

    } else if (strcmp(cpf, (*raiz)->uma_pessoa->cpf) == 1){
        return localizaArvAVL(&(*raiz)->dir, cpf);

    } else if (strcmp(cpf, (*raiz)->uma_pessoa->cpf) == 0){
        return (*raiz)->uma_pessoa;
    }
}


void RotacaoLL(ArvAVL *A){//LL
    // printf("RotacaoLL\n");
    struct NoArv *B;
    B = (*A)->esq;
    (*A)->esq = B->dir;
    B->dir = *A;
    (*A)->altura = maior(altura_NO((*A)->esq),altura_NO((*A)->dir)) + 1;
    B->altura = maior(altura_NO(B->esq),(*A)->altura) + 1;
    *A = B;
}


void RotacaoRR(ArvAVL *A){//RR
    // printf("RotacaoRR\n");
    struct NoArv *B;
    B = (*A)->dir;
    (*A)->dir = B->esq;
    B->esq = (*A);
    (*A)->altura = maior(altura_NO((*A)->esq),altura_NO((*A)->dir)) + 1;
    B->altura = maior(altura_NO(B->dir),(*A)->altura) + 1;
    (*A) = B;
}


void RotacaoLR(ArvAVL *A){//LR
    RotacaoRR(&(*A)->esq);
    RotacaoLL(A);
}


void RotacaoRL(ArvAVL *A){//RL
    RotacaoLL(&(*A)->dir);
    RotacaoRR(A);
}


int insere_ArvAVL(ArvAVL *raiz, pessoa *x){
    int res;
    if(*raiz == NULL){//Árvore vazia ou nó folha

        struct NoArv *novo;
        novo = (struct NoArv*) malloc(sizeof(struct NoArv));
        if(novo == NULL)
            return 0;

        novo->uma_pessoa = x;
        novo->altura = 0;
        novo->esq = NULL;
        novo->dir = NULL;
        *raiz = novo;
        return 1;

    }
    
    struct NoArv *atual = *raiz;
    if(strcmp(x->cpf, atual->uma_pessoa->cpf) < 0){

        if((res = insere_ArvAVL(&(atual->esq), x)) == 1){

            if(fatorBalanceamento_NO(atual) >= 2){

                if(strcmp(x->cpf, (*raiz)->esq->uma_pessoa->cpf) < 0){
                    RotacaoLL(raiz);
                }else{
                    RotacaoLR(raiz);
                }
            }
        }
        
    }else{
        if(strcmp(x->cpf, atual->uma_pessoa->cpf) > 0){

            if((res = insere_ArvAVL(&(atual->dir), x)) == 1){

                if(fatorBalanceamento_NO(atual) >= 2){
                    
                    if(strcmp((*raiz)->dir->uma_pessoa->cpf, x->cpf) < 0){
                        RotacaoRR(raiz);
                    }else{
                        RotacaoRL(raiz);
                    }
                }
            }
        }else{
            printf("Valor duplicado!!\n");
            return 0;
        }
    }

    atual->altura = maior(altura_NO(atual->esq),altura_NO(atual->dir)) + 1;

    return res;
}


struct NoArv* procuraMenor(struct NoArv* atual){
    struct NoArv *no1 = atual;
    struct NoArv *no2 = atual->esq;
    while(no2 != NULL){
        no1 = no2;
        no2 = no2->esq;
    }
    return no1;
}


int remove_ArvAVL(ArvAVL *raiz, pessoa *x){
	if(*raiz == NULL){// valor não existe
	    printf("valor n�o existe!!\n");
	    return 0;
	}

    int res;
    
	if(strcmp(x->cpf, (*raiz)->uma_pessoa->cpf) == -1){
	    if((res = remove_ArvAVL(&(*raiz)->esq, x)) == 1){
            if(fatorBalanceamento_NO(*raiz) >= 2){
                if(altura_NO((*raiz)->dir->esq) <= altura_NO((*raiz)->dir->dir))
                    RotacaoRR(raiz);
                else
                    RotacaoRL(raiz);
            }
	    }
	}
    
	if(strcmp((*raiz)->uma_pessoa->cpf, x->cpf) == -1){
	    if((res = remove_ArvAVL(&(*raiz)->dir, x)) == 1){
            if(fatorBalanceamento_NO(*raiz) >= 2){
                if(altura_NO((*raiz)->esq->dir) <= altura_NO((*raiz)->esq->esq) )
                    RotacaoLL(raiz);
                else
                    RotacaoLR(raiz);
            }
	    }
	}
    
	if(strcmp((*raiz)->uma_pessoa->cpf, x->cpf) == 0){
	    if(((*raiz)->esq == NULL || (*raiz)->dir == NULL)){// nó tem 1 filho ou nenhum
			struct NoArv *oldNode = (*raiz);
			if((*raiz)->esq != NULL)
                *raiz = (*raiz)->esq;
            else
                *raiz = (*raiz)->dir;
            free(oldNode->uma_pessoa);
			free(oldNode);

		}else { // nó tem 2 filhos
			struct NoArv* temp = procuraMenor((*raiz)->dir);
            struct pessoa* aux;

            aux = (*raiz)->uma_pessoa;
            (*raiz)->uma_pessoa = temp->uma_pessoa;
            temp->uma_pessoa = aux;

            // strcpy((*raiz)->uma_pessoa->cpf, temp->uma_pessoa->cpf);
			// (*raiz)->x.cpf = temp->x.cpf;

			remove_ArvAVL(&(*raiz)->dir, temp->uma_pessoa);
            if(fatorBalanceamento_NO(*raiz) >= 2){
				if(altura_NO((*raiz)->esq->dir) <= altura_NO((*raiz)->esq->esq))
					RotacaoLL(raiz);
				else
					RotacaoLR(raiz);
			}
		}

		if (*raiz != NULL)
            (*raiz)->altura = maior(altura_NO((*raiz)->esq),altura_NO((*raiz)->dir)) + 1;
		return 1;
	}

	(*raiz)->altura = maior(altura_NO((*raiz)->esq),altura_NO((*raiz)->dir)) + 1;

	return res;
}

void carregaArquivoArvore(ArvAVL *raiz, Grafo *g){

    /*
    carrega do arquivo, as pessoas cadastradas
    constrói a árvore AVL e o GRAFO (não carrega as amizades);
    */
    
    FILE *arquivo;

    arquivo = fopen("dados-arvore", "rb");

    if (!arquivo){
        printf("\nErro: o arquivo não pode ser aberto");
        return;
    }

    rewind(arquivo);

    pessoa *x = NULL;
    int resultado;

    while (!feof(arquivo)){

        x = (pessoa*) malloc(sizeof(pessoa));
        resultado = fread(x, sizeof(pessoa), 1, arquivo);

        if (resultado){
            insere_ArvAVL(raiz, x);
            g->adj = insereNoGrafo(g->adj, x);

            x = NULL;
        }
    }

    fclose(arquivo);
}


void gravarArvore(ArvAVL *raiz, FILE *arquivo){
    if (raiz == NULL) return;
    if (*raiz != NULL){
        gravarArvore(&((*raiz)->esq), arquivo);

        fwrite((*raiz)->uma_pessoa, sizeof(pessoa), 1, arquivo);

        gravarArvore(&((*raiz)->dir), arquivo);
    }
}


void atualizaArquivoArvore(ArvAVL *raiz){
    
    FILE *arquivo;
    int i, resultado;

    arquivo = fopen("dados-arvore", "wb");

    if (!arquivo){
        printf("\nErro: o arquivo não pode ser aberto.");
        return;
    }

    rewind(arquivo);

    gravarArvore(raiz, arquivo);

    fclose(arquivo);

}



#endif
