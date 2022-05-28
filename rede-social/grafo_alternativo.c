#ifndef grafo_h
#define grafo_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "prototipos.h"



void atualizarArquivoGrafo(Grafo *g){

    int qdd_amizades = contaAmizades(g->adj);
    char amizades[qdd_amizades][2][12];

    Cabeca *aux_cabeca;
    aux_cabeca = g->adj;

    NoGrafo *aux_no_grafo;

    int i = 0;
    while (aux_cabeca){
        aux_no_grafo = aux_cabeca->lista;
        
        while (aux_no_grafo){
            strcpy(amizades[i][0], aux_cabeca->linha->cpf);
            strcpy(amizades[i][1], aux_no_grafo->x->cpf);
            aux_no_grafo = aux_no_grafo->prox;
            i++;
        }
        aux_cabeca = aux_cabeca->prox;
    }

    // for (i=0 ; i<qdd_amizades ; i++){
    //     printf("\n%s --> %s\n", amizades[i][0], amizades[i][1]);
    // }


    FILE *arquivo;
    int resultado;

    arquivo = fopen("dado-grafo", "wb");

    if (!arquivo){
        printf("\nErro: o arquivo não pode ser aberto");
        return;
    }

    rewind(arquivo);

    for( i=0 ; i<qdd_amizades ; i++){
        resultado = fwrite(&amizades[i], sizeof(char[2][12]), 1, arquivo);
    }

    fclose(arquivo);

}


void carregaArquivoGrafo(ArvAVL *raiz, Grafo *g){

    
    char amizades[1][2][12];

    FILE *arquivo;
    int resultado, i;
    arquivo = fopen("dado-grafo", "rb");

    if (!arquivo){
        printf("arquivo não aberto");
        return;
    }

    rewind(arquivo);

    pessoa *u;
    pessoa *v;

    while (! feof(arquivo) ){
        resultado = fread(&amizades[0], sizeof(char[2][12]), 1, arquivo);
        
        if (!resultado){
            return;
        }

        // printf("\n%s --> %s\n", amizades[0][0], amizades[0][1]);
        u = localizaArvAVL(raiz, amizades[0][0]);
        v = localizaArvAVL(raiz, amizades[0][1]);
        insereAresta(g, u, v);
    }

    fclose(arquivo);
    
}


int contaAmizades(Cabeca *c){

    int contagem;

    if (c != NULL){
        contagem = contaAmizades(c->prox);
        contagem = contagem + contaNoLinha(c->lista);
        return contagem;

    } else {
        return 0;
    }
}


int contaNoLinha(NoGrafo *p){
    if (p == NULL){
        return 0;

    } else {
        return contaNoLinha(p->prox) + 1;
    }
}


void iniciaGrafo(Grafo *g){
    g->adj = NULL;
}


Cabeca * insereNoGrafo(Cabeca *c, pessoa *x ){
    
    if (c != NULL ){
        c->prox = insereNoGrafo(c->prox, x);
        return c;

    } else {
        Cabeca *novo;
        novo = (Cabeca *) malloc(sizeof(Cabeca));
        novo->linha = x;
        novo->lista = NULL;
        novo->prox = NULL;
        return novo;
    }
}


Cabeca * removeDoGrafo(Cabeca *c, pessoa *x){

    /*
    umas das melhores funções recursivas que já viz
    */

    if (c != NULL){
        c->prox = removeDoGrafo(c->prox, x);

    } else {
        return c;
    }


    if (strcmp(c->linha->cpf, x->cpf) == 0){
        
        Cabeca *aux;
        aux = c->prox;

        liberaLista(c->lista);
        free(c);
        return aux;

    } else {
        c->lista = removeDaLista(c->lista, x);
        return c;
    }
}


void cadastrarAmizade(ArvAVL *raiz, Grafo *g){

    printf("\n=== CADASTRANDO AMIZADE ===\n");

    pessoa *u;
    pessoa *v;

    char cpf_u[12];
    char cpf_v[12];

    printf("Digite o cpf da primeira pessoa:");
    fflush(stdin); scanf("%s", &cpf_u);

    printf("Digite o cpf da segunda pessoa:");
    fflush(stdin); scanf("%s", &cpf_v);

    u = localizaArvAVL(raiz, cpf_u);
    v = localizaArvAVL(raiz, cpf_v);
    
    if ((u == NULL) || (v == NULL)){
        printf("\nErro: cpf não encontrado.");
        return;
    }

    insereAresta(g, u, v);
    printf("\nAmizade cadastrada\n");
}


void excluirAmizade(ArvAVL *raiz, Grafo *g){
    printf("\n=== EXCLUINDO AMIZADE ===\n");

    pessoa *u;
    pessoa *v;

    char cpf_u[12];
    char cpf_v[12];

    printf("Digite o cpf da primeira pessoa:");
    fflush(stdin); scanf("%s", &cpf_u);

    printf("Digite o cpf da segunda pessoa:");
    fflush(stdin); scanf("%s", &cpf_v);

    u = localizaArvAVL(raiz, cpf_u);
    v = localizaArvAVL(raiz, cpf_v);
    
    if ((u == NULL) || (v == NULL)){
        printf("\nErro: cpf não encontrado.");
        return;
    }
    removeAresta(g, u, v);
    printf("\nAmizade excluida\n");
}


