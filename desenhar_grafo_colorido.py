
import matplotlib.pyplot as plt
import networkx as nx


def ler_grafo(nome_arquivo="grafo.txt"):
    with open(nome_arquivo, "r", encoding="utf-8") as arquivo:
        linhas = [linha.strip() for linha in arquivo if linha.strip()]

    vertices = int(linhas[0].split(":")[1].strip())
    direcionado = linhas[1].split(":")[1].strip().lower() == "true"

    cores = list(map(int, linhas[2].split(":")[1].split()))

    indice_arestas = next(
        i for i, linha in enumerate(linhas)
        if linha.lower() == "edges:"
    )

    ligacoes = []
    for linha in linhas[indice_arestas + 1:]:
        dados = linha.split()
        origem = int(dados[0])
        destino = int(dados[1])
        ligacoes.append((origem, destino))

    return vertices, direcionado, cores, ligacoes


def desenhar_grafo():
    vertices, direcionado, cores, ligacoes = ler_grafo()

    # Cria o grafo
    G = nx.DiGraph() if direcionado else nx.Graph()
    G.add_nodes_from(range(1, vertices + 1))
    G.add_edges_from(ligacoes)

    # Paleta de cores para os vertices
    paleta = [
        "#66c2a5", "#fc8d62", "#8da0cb", "#e78ac3",
        "#a6d854", "#ffd92f", "#e5c494", "#b3b3b3",
        "#80b1d3", "#fb8072"
    ]

    # Associa uma cor a cada vertice
    cores_vertices = [
        paleta[(cor - 1) % len(paleta)] if cor > 0 else "#ffffff"
        for cor in cores
    ]

    # Organiza a posicao dos vertices
    pos = nx.spring_layout(G, seed=42)

    # Reserva espaco na parte inferior para a legenda
    fig, ax = plt.subplots(figsize=(9, 7))

    # Desenha as ligacoes
    if direcionado:
        nx.draw_networkx_edges(
            G, pos, ax=ax, edge_color="gray",
            arrows=True, arrowsize=20
        )
    else:
        nx.draw_networkx_edges(
            G, pos, ax=ax, edge_color="gray"
        )

    # Desenha os vertices coloridos
    nx.draw_networkx_nodes(
        G, pos, ax=ax,
        node_color=cores_vertices,
        node_size=1500,
        edgecolors="black",
        linewidths=1.5
    )

    # Escreve o numero de cada vertice dentro dele
    rotulos = {v: str(v) for v in G.nodes()}
    nx.draw_networkx_labels(
        G, pos, labels=rotulos, ax=ax,
        font_size=12, font_weight="bold",
        font_color="black"
    )

    # Cria uma legenda apenas para as cores realmente utilizadas
    cores_usadas = sorted(set(cores))
    elementos_legenda = []

    for cor in cores_usadas:
        if cor <= 0:
            continue

        elementos_legenda.append(
            plt.Line2D(
                [0], [0],
                marker="o",
                color="w",
                label=f"Cor {cor}",
                markerfacecolor=paleta[(cor - 1) % len(paleta)],
                markeredgecolor="black",
                markersize=10
            )
        )

    if elementos_legenda:
        fig.legend(
            handles=elementos_legenda,
            title="Legenda das cores",
            loc="lower center",
            ncol=min(len(elementos_legenda), 5),
            frameon=True,
            bbox_to_anchor=(0.5, 0.02)
        )

    ax.set_title("Coloracao do Grafo", fontsize=15)
    ax.axis("off")

    # Deixa espaco para a legenda na parte inferior
    plt.tight_layout(rect=[0, 0.13, 1, 0.95])

    plt.show()


if __name__ == "__main__":
    desenhar_grafo()
