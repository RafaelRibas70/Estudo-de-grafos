#include <stdio.h>
#include <stdlib.h>

#include "estrutura_dados.h"
#include "metodos_pesquisa.h"

int main() {
    int vertices = 0;
    printf("Quantos vertices? ");
    scanf("%d", &vertices);

    int **matriz = alocar_matriz(vertices);
    int **matriz_valorada = alocar_matriz(vertices);

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

    int valor_vertice = 0;
    int cont_conexao = 1;
    while (1) {
        int origem = 0, destino = 0;
        printf("Conexao %d (origem / destino / valor_da_conexao): ", cont_conexao);
        scanf("%d", &origem);

        if (origem == -1) {
            printf("Encerrando insercao de conexoes.\n");
            break;
        }

        scanf("%d", &destino);
        scanf("%d", &valor_vertice);

        if (origem > vertices || origem < 1 || destino > vertices || destino < 1) {
            printf("Escolha fora dos limites (1 a %d), tente novamente.\n", vertices);
        } else {
            int mod = (escolha_tipo == 1) ? 1 : 2;
            mod_add(vertices, matriz, origem, destino, mod, 1);
            mod_add(vertices, matriz_valorada, origem, destino, mod, valor_vertice);
            cont_conexao++;
        }
    }



    int opcao = -1;
    while (opcao != 7) {
        printf("\n--- MENU ---\n");
        printf("0 - Alterar o grafo\n");
        printf("1 - Buscar por Profundidade (DFS)\n");
        printf("2 - Buscar por Largura (BFS)\n");
        printf("3 - Visualizar fecho transitivo direto\n");
        printf("4 - Visualizar fecho transitivo inverso\n");
        printf("5 - Verificar conexidade e SFC\n");
        printf("6 - Colorir grafo\n");
        printf("7 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 0: {
                int opcao_mod;
                printf("\n0-Remover vertice\n1-Remover aresta\n2-Remover arco\n3-Adicionar vertice\n4-Adicionar aresta\n5-Adicionar arco\nOpcao: ");
                scanf("%d", &opcao_mod);

                switch (opcao_mod) {
                    case 0: {
                        printf("Vertice a remover (1 a %d): ", vertices);
                        int v;
                        scanf("%d", &v);
                        matriz = remover_vertice(&vertices, matriz, v);
                        if (matriz != NULL) print_matriz(vertices, matriz);
                        break;
                    }
                    case 1: {
                        printf("Origem e destino: ");
                        int o, d;
                        scanf("%d %d", &o, &d);
                        mod_remove(vertices, matriz, o, d, 2);
                        print_matriz(vertices, matriz);
                        break;
                    }
                    case 2: {
                        printf("Origem e destino: ");
                        int o, d;
                        scanf("%d %d", &o, &d);
                        mod_remove(vertices, matriz, o, d, 1);
                        print_matriz(vertices, matriz);
                        break;
                    }
                    case 3: {
                        matriz = adicionar_vertice(&vertices, matriz);
                        print_matriz(vertices, matriz);
                        break;
                    }
                    case 4: {
                        printf("Origem e destino: ");
                        int o, d, valor=1;
                        scanf("%d %d %d", &o, &d, &valor);
                        mod_add(vertices, matriz, o, d, 2, valor);
                        print_matriz(vertices, matriz);
                        break;
                    }
                    case 5: {
                        printf("Origem e destino: ");
                        int o, d, valor=1;
                        scanf("%d %d %d", &o, &d, &valor);
                        mod_add(vertices, matriz, o, d, 1, valor);
                        print_matriz(vertices, matriz);
                        break;
                    }
                    
                    default:
                        printf("Opcao de alteracao invalida!\n");
                        break;
                }
                break;
            }

            case 1: {
                printf("Vertice inicial (1 a %d): ", vertices);
                int ini;
                scanf("%d", &ini);

                int *visitado = calloc(vertices, sizeof(int));
                int *ordem = calloc(vertices, sizeof(int));

                pesquisa_DFS(vertices, matriz, visitado, ini, ordem);

                printf("DFS: ");
                for (int i = 0; i < vertices; i++) {
                    if (ordem[i] != 0) printf("%d ", ordem[i]);
                }
                printf("\n");

                free(visitado);
                free(ordem);
                break;
            }

            case 2: {
                printf("Vertice inicial (1 a %d): ", vertices);
                int ini;
                scanf("%d", &ini);

                int *visitado = calloc(vertices, sizeof(int));
                int *ordem = calloc(vertices, sizeof(int));

                pesquisa_BFS(vertices, matriz, visitado, ini, ordem);

                printf("BFS: ");
                for (int i = 0; i < vertices; i++) {
                    if (ordem[i] != 0) printf("%d ", ordem[i]);
                }
                printf("\n");

                free(visitado);
                free(ordem);
                break;
            }

            case 3: {
                printf("Vertice (1 a %d): ", vertices);
                int v;
                scanf("%d", &v);

                int *fecho = calloc(vertices, sizeof(int));
                fecho_transitivo_direto(vertices, matriz, v, fecho);

                printf("Fecho Direto do %d: { ", v);
                for (int i = 0; i < vertices; i++) {
                    if (fecho[i] == 1) printf("%d ", i + 1);
                }
                printf("}\n");

                free(fecho);
                break;
            }

            case 4: {
                printf("Vertice (1 a %d): ", vertices);
                int v;
                scanf("%d", &v);

                int *fecho = calloc(vertices, sizeof(int));
                fecho_transitivo_inverso(vertices, matriz, v, fecho);

                printf("Fecho Inverso do %d: { ", v);
                for (int i = 0; i < vertices; i++) {
                    if (fecho[i] == 1) printf("%d ", i + 1);
                }
                printf("}\n");

                free(fecho);
                break;
            }

            case 5:
                verificar_conexidade_e_sfc(vertices, matriz);
                break;

            case 6: {
                int *resultado = calloc(vertices, sizeof(int));
                int *ordem_pintura = calloc(vertices, sizeof(int));

                if (resultado == NULL) {
                    printf("Erro ao alocar memoria para a coloracao.\n");
                    break;
                }

                // Realiza a coloracao do grafo
                colorir_matriz(vertices, resultado, matriz, ordem_pintura);

                // Exibe a cor de cada vertice
                printf("\n--- Coloracao do Grafo ---\n");

                for (int i = 0; i < vertices; i++) {
                    printf("Vertice %d: Cor %d\n", i + 1, resultado[i]);
                }
                printf("\nOrdem de coloracao:\n");
                for (int i = 0; i < vertices; i++) {
                    printf("%d ", ordem_pintura[i]);
                }
                printf("\n");

                // Cria o arquivo com os dados do grafo
                FILE *arquivo = fopen("grafo.txt", "w");

                if (arquivo == NULL) {
                    printf("Erro ao criar o arquivo grafo.txt.\n");
                } else {
                    // Quantidade de vertices
                    fprintf(arquivo, "vertices: %d\n", vertices);

                    // Informa se o grafo e direcionado
                    fprintf(arquivo, "directed: %s\n",
                            escolha_tipo == 1 ? "true" : "false");

                    // Salva as cores dos vertices
                    fprintf(arquivo, "colors:");

                    for (int i = 0; i < vertices; i++) {
                        fprintf(arquivo, " %d", resultado[i]);
                    }

                    fprintf(arquivo, "\nedges:\n");

                    // Salva as ligacoes existentes no grafo
                    for (int i = 0; i < vertices; i++) {
                        for (int j = 0; j < vertices; j++) {
                            if (matriz[i][j] != 0) {

                                // Evita duplicar arestas em grafos nao direcionados
                                if (escolha_tipo == 1 || i <= j) {
                                    fprintf(arquivo, "%d %d\n", i + 1, j + 1);
                                }
                            }
                        }
                    }

                    fclose(arquivo);

                    printf("\nGrafo exportado para grafo.txt.\n");
                    printf("Abrindo o desenho do grafo...\n");

                    // Executa o script Python
                    int erro = system("python desenhar_grafo_colorido.py");

                    if (erro != 0) {
                        printf("Erro ao executar o Python.\n");
                        printf("Verifique se o Python esta instalado e configurado.\n");
                    }
                }

                // Libera a memoria utilizada
                free(resultado);

                break;
            }

            case 7:
                printf("Saindo...\n");
                break;

            default:
                printf("Opcao invalida!\n");
                break;
        }
    }

    if (matriz != NULL) {
        liberar_matriz(matriz, vertices);
    }

    return 0;
}