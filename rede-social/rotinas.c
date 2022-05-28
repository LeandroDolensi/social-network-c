#ifndef rotina_c
#define rotina_c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "prototipos.h"

#include "ArvoreAVL.c"
#include "grafo_alternativo.c"


void atualizaArquivoId(int id){

    FILE *arquivo;
    arquivo = fopen("dado-id", "wb");

    if (!arquivo){
        return;
    }

    rewind(arquivo);
    fwrite(&id, sizeof(int), 1, arquivo);
    fclose(arquivo);
}

int carregaArquivoId(){

    int id;
    FILE *arquivo;
    arquivo = fopen("dado-id", "rb");

    if (!arquivo){
        return 0;
    }

    rewind(arquivo);
    fread(&id, sizeof(int), 1, arquivo);
    fclose(arquivo);

    return id;
}

void inicializaArvore(ArvAVL *raiz, int *id, Grafo *g){

    pessoa *x = malloc(sizeof(pessoa));
    x->id = ++(*id);
    strcpy(x->cpf, "12312312332");
    strcpy(x->nome, "Carlos");
    strcpy(x->sobrenome, "Almeida");
    insere_ArvAVL(raiz, x);
    g->adj = insereNoGrafo(g->adj, x);


    x = NULL;
    x = malloc(sizeof(pessoa));
    x->id = ++(*id);
    strcpy(x->cpf, "55555555555");
    strcpy(x->nome, "Beto");
    strcpy(x->sobrenome, "Matorato");
    insere_ArvAVL(raiz, x);
    g->adj = insereNoGrafo(g->adj, x);

    x = NULL;
    x = malloc(sizeof(pessoa));
    x->id = ++(*id);
    strcpy(x->cpf, "45678912355");
    strcpy(x->nome, "Ana");
    strcpy(x->sobrenome, "Flamissa");
    insere_ArvAVL(raiz, x);
    g->adj = insereNoGrafo(g->adj, x);

    x = NULL;
    x = malloc(sizeof(pessoa));
    x->id = ++(*id);
    strcpy(x->cpf, "66666666666");
    strcpy(x->nome, "Felipe");
    strcpy(x->sobrenome, "Campos");
    insere_ArvAVL(raiz, x);
    g->adj = insereNoGrafo(g->adj, x);

    x = NULL;
    x = malloc(sizeof(pessoa));
    x->id = ++(*id);
    strcpy(x->cpf, "00000000000");
    strcpy(x->nome, "Eduardo");
    strcpy(x->sobrenome, "Gomes");
    insere_ArvAVL(raiz, x);
    g->adj = insereNoGrafo(g->adj, x);

    x = NULL;
    x = malloc(sizeof(pessoa));
    x->id = ++(*id);
    strcpy(x->cpf, "45898569845");
    strcpy(x->nome, "Daniel");
    strcpy(x->sobrenome, "Silva");
    insere_ArvAVL(raiz, x);
    g->adj = insereNoGrafo(g->adj, x);

    x = NULL;
    x = malloc(sizeof(pessoa));
    x->id = ++(*id);
    strcpy(x->cpf, "75896585412");
    strcpy(x->nome, "Mariana");
    strcpy(x->sobrenome, "Zukerberg");
    insere_ArvAVL(raiz, x);
    g->adj = insereNoGrafo(g->adj, x);

    x = NULL;
    x = malloc(sizeof(pessoa));
    x->id = ++(*id);
    strcpy(x->cpf, "35839336665");
    strcpy(x->nome, "Josivaldo");
    strcpy(x->sobrenome, "Fernandes");
    insere_ArvAVL(raiz, x);
    g->adj = insereNoGrafo(g->adj, x);
}


void setMenuPrincipal(){
    printf("\n=====       MENU PRINCIPAL       =====");
    printf("\n[ 1 ] - Cadastrar na Arvore");
    printf("\n[ 2 ] - Mostrar Arvore");
    printf("\n[ 3 ] - Excluir da Arvore");
    printf("\n[ 4 ] - Cadastrar Amizade");
    printf("\n[ 5 ] - Mostrar Amizades");
    printf("\n[ 6 ] - Mostrar Grafo");
    printf("\n[ 7 ] - Mostrar Sugestoes de Amizade");
    printf("\n[ 8 ] - Exluir Amizade");
    printf("\n[ 0 ] - Sair");
}


int getOpcao(int qdd_opcaos){
    int opcao = -1;

    do {
        printf("\nDigite a opcao desejada:");
        fflush(stdin);
        scanf("%d", &opcao);
    }while (opcao < 0  &  opcao > qdd_opcaos-1);

    return opcao;
    
}


void mostrarArvore(ArvAVL *raiz){

    

    int opcao = -1;
    do {
        printf("\n=====------ MOSTRANDO ARVORE ------=====");
        setMenuMostrar();
        opcao = getOpcao(4);

        if (opcao == 1){
            
            printf("\n=====         PRE ORDEM          =====");
            preOrdem_ArvAVL(raiz);
        }
        if (opcao == 2){ 
            printf("\n=====          EM ORDEM          =====");
            emOrdem_ArvAVL(raiz);
        }
        if (opcao == 3){ 
            printf("\n=====         POS ORDEM          =====");
            posOrdem_ArvAVL(raiz);
        }
    }while (opcao);
}


void setMenuMostrar(){
    printf("\n[ 1 ] - Pre Ordem");
    printf("\n[ 2 ] - Em Ordem");
    printf("\n[ 3 ] - Pos Ordem");
    printf("\n[ 0 ] - Sair");
}


#endif
