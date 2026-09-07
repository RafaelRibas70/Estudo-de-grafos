#include <stdio.h>
#include <stdlib.h>

#include "estrutura_dados.h"
#include "metodos_pesquisa.h"

int main() {
    int n = 0;
    printf("Quantos vertices? ");
    scanf("%d", &n);

    int **matriz = alocar_matriz(n);

    int escolha_tipo;
    do {
        printf("Qual o tipo de ligacao? \n1-arco (dirigido)\n2-aresta (nao dirigido)\n");
        scanf("%d", &escolha_tipo);
        if (escolha_tipo != 1 && escolha_tipo != 2) {
            printf("Escolha incorreta, tente novamente.\n");
        }
    } while (escolha_tipo != 1 && escolha_tipo != 2);

    printf("\n--- Coleta de Conexoes ---\n");
    printf("Digite a Origem e o Destino (ex: 1 2).\n");
    printf("Para finalizar a insercao, digite -1 no valor da origem.\n\n");

    int cont_conexao = 1;
    while (1) {
        int origem = 0, destino = 0;
        printf("Conexao %d (origem destino): ", cont_conexao);
        scanf("%d", &origem);

        if (origem == -1) {
            printf("Encerrando insercao de conexoes.\n");
            break;
        }

        scanf("%d", &destino);

        if (origem > n || origem < 1 || destino > n || destino < 1) {
            printf("Escolha fora dos limites (1 a %d), tente novamente.\n", n);
        } else {
            int mod = (escolha_tipo == 1) ? 2 : 1;
            mod_add(n, matriz, origem, destino, mod);
            cont_conexao++;
        }
    }

    printf("\nSua matriz de adjacencia:\n");
    print_matriz(n, matriz);

    int opcao = -1;
    while (opcao != 6) {
        printf("\n--- MENU ---\n");
        printf("0 - Alterar o grafo\n");
        printf("1 - Buscar por Profundidade (DFS)\n");
        printf("2 - Buscar por Largura (BFS)\n");
        printf("3 - Visualizar fecho transitivo direto\n");
        printf("4 - Visualizar fecho transitivo inverso\n");
        printf("5 - Verificar conexidade e SFC\n");
        printf("6 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 0: {
                int opcao_mod;
                printf("\n0-Remover vertice\n1-Remover aresta\n2-Remover arco\n3-Adicionar vertice\n4-Adicionar aresta\n5-Adicionar arco\nOpcao: ");
                scanf("%d", &opcao_mod);

                switch (opcao_mod) {
                    case 0: {
                        printf("Vertice a remover (1 a %d): ", n);
                        int v;
                        scanf("%d", &v);
                        matriz = remover_vertice(&n, matriz, v);
                        if (matriz != NULL) print_matriz(n, matriz);
                        break;
                    }
                    case 1: {
                        printf("Origem e destino: ");
                        int o, d;
                        scanf("%d %d", &o, &d);
                        mod_remove(n, matriz, o, d, 1);
                        print_matriz(n, matriz);
                        break;
                    }
                    case 2: {
                        printf("Origem e destino: ");
                        int o, d;
                        scanf("%d %d", &o, &d);
                        mod_remove(n, matriz, o, d, 2);
                        print_matriz(n, matriz);
                        break;
                    }
                    case 3: {
                        matriz = adicionar_vertice(&n, matriz);
                        print_matriz(n, matriz);
                        break;
                    }
                    case 4: {
                        printf("Origem e destino: ");
                        int o, d;
                        scanf("%d %d", &o, &d);
                        mod_add(n, matriz, o, d, 1);
                        print_matriz(n, matriz);
                        break;
                    }
                    case 5: {
                        printf("Origem e destino: ");
                        int o, d;
                        scanf("%d %d", &o, &d);
                        mod_add(n, matriz, o, d, 2);
                        print_matriz(n, matriz);
                        break;
                    }
                    default:
                        printf("Opcao de alteracao invalida!\n");
                        break;
                }
                break;
            }

            case 1: {
                printf("Vertice inicial (1 a %d): ", n);
                int ini;
                scanf("%d", &ini);

                int *visitado = calloc(n, sizeof(int));
                int *ordem = calloc(n, sizeof(int));

                pesquisa_DFS(n, matriz, visitado, ini, ordem);

                printf("DFS: ");
                for (int i = 0; i < n; i++) {
                    if (ordem[i] != 0) printf("%d ", ordem[i]);
                }
                printf("\n");

                free(visitado);
                free(ordem);
                break;
            }

            case 2: {
                printf("Vertice inicial (1 a %d): ", n);
                int ini;
                scanf("%d", &ini);

                int *visitado = calloc(n, sizeof(int));
                int *ordem = calloc(n, sizeof(int));

                pesquisa_BFS(n, matriz, visitado, ini, ordem);

                printf("BFS: ");
                for (int i = 0; i < n; i++) {
                    if (ordem[i] != 0) printf("%d ", ordem[i]);
                }
                printf("\n");

                free(visitado);
                free(ordem);
                break;
            }

            case 3: {
                printf("Vertice (1 a %d): ", n);
                int v;
                scanf("%d", &v);

                int *fecho = calloc(n, sizeof(int));
                fecho_transitivo_direto(n, matriz, v, fecho);

                printf("Fecho Direto do %d: { ", v);
                for (int i = 0; i < n; i++) {
                    if (fecho[i] == 1) printf("%d ", i + 1);
                }
                printf("}\n");

                free(fecho);
                break;
            }

            case 4: {
                printf("Vertice (1 a %d): ", n);
                int v;
                scanf("%d", &v);

                int *fecho = calloc(n, sizeof(int));
                fecho_transitivo_inverso(n, matriz, v, fecho);

                printf("Fecho Inverso do %d: { ", v);
                for (int i = 0; i < n; i++) {
                    if (fecho[i] == 1) printf("%d ", i + 1);
                }
                printf("}\n");

                free(fecho);
                break;
            }

            case 5:
                verificar_conexidade_e_sfc(n, matriz);
                break;

            case 6:
                printf("Saindo...\n");
                break;

            default:
                printf("Opcao invalida!\n");
                break;
        }
    }

    if (matriz != NULL) {
        liberar_matriz(matriz, n);
    }

    return 0;
}