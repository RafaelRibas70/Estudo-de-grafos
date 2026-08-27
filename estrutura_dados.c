#include "estrutura_dados.h"
#include <stdio.h>
#include <stdlib.h>

//=========================FIFO (FILA)======================

void inicializar_fila(Tfila *fila){
    fila->inicio = NULL;
    fila->fim = NULL;
};

void inserir_item_fila(Tfila *fila, int dado){
    Titem_da_fila *aux;
    aux = malloc(sizeof(Titem_da_fila));
    aux->no = dado;
    aux->proximo_no=NULL;
    if(fila->inicio == NULL){
        fila->inicio = aux;
        fila->fim = aux;
    }else{
        fila->fim->proximo_no = aux;
        fila->fim = aux;
    }
}

void tirar_item_da_fila(Tfila *fila){
    Titem_da_fila *aux;
    aux = fila->inicio;
    fila->inicio = fila->inicio->proximo_no;
    if(fila->inicio==NULL){
        fila->fim = NULL;
    }
    free(aux);
}

//=========================LIFO (PILHA)======================

void inicializar_pilha(Tpilha *pilha){
    pilha->inicio = NULL;
}

void inserir_item_da_pilha(Tpilha *inicio, int dado){
    Titem_da_pilha *aux;
    aux = malloc(sizeof(Titem_da_pilha));
    aux->no = dado;
    aux->proximo_no =NULL;
    inicio->inicio = aux;
}

void remover_item_da_pilha(Tpilha *pilha){
    Titem_da_pilha *aux;
    aux = pilha->inicio;
    pilha->inicio = pilha->inicio->proximo_no;
    free(aux);
}