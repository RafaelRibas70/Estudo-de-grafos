#include "metodos_pesquisa.h"
#include "estrutura_dados.h"
#include <stdio.h>
#include <stdlib.h>

void pesquisa_DFS(int qtd_vertice, int **matriz, int *vet_visitado, int vertice_inicio, int *vet_ordem) {
    Tpilha pilha;
    inicializar_pilha(&pilha);
    int posicao = 0;

    // Garante a visita a TODOS os vértices do grafo
    for (int k = 0; k < qtd_vertice; k++) {
        // Na primeira iteração começa no vértice escolhido; nas seguintes, testa de 0 a N-1
        int v_atual = (k == 0) ? (vertice_inicio - 1) : k;

        if (vet_visitado[v_atual] == 0) {
            inserir_item_da_pilha(&pilha, v_atual);

            while (pilha.inicio != NULL) {
                int atual = pilha.inicio->no;
                remover_item_da_pilha(&pilha);

                if (vet_visitado[atual] == 0) {
                    vet_visitado[atual] = 1;
                    vet_ordem[posicao] = atual + 1;
                    posicao++;

                    for (int j = qtd_vertice - 1; j >= 0; j--) {
                        if (matriz[atual][j] == 1 && vet_visitado[j] == 0) {
                            inserir_item_da_pilha(&pilha, j);
                        }
                    }
                }
            }
        }
    }
}

void pesquisa_BFS(int qtd_vertice, int **matriz, int *vet_visitado, int vertice_inicio, int *vet_ordem) {
    Tfila fila;
    inicializar_fila(&fila);
    int posicao = 0;

    // Garante a visita a TODOS os vértices do grafo
    for (int k = 0; k < qtd_vertice; k++) {
        int v_atual = (k == 0) ? (vertice_inicio - 1) : k;

        if (vet_visitado[v_atual] == 0) {
            vet_visitado[v_atual] = 1;
            vet_ordem[posicao] = v_atual + 1;
            posicao++;

            inserir_item_fila(&fila, v_atual);

            while (fila.inicio != NULL) {
                int atual = fila.inicio->no;
                tirar_item_da_fila(&fila);

                for (int j = 0; j < qtd_vertice; j++) {
                    if (matriz[atual][j] == 1 && vet_visitado[j] == 0) {
                        vet_visitado[j] = 1;
                        inserir_item_fila(&fila, j);
                        vet_ordem[posicao] = j + 1;
                        posicao++;
                    }
                }
            }
        }
    }
}   

void fecho_transitivo_direto(int qtd_vertice, int **matriz, int vertice_inicio, int *vet_fecho) {
    Tfila fila;
    inicializar_fila(&fila);

    int inicio = vertice_inicio - 1;

    for (int i = 0; i < qtd_vertice; i++) {
        vet_fecho[i] = 0;
    }

    vet_fecho[inicio] = 1;
    inserir_item_fila(&fila, inicio);

    while (fila.inicio != NULL) {
        int atual = fila.inicio->no;
        tirar_item_da_fila(&fila);

        for (int destino = 0; destino < qtd_vertice; destino++) {
            if (matriz[atual][destino] == 1 && vet_fecho[destino] == 0) {
                vet_fecho[destino] = 1;
                inserir_item_fila(&fila, destino);
            }
        }
    }
}

void fecho_transitivo_inverso(int qtd_vertice, int **matriz, int vertice_inicio, int *vet_fecho) {
    Tfila fila;
    inicializar_fila(&fila);

    int inicio = vertice_inicio - 1;

    for (int i = 0; i < qtd_vertice; i++) {
        vet_fecho[i] = 0;
    }

    vet_fecho[inicio] = 1;
    inserir_item_fila(&fila, inicio);

    while (fila.inicio != NULL) {
        int atual = fila.inicio->no;
        tirar_item_da_fila(&fila);

        for (int origem = 0; origem < qtd_vertice; origem++) {
            if (matriz[origem][atual] == 1 && vet_fecho[origem] == 0) {
                vet_fecho[origem] = 1;
                inserir_item_fila(&fila, origem);
            }
        }
    }
}

