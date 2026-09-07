#ifndef METODOS_DE_PESQUISA
#define METODOS_DE_PESQUISA

//=========================BUSCAS NO GRAFO======================

void pesquisa_DFS(int qtd_vertice, int **matriz, int *vet_visitado, int vertice_inicio, int *vet_ordem);

void pesquisa_BFS(int qtd_vertice, int **matriz, int *vet_visitado, int vertice_inicio, int *vet_ordem);

//=========================FECHO TRANSITIVO======================

void fecho_transitivo_direto(int qtd_vertice, int **matriz, int vertice_inicio, int *vet_fecho);

void fecho_transitivo_inverso(int qtd_vertice, int **matriz, int vertice_inicio, int *vet_fecho);

//=========================MANIPULAÇÃO E IMPRESSÃO DO GRAFO======================

void print_matriz(int qtd_vertice, int **matriz);

int mod_remove(int qtd_vertice, int **matriz, int vertice_origem, int vertice_destino, int mod);

int mod_add(int qtd_vertice, int **matriz, int vertice_origem, int vertice_destino, int mod);

int** alocar_matriz(int n);

void liberar_matriz(int **matriz, int n);

int** adicionar_vertice(int *qtd_vertice, int **matriz);

int** remover_vertice(int *qtd_vertice, int **matriz, int vertice_remover);

//=========================CONEXIDADE E SUBGRAFOS======================

void verificar_conexidade_e_sfc(int qtd_vertice, int **matriz);

#endif