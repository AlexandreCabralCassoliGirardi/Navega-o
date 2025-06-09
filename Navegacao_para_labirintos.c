#include <stdio.h>
#include <stdlib.h>

#define LINHAS 5
#define COLUNAS 5
#define MAX_VERTICES (LINHAS * COLUNAS)

typedef struct No {
    int destino;
    struct No* prox;
} No;

No* adj[MAX_VERTICES];
int visitado_bfs[MAX_VERTICES];
int visitado_dfs[MAX_VERTICES];

typedef struct {
    int itens[MAX_VERTICES];
    int frente, tras;
} Fila;

void inicializarFila(Fila* f) {
    f->frente = -1;
    f->tras = -1;
}

int filaVazia(Fila* f) {
    return f->frente == -1;
}

void enfileirar(Fila* f, int valor) {
    if (f->tras == MAX_VERTICES - 1) return;
    if (f->frente == -1) f->frente = 0;
    f->tras++;
    f->itens[f->tras] = valor;
}

int desenfileirar(Fila* f) {
    int valor = -1;
    if (filaVazia(f)) return valor;
    valor = f->itens[f->frente++];
    if (f->frente > f->tras)
        f->frente = f->tras = -1;
    return valor;
}

int coordenada_para_indice(int x, int y) {
    return x * COLUNAS + y;
}

void adicionarAresta(int u, int v) {
    No* novo = malloc(sizeof(No));
    novo->destino = v;
    novo->prox = adj[u];
    adj[u] = novo;
}

void construirListaAdjacencia(int lab[LINHAS][COLUNAS]) {
    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};

    for (int x = 0; x < LINHAS; x++) {
        for (int y = 0; y < COLUNAS; y++) {
            if (lab[x][y] == 1) {
                int u = coordenada_para_indice(x, y);
                for (int i = 0; i < 4; i++) {
                    int nx = x + dx[i];
                    int ny = y + dy[i];
                    if (nx >= 0 && ny >= 0 && nx < LINHAS && ny < COLUNAS && lab[nx][ny] == 1) {
                        int v = coordenada_para_indice(nx, ny);
                        adicionarAresta(u, v);
                    }
                }
            }
        }
    }
}

void BFS(int inicio, int destino) {
    Fila f;
    inicializarFila(&f);
    enfileirar(&f, inicio);
    visitado_bfs[inicio] = 1;

    while (!filaVazia(&f)) {
        int atual = desenfileirar(&f);
        printf("%d ", atual);
        if (atual == destino) {
            printf("\nChegou ao destino!\n");
            return;
        }
        No* viz = adj[atual];
        while (viz) {
            if (!visitado_bfs[viz->destino]) {
                enfileirar(&f, viz->destino);
                visitado_bfs[viz->destino] = 1;
            }
            viz = viz->prox;
        }
    }
    printf("\nSem caminho até o destino.\n");
}

void DFS(int atual, int destino) {
    visitado_dfs[atual] = 1;
    printf("%d ", atual);

    if (atual == destino) {
        printf("\nChegou ao destino!\n");
        return;
    }

    No* viz = adj[atual];
    while (viz) {
        if (!visitado_dfs[viz->destino]) {
            DFS(viz->destino, destino);
        }
        viz = viz->prox;
    }
}

int main() {
    int labirinto[LINHAS][COLUNAS] = {
        {1, 0, 1, 1, 1},
        {1, 0, 1, 0, 1},
        {1, 1, 1, 0, 1},
        {0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1}
    };

    construirListaAdjacencia(labirinto);

    int origem = coordenada_para_indice(0, 0);
    int destino = coordenada_para_indice(LINHAS - 1, COLUNAS - 1);

    printf("BUSCA EM LARGURA\n");
    BFS(origem, destino);

    printf("\n EM PROFUNDIDADE\n");
    DFS(origem, destino);

    return 0;
}