//=========================MANIPULAÇÃO E IMPRESSÃO DO GRAFO======================

void print_matriz(int qtd_vertice, int **matriz) {
    for (int i = 0; i < qtd_vertice; i++) {
        for (int j = 0; j < qtd_vertice; j++) {
            printf("%d\t", matriz[i][j]);
        }
        printf("\n\n");
    }
}

int mod_remove(int qtd_vertice, int **matriz, int vertice_origem, int vertice_destino, int mod) {
    if (vertice_origem > qtd_vertice || vertice_destino > qtd_vertice || vertice_origem < 1 || vertice_destino < 1) {
        return -1;
    }

    if (mod == 1) {
        matriz[vertice_origem - 1][vertice_destino - 1] = 0;
    }
    if (mod == 2) {
        matriz[vertice_origem - 1][vertice_destino - 1] = 0;
        matriz[vertice_destino - 1][vertice_origem - 1] = 0;
    }

    return 0;
}

int mod_add(int qtd_vertice, int **matriz, int vertice_origem, int vertice_destino, int mod, int valor_vertice) {
    if (vertice_origem > qtd_vertice || vertice_destino > qtd_vertice || vertice_origem < 1 || vertice_destino < 1) {
        return -1;
    }

    if (mod == 1) {
        matriz[vertice_origem - 1][vertice_destino - 1] = valor_vertice;
    }
    if (mod == 2) {
        matriz[vertice_origem - 1][vertice_destino - 1] = valor_vertice;
        matriz[vertice_destino - 1][vertice_origem - 1] = valor_vertice;
    }

    return 0;
}

int** alocar_matriz(int n) {
    int **matriz = malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        matriz[i] = calloc(n, sizeof(int));
    }
    return matriz;
}

void liberar_matriz(int **matriz, int n) {
    for (int i = 0; i < n; i++) {
        free(matriz[i]);
    }
    free(matriz);
}

int** adicionar_vertice(int *qtd_vertice, int **matriz) {
    int novo_n = *qtd_vertice + 1;
    int **nova_matriz = alocar_matriz(novo_n);

    for (int i = 0; i < *qtd_vertice; i++) {
        for (int j = 0; j < *qtd_vertice; j++) {
            nova_matriz[i][j] = matriz[i][j];
        }
    }

    liberar_matriz(matriz, *qtd_vertice);
    *qtd_vertice = novo_n;

    printf("Vértice %d adicionado com sucesso!\n", *qtd_vertice);
    return nova_matriz;
}

int** remover_vertice(int *qtd_vertice, int **matriz, int vertice_remover) {
    if (vertice_remover < 1 || vertice_remover > *qtd_vertice) {
        printf("Vértice inválido para remoção!\n");
        return matriz;
    }

    int novo_n = *qtd_vertice - 1;
    if (novo_n == 0) {
        liberar_matriz(matriz, *qtd_vertice);
        *qtd_vertice = 0;
        printf("Vértice %d removido. Grafo agora está vazio!\n", vertice_remover);
        return NULL;
    }

    int **nova_matriz = alocar_matriz(novo_n);
    int idx_remover = vertice_remover - 1;

    int nova_i = 0;
    for (int i = 0; i < *qtd_vertice; i++) {
        if (i == idx_remover) continue;
        int nova_j = 0;
        for (int j = 0; j < *qtd_vertice; j++) {
            if (j == idx_remover) continue;
            nova_matriz[nova_i][nova_j] = matriz[i][j];
            nova_j++;
        }
        nova_i++;
    }

    liberar_matriz(matriz, *qtd_vertice);
    *qtd_vertice = novo_n;
    printf("Vértice %d removido com sucesso!\n", vertice_remover);

    return nova_matriz;
}

//=========================CONEXIDADE E SUBGRAFOS======================