void mostrarAmizades(ArvAVL *raiz, Grafo *g){
    printf("\n=== MOSTRANDO AMIZADES ===\n");

    pessoa *x;
    Cabeca *c;

    char cpf[12];

    printf("Digite o cpf:");
    fflush(stdin); scanf("%s", &cpf);

    x = localizaArvAVL(raiz, cpf);
    c = localizaPosGrafo(g->adj, x);

    if (c != NULL){
        printf("PESSOA:");
        mostrarPessoa(x, 1);

        printf("\nAMIGOS:");
        imprimeAmigos(c->lista);
    }
}


void mostrarSugestoesAmizade(ArvAVL *raiz, Grafo *g){
    printf("\n=== MOSTRANDO SUGESTOES de AMIZADE ===\n");
    

    pessoa *u;
    Cabeca *v;
    v = g->adj;

    char cpf[12];
    printf("Digite o cpf:");
    fflush(stdin); scanf("%s", &cpf);

    u = localizaArvAVL(raiz, cpf);

    while (v) {
        if (( strcmp(cpf, v->linha->cpf) != 0 ) && ( temAresta(g, u, v->linha) )){
            imprimeSugestoes(g, v, u);
        }
        v = v->prox;
    }
}


void imprimeSugestoes(Grafo *g, Cabeca *v, pessoa *x){
    
    NoGrafo *aux;
    aux = v->lista;

    printf("\n\nAMIGO:");
    mostrarPessoa(v->linha, 2);

    printf("\nSUGESTOES:");

    while (aux) {
        if ((strcmp(aux->x->cpf, x->cpf) != 0) && (! temAresta(g, aux->x, x))){
            mostrarPessoa(aux->x, 1);
        } 
        aux = aux->prox;
    }
}


void liberaLista(NoGrafo *lista){
    if (lista != NULL){
        liberaLista(lista->prox);
        free(lista);
    }
}


void liberaCabecas(Cabeca *c){

    if (c != NULL){
        liberaCabecas(c->prox);
        liberaLista(c->lista);
        free(c);
    }
    return;
}


void destroiGrafo(Grafo *g){
    liberaCabecas(g->adj);
    free(g);
}


NoGrafo * insereNaLista(NoGrafo *lista, pessoa *x){
    NoGrafo *novo;
    novo = (NoGrafo*) malloc(sizeof(NoGrafo));
    novo->x = x;
    novo->prox = lista;

    return novo;
}


Cabeca * localizaPosGrafo(Cabeca *c, pessoa *x){
    Cabeca *posicao;
    if ( c != NULL && (strcmp(c->linha->cpf, x->cpf) != 0)){
        posicao = localizaPosGrafo(c->prox, x);
        return posicao;
    } else {
        return c;
    }
}


void insereAresta(Grafo *g, pessoa *u, pessoa *v){

    Cabeca * pos_u = localizaPosGrafo(g->adj, u);
    Cabeca * pos_v = localizaPosGrafo(g->adj, v);

    if ((pos_u == NULL) || (pos_v == NULL)){
        printf("\nErro: amizade não inserida.");
        return;
    }

    if (temAresta(g, u, v)){
        return;
    }


    pos_u->lista = insereNaLista(pos_u->lista, v);
    pos_v->lista = insereNaLista(pos_v->lista, u);

}


NoGrafo * removeDaLista(NoGrafo *lista, pessoa *x){
    if( lista == NULL){
        return NULL;

    } else if (strcmp(lista->x->cpf, x->cpf) == 0){
        NoGrafo *proximo;
        proximo = lista->prox;
        free(lista);
        return proximo;

    } else {
        lista->prox = removeDaLista(lista->prox, x);
        return lista;
    }
}


void  removeAresta(Grafo *g, pessoa *u, pessoa *v){
    
    Cabeca *pos_u = localizaPosGrafo(g->adj, u);
    Cabeca *pos_v = localizaPosGrafo(g->adj, v);

    pos_u->lista = removeDaLista(pos_u->lista, v);
    pos_v->lista = removeDaLista(pos_v->lista, u);

}


int temAresta(Grafo *g, pessoa *u, pessoa *v){
    Cabeca *pos_u;
    NoGrafo *p;

    pos_u = localizaPosGrafo(g->adj, u);
    
    for( p=pos_u->lista ; p!=NULL ; p=p->prox ){
        if (strcmp(p->x->cpf, v->cpf) == 0){
            return 1;
        }
    }
    return 0;
}


void imprimeAmigos(NoGrafo *lista){
    if (lista != NULL){
        imprimeAmigos(lista->prox);
        mostrarPessoa(lista->x, 2);
    } else {
        return;
    }
}


void imprimeArestas(Cabeca *c){
    if (c != NULL){
        imprimeArestas(c->prox);

        printf("\n\n\n\nPESSOA:");
        mostrarPessoa(c->linha, 1);

        printf("\nAMIGOS:");
        imprimeAmigos(c->lista);
        
    } else {
        return;
    }
}


#endif
