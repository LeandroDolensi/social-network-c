#include <stdio.h>
#include <stdlib.h>

#include "ArvoreAVL.c"
#include "rotinas.c"
#include "grafo_alternativo.c"


void main(){

    ArvAVL *avl;
    avl = cria_ArvAVL();
    

    Grafo *g;
    iniciaGrafo(g);
    
    int *id = malloc(sizeof(int));
    *id = carregaArquivoId();

    printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    printf("\n=====  REDE SOCIAL EXPERIMENTAL  =====");
    printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");

    // inicializaArvore(avl, id, g);
    carregaArquivoArvore(avl, g);
    carregaArquivoGrafo(avl, g);

    int opcao;
    opcao = -1;

    do {
        setMenuPrincipal();
        opcao = getOpcao(5);

        if (opcao == 1){
            cadastraNovaPessoa(avl, id, g);

        } else if (opcao == 2){
            mostrarArvore(avl);

        } else if (opcao == 3){
            excluirCadastro(avl, g);

        } else if (opcao == 4){
            cadastrarAmizade(avl, g);

        } else if (opcao == 5){
            mostrarAmizades(avl, g);
        
        } else if (opcao == 6){
            imprimeArestas(g->adj);

        } else if (opcao == 7){
            mostrarSugestoesAmizade(avl, g);

        } else if (opcao == 8){
            excluirAmizade(avl, g);
        }
    } while (opcao);

    atualizaArquivoId(*id);
    atualizarArquivoGrafo(g);
    atualizaArquivoArvore(avl);
}