void verificar_conexidade_e_sfc(int qtd_vertice, int **matriz) {
    // Alocação dinâmica dos vetores auxiliares
    int *fecho_dir = calloc(qtd_vertice, sizeof(int));
    int *fecho_inv = calloc(qtd_vertice, sizeof(int));
    int *visitado = calloc(qtd_vertice, sizeof(int));

    int num_sfc = 0;
    int eh_fortemente_conexo = 1;

    printf("--- Subgrafos fortemente conexos maximos (SFC) ---\n");

    for (int i = 0; i < qtd_vertice; i++) {
        if (visitado[i] == 0) {
            num_sfc++;
            int v_inicio = i + 1;

            fecho_transitivo_direto(qtd_vertice, matriz, v_inicio, fecho_dir);
            fecho_transitivo_inverso(qtd_vertice, matriz, v_inicio, fecho_inv);

            printf("SFC %d: { ", num_sfc);
            int tam_sfc = 0;
            for (int j = 0; j < qtd_vertice; j++) {
                if (fecho_dir[j] == 1 && fecho_inv[j] == 1) {
                    printf("%d ", j + 1);
                    visitado[j] = 1;
                    tam_sfc++;
                }
            }
            printf("}\n");

            if (tam_sfc < qtd_vertice) {
                eh_fortemente_conexo = 0;
            }
        }
    }

    printf("\n Resultado da verificacao:\n");
    if (eh_fortemente_conexo == 1 && num_sfc == 1) {
        printf("-> O grafo É FORTEMENTE CONEXO.\n");
    } else {
        printf("-> O grafo NAO É fortemente conexo.\n");
        printf("-> Total de subgrafos fortemente conexos maximos: %d\n", num_sfc);
    }

    // Libera a memória alocada para os vetores
    free(fecho_dir);
    free(fecho_inv);
    free(visitado);
}


//=========================COLORACAO==================================
void colorir_matriz(int qtd_vertice, int *resultado, int **matriz, int *ordem_pintura) {

    int *vertice_grau = calloc(qtd_vertice, sizeof(int));
    int *pintado = calloc(qtd_vertice, sizeof(int));

    int contador_ordem = 0;
    int maior_grau;
    int vertice_maior;
    int cor;
    int cor_usada;

    // Inicializa os vetores.
    for (int i = 0; i < qtd_vertice; i++) {
        resultado[i] = 0;
        ordem_pintura[i] = 0;

        // Calcula o grau de cada vértice.
        for (int j = 0; j < qtd_vertice; j++) {
            if (matriz[i][j] != 0) {
                vertice_grau[i]++;
            }
        }
    }

    // Repete até que todos os vértices sejam pintados.
    for (int k = 0; k < qtd_vertice; k++) {

        // Escolhe o vértice não pintado de maior grau.
        maior_grau = -1;
        vertice_maior = -1;

        for (int i = 0; i < qtd_vertice; i++) {
            if (pintado[i] == 0 && vertice_grau[i] > maior_grau) {
                maior_grau = vertice_grau[i];
                vertice_maior = i;
            }
        }

        // Se não houver vértice disponível, encerra.
        if (vertice_maior == -1) {
            break;
        }

        // Registra a ordem em que o vértice foi escolhido.
        ordem_pintura[contador_ordem] = vertice_maior + 1;
        contador_ordem++;

        // Procura a menor cor que não esteja nos vizinhos.
        cor = 1;

        do {
            cor_usada = 0;

            for (int j = 0; j < qtd_vertice; j++) {
                if (matriz[vertice_maior][j] != 0 &&
                    resultado[j] == cor) {
                    cor_usada = 1;
                    break;
                }
            }

            if (cor_usada) {
                cor++;
            }

        } while (cor_usada);

        // Atribui a cor ao vértice escolhido.
        resultado[vertice_maior] = cor;
        pintado[vertice_maior] = 1;
    }

    free(vertice_grau);
    free(pintado);
}
//=========================DIJKSTRA===================================

