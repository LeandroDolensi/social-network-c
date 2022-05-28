#ifndef prototipos_h
#define prototipos_h


// tipos de dados
typedef struct pessoa {
    int id;
    char cpf[12];
    char nome[200];
    char sobrenome[200];
}pessoa;

typedef struct NoArv{
    pessoa *uma_pessoa;
    int altura;
    struct NoArv *esq;
    struct NoArv *dir;
}NoArv;

typedef  NoArv * ArvAVL;

typedef struct NoGrafo {
    pessoa *x;
    struct NoGrafo *prox;
}NoGrafo;

typedef struct Cabeca {
    pessoa *linha;
    NoGrafo * lista;
    struct Cabeca * prox;
} Cabeca;

typedef struct Grafo{
    Cabeca * adj;
}Grafo;




// grafo
void iniciaGrafo(Grafo *g);
Cabeca * insereNoGrafo(Cabeca *c, pessoa *x );
void liberaLista(NoGrafo *lista);
void liberaCabecas(Cabeca *c);
void destroiGrafo(Grafo *g);
NoGrafo * insereNaLista(NoGrafo *lista, pessoa *x);
Cabeca * localizaPosGrafo(Cabeca *c, pessoa *x);
void insereAresta(Grafo *g, pessoa *u, pessoa *v);
NoGrafo * removeDaLista(NoGrafo *lista, pessoa *x);
void  removeAresta(Grafo *g, pessoa *u, pessoa *v);
int temAresta(Grafo *g, pessoa *u, pessoa *v);
void imprimeAmigos(NoGrafo *lista);
void imprimeArestas(Cabeca *c);
Cabeca * removeDoGrafo(Cabeca *c, pessoa *x);
void cadastrarAmizade(ArvAVL *raiz, Grafo *g);
void excluirAmizade(ArvAVL *raiz, Grafo *g);
void mostrarAmizades(ArvAVL *raiz, Grafo *g);
void mostrarSugestoesAmizade(ArvAVL *raiz, Grafo *g);
void imprimeSugestoes(Grafo *g, Cabeca *v, pessoa *x);
int contaNoLinha(NoGrafo *p);
int contaAmizades(Cabeca *c);



// árvore AVL
ArvAVL* cria_ArvAVL();
void libera_ArvAVL(ArvAVL *raiz);
int insere_ArvAVL(ArvAVL *raiz, pessoa *x);
int remove_ArvAVL(ArvAVL *raiz, pessoa *x);
int estaVazia_ArvAVL(ArvAVL *raiz);
int altura_ArvAVL(ArvAVL *raiz);
int totalNO_ArvAVL(ArvAVL *raiz);
int consulta_ArvAVL(ArvAVL *raiz, char cpf[12]);
void preOrdem_ArvAVL(ArvAVL *raiz);
void emOrdem_ArvAVL(ArvAVL *raiz);
void posOrdem_ArvAVL(ArvAVL *raiz);
void mostrarPessoa(pessoa *x, int tipo);
void excluiCadastro(ArvAVL *raiz, Grafo * g);
pessoa * localizaArvAVL(ArvAVL *raiz, char cpf[12]);


// rotinas
void setMenuPrincipal();
int getOpcao(int qdd_opcoes);
void mostrarArvore(ArvAVL *);
void setMenuMostrar();
void inicializaArvore(ArvAVL *raiz, int *id, Grafo *g);
void cadastraNovaPessoa(ArvAVL *raiz, int * id, Grafo *g);
void atualizaArquivoArvore(ArvAVL *raiz);
void gravarArvore(ArvAVL *raiz, FILE *arquivo);
void carregaArquivoArvore(ArvAVL *raiz, Grafo *g);
void atualizarArquivoGrafo(Grafo *g);
void atualizaArquivoId(int id);
int carregaArquivoId();





#endif
