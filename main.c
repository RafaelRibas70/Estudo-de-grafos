#include <stdio.h>
#include <stdbool.h>

#include "grafo.h"

int main(){
  printf("Quantas vértices?");
  int n;
  scanf("%d", &n);

  int matriz[n][n];
  for (int i = 0; i < n; i++){
    for (int j = 0; j < n; j++){
      matriz[i][j] = 0;
    }
  }
  int matriz_mod_r[n-1][n-1]; //matriz para remover vertice

  printf("Quantas conexões?");
  int con;
  scanf("%d", &con);

  int escolha_tipo;
  do{
    printf("Qual o tipo de ligação? \n1-arco\n2-aresta\n");
    scanf("%d", &escolha_tipo);
      if(escolha_tipo!=1&& escolha_tipo!=2){
        printf("Escolha errada, tente novamente\n");
      }
  }while(escolha_tipo!=1 && escolha_tipo!=2);

  if(escolha_tipo==1){
    for (int i = 0; i < con; i++) {
      printf("Conexao: origem-destino: ");
      int origem = 0, destino = 0;
      scanf("%d %d", &origem, &destino);
      if(origem > n || origem < 1 || destino > n|| destino < 1){
        printf("Escolha fora dos limites, tente novamente\n");
        i--;
      }else{
        matriz[origem - 1][destino - 1] = 1;
      }
    }
  }else{
    for (int i = 0; i < con; i++) {
      printf("Conexao: origem-destino: ");
      int origem = 0, destino = 0;
      scanf("%d %d", &origem, &destino);
      if(origem > n || origem < 1 || destino > n|| destino < 1){
        printf("Escolha fora dos limites, tente novamente\n");
        i--;
      }else{
        matriz[origem - 1][destino - 1] = 1;
        matriz[destino - 1][origem - 1] = 1;
      }
    }
  }

  printf("\nSua matriz:\n");
  print_matriz(n, matriz);

  bool terminar = false;
  while(!terminar){
    int opcao;
    int mod;

    printf("--- MENU ---\n");
    printf("0 - Alterar o grafo\n");
    printf("1 - Buscar por Profundidade (DFS)\n");
    printf("2 - Buscar por Largura (BFS)\n");
    printf("3 - Visualizar fecho transitivo direto\n");
    printf("4 - Visualizar fecho transitivo indireto\n");
    printf("5 - Verificar se o grafo é conexo\n");
    printf("Digite sua escolha: ");
    scanf("%d", &opcao);
    printf("\n");

    int fecho[n][n]; //uma nova matriz para fazer o fecho direto
    int fecho_ind[n][n]; //mesma coisa so que pro indireto

    switch(opcao){
      // -- ALTERAR O GRAFO --
      case 0:
        int opcao_mod;
        printf("0 - Remover vértice\n1 - Remover aresta\n2 - Removar arco\n3 - Adicionar vértice\n4 - Adicionar aresta\n5 - Adicionar arco\n\n");
        scanf("%d", &opcao_mod);

        switch(opcao_mod){
          case 0: //ainda falta implementar
            printf("Escolheu remover vértice\n");
            printf("Digite qual vértice será removida: ");
            print_matriz(n, matriz);
          break;
          case 1:
            printf("Escolheu remover aresta.\nDigite origem-destino: ");
            int escolha_origem1; int escolha_destino1;
            mod = 1;
            scanf("%d %d", &escolha_origem1, &escolha_destino1);
            if(mod_remove(n, matriz, escolha_origem1, escolha_destino1, mod) == 0){ //remove aresta ou arco
              print_matriz(n, matriz);                                //printa a nova matriz do grafo
            }
          break;
          case 2:
            printf("Escolheu remover arco.\nDigite origem-destino: ");
            int escolha_origem2; int escolha_destino2;
            mod = 2;
            scanf("%d %d", &escolha_origem2, &escolha_destino2);
            if(mod_remove(n, matriz, escolha_origem2, escolha_destino2, mod) == 0){ //remove aresta ou arco
              print_matriz(n, matriz);                                //printa a nova matriz do grafo
            }
          break;
          case 3:
            printf("Escolheu adicionar vértice.\n");
            //ainda falta implementar
          break;
          case 4:
            printf("Escolheu adicionar aresta.\n");
            int escolha_origem3; int escolha_destino3;
            mod = 2;
            scanf("%d %d", &escolha_origem3, &escolha_destino3);
            if(mod_add(n, matriz, escolha_origem3, escolha_destino3, mod) == 0){ //adiciona aresta ou arco
              print_matriz(n, matriz);                                //printa a nova matriz do grafo
            }
          break;
          case 5:
            printf("Escolheu adicionar arco.\n");
            int escolha_origem4; int escolha_destino4;
            mod = 2;
            scanf("%d %d", &escolha_origem4, &escolha_destino4);
            if(mod_add(n, matriz, escolha_origem4, escolha_destino4, mod) == 0){ //adiciona aresta ou arco
              print_matriz(n, matriz);                                //printa a nova matriz do grafo
            }
          break;
        }
      break;
      case 1:{
        printf("Busca em profundidade:\n");
        int visitados_DFS[n];
        for (int i = 0; i < n; i++){
          visitados_DFS[i] = 0;
        }
        int visitados_BFS[n];
        for (int i = 0; i < n; i++){
          visitados_BFS[i] = 0;
        }

        printf("Escolha um nó inicial: ");
        int inicio;
        scanf("%d", &inicio);
        int atual = inicio;
        visitados_DFS[inicio - 1] = 1;
        visitados_BFS[inicio - 1] = 1;
        printf("\nVisitamos: %d\n", inicio);

        int topo = 0;
        int pilha[n + 1];
        pilha[topo++] = atual;

        bool parar_DFS = false;

        // PESQUISA DFS
        while (!parar_DFS) {
          //se a pilha estiver vazia procurar um novo nó não visitado
          if (topo == 0) {
            int novo = -1;
            for (int i = 0; i < n; i++) {
              if (!visitados_DFS[i]) { //tem que verificar se foi visitado um por um
                novo = i + 1;
                break;
              }
            }

            if (novo == -1) {
              parar_DFS = true;  //todos visitados
            }else {
              atual = novo;
              visitados_DFS[atual - 1] = 1;
              pilha[topo++] = atual;
              printf("Visitamos: %d\n", atual);
            }
          }

          //Percorre a linha no atual
          for (int j = 0; j < n; j++) {
            if (matriz[atual - 1][j] == 1) {
              if (!visitados_DFS[j]) {
                atual = j + 1;
                visitados_DFS[atual - 1] = 1;
                pilha[topo++] = atual;
                printf("Visitamos: %d\n", atual);
                j = 0; //recomeça pela linha do novo atual
              }
              //ignora se o j+1 ja foi visitado
            }
          }

          //quando percorre a linha e nao encontra nada, desempilha
          if (topo > 0) {
            //se eu coloco aqui topo = topo-- da falha seila pq
            atual = pilha[--topo];
          } else {
            //se a pilha zerou, o loop vai tentar encontrar um novo nó no início do while
          }

          //verifica se todos foram visitados
          int cont = 0;
          for (int i = 0; i < n; i++){
            if (visitados_DFS[i]) {
              cont++;
            }
            if (cont == n) {
              printf("Já visitamos tudo.\n\n");
              parar_DFS = true;
            }
          }
        }
      }
      break;
      case 2:
        printf("Busca em Largura:\n");
      break;
      case 3:{
        int origem;
        printf("Escolha o vértice de origem (1 a %d): ", n);
        scanf("%d", &origem);
        if (origem < 1 || origem > n) {
            printf("Vértice inválido!\n");
            break;
        }
        int origem_idx = origem - 1;

        // BFS para calcular distâncias mínimas
        int dist[n];
        for (int i = 0; i < n; i++) dist[i] = -1;  // -1 = inalcançável
        int fila[n];
        int frente = 0, tras = 0;

        dist[origem_idx] = 0;
        fila[tras++] = origem_idx;

        while (frente < tras) {
            int u = fila[frente++];
            for (int v = 0; v < n; v++) {
                if (matriz[u][v] == 1 && dist[v] == -1) {
                    dist[v] = dist[u] + 1;
                    fila[tras++] = v;
                }
            }
        }

        // Exibe a tabela
        printf("\nTabela de distâncias a partir do vértice %d:\n", origem);
        printf("Destino\tDistância\n");
        printf("----------------\n");
        for (int i = 0; i < n; i++) {
            printf("  %d\t", i + 1);
            if (dist[i] == -1)
                printf("  ∞\n");
            else
                printf("  %d\n", dist[i]);
        }

        // Grau de saída (número de vizinhos diretos)
        int grau = 0;
        for (int j = 0; j < n; j++) {
            if (matriz[origem_idx][j] == 1) grau++;
        }
        printf("\nΓ(%d) = %d\n", origem, grau);
      }
      break;
      case 4:{
        int vertice;
        printf("Escolha o vértice de referência (1 a %d): ", n);
        scanf("%d", &vertice);
        if (vertice < 1 || vertice > n) {
            printf("Vértice inválido!\n");
            break;
        }
        int v_idx = vertice - 1;

        // BFS reverso: partimos do vértice escolhido e "caminhamos para trás"
        // Ou seja, procuramos quais vértices têm aresta para o vértice atual.
        // Usamos a matriz transposta (colunas viram linhas).
        int dist[n];
        for (int i = 0; i < n; i++) dist[i] = -1;
        int fila[n];
        int frente = 0, tras = 0;

        dist[v_idx] = 0;  // O próprio vértice tem distância 0
        fila[tras++] = v_idx;

        while (frente < tras) {
            int u = fila[frente++];
            // Para cada vértice w que tem aresta para u (ou seja, matriz[w][u] == 1)
            for (int w = 0; w < n; w++) {
                if (matriz[w][u] == 1 && dist[w] == -1) {
                    dist[w] = dist[u] + 1;
                    fila[tras++] = w;
                }
            }
        }

        printf("\nTabela de distâncias (indireta) até o vértice %d:\n", vertice);
        printf("Vértice\tDistância (passos até %d)\n", vertice);
        printf("------------------------------------\n");
        for (int i = 0; i < n; i++) {
            printf("  %d\t", i + 1);
            if (dist[i] == -1)
                printf("  ∞ (não alcança %d)\n", vertice);
            else
                printf("  %d\n", dist[i]);
        }

        // Grau de proximidade indireta: quantos vértices alcançam o escolhido (distância finita)
        int cont = 0;
        for (int i = 0; i < n; i++) {
            if (dist[i] != -1 && i != v_idx) cont++;
        }
        printf("\nGrau de proximidade indireta de %d: %d vértices o alcançam\n", vertice, cont);
      }
      break;
    }
  }

  return 0;
}