void alg_dijkstra (int vertice_partida, int qtd_vertice, int *estimativa, int **matriz){

    int precedente[qtd_vertice];
    int visitado[qtd_vertice];
    int infinito = 9999999;

    for (int i = 0; i < qtd_vertice; i++){
        estimativa[i] = infinito;
        precedente[i] = -1;
        visitado[i] = 0;
    }

    estimativa[vertice_partida] = 0;

    int atual = vertice_partida;

    for (int i = 0; i < qtd_vertice; i++){
        for (int j = 0; j < qtd_vertice; j++){
            if (matriz[atual][j] != 0 && visitado[j] == 0){
                int nova_estimativa = estimativa[atual] + matriz[atual][j];
                if (nova_estimativa < estimativa[j]){
                    estimativa[j] = nova_estimativa;
                    precedente[j] = atual;
                }
            }
        }

        visitado[atual] = 1;
        int menor = infinito;
        int proximo = -1;

        for (int j = 0; j < qtd_vertice; j++){
            if (visitado[j] == 0 && estimativa[j] < menor){
                menor = estimativa[j];
                proximo = j;
            }
        }

        if (proximo == -1){
            break;
        }
        atual = proximo;
    }
}
//=========================ALG_ESTRELA===================================
/*
void alg_aestrela (int vertice_partida, int vertice_destino, int qtd_vertice, int *estimativa, int **matriz, int *heuristica){
    int precedente[qtd_vertice];
    int visitado[qtd_vertice];
    int infinito = 9999999;

    for (int i = 0; i < qtd_vertice; i++){
        estimativa[i] = infinito;
        precedente[i] = -1;
        visitado[i] = 0;
    }

    estimativa[vertice_partida] = 0;
    int atual = vertice_partida;

    for (int i = 0; i < qtd_vertice; i++){
        if (atual == vertice_destino){
            break;
        }

        for (int j = 0; j < qtd_vertice; j++){
            if (matriz[atual][j] != 0 && visitado[j] == 0){
                int nova_estimativa = estimativa[atual] + matriz[atual][j];

                if (nova_estimativa < estimativa[j]){
                    estimativa[j] = nova_estimativa;
                    precedente[j] = atual;
                }
            }
        }

        visitado[atual] = 1;

        int menor = infinito;
        int proximo = -1;

        for (int j = 0; j < qtd_vertice; j++){
            if (visitado[j] == 0 && estimativa[j] != infinito){
                int f = estimativa[j] + heuristica[j];

                if (f < menor){
                    menor = f;
                    proximo = j;
                }
            }
        }

        if (proximo == -1){
            break;
        }

        atual = proximo;
    }


}
*/
void alg_aestrela (int vertice_partida, int vertice_destino, int qtd_vertice, int *estimativa, int **matriz, int *heuristica)
{
    int f[qtd_vertice];
    int visitado[qtd_vertice];
    int infinito = 9999999;

    // Inicializa os vetores
    for (int i = 0; i < qtd_vertice; i++) {
        estimativa[i] = infinito;
        f[i] = infinito;
        visitado[i] = 0;
    }

    // Vértice inicial
    estimativa[vertice_partida] = 0;
    f[vertice_partida] = heuristica[vertice_partida];

    while (1) {

        int atual = -1;
        int menor_f = infinito;

        // Escolhe o vértice com menor f(n)
        for (int i = 0; i < qtd_vertice; i++) {

            if (visitado[i] == 0 && f[i] < menor_f) {
                menor_f = f[i];
                atual = i;
            }
        }

        // Não existe mais caminho
        if (atual == -1) {
            break;
        }

        // Chegou ao destino
        if (atual == vertice_destino) {
            break;
        }

        visitado[atual] = 1;

        // Analisa os vizinhos
        for (int i = 0; i < qtd_vertice; i++) {

            if (matriz[atual][i] != 0 && visitado[i] == 0) {

                // Calcula o novo custo real g(n)
                int nova_estimativa =
                    estimativa[atual] + matriz[atual][i];

                // Encontrou um caminho melhor
                if (nova_estimativa < estimativa[i]) {

                    // Guarda o custo real no vetor resultado
                    estimativa[i] = nova_estimativa;

                    // Calcula f(n) = g(n) + h(n)
                    f[i] = estimativa[i] + heuristica[i];
                }
            }
        }
    }
}