#ifndef ESTRUTURA_DE_DADOS
#define ESTRUTURA_DE_DADOS

//=========================FIFO (FILA)======================
typedef struct Titem_da_fila{
    int no;
    struct Titem_da_fila *proximo_no;
}Titem_da_fila;

typedef struct Tfila{
    Titem_da_fila *inicio;
    Titem_da_fila *fim;
}Tfila;

void inicializar_fila(Tfila *fila);

void inserir_item_fila(Tfila *fila, int dado);

void tirar_item_da_fila(Tfila *fila);

//=========================LIFO (PILHA)======================

typedef struct Titem_da_pilha{
    int no;
    struct Titem_da_pilha *proximo_no;
}Titem_da_pilha;

typedef struct Tpilha{
    Titem_da_pilha *inicio;
}Tpilha;

void inicializar_pilha(Tpilha *pilha);

void inserir_item_da_pilha(Tpilha *inicio, int dado);

void remover_item_da_pilha(Tpilha *pilha);


#endif