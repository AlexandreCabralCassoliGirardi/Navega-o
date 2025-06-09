#include <stdio.h>
#include <limits.h>

#define V 6

int minDistancia(int dist[], int visitado[]) {
    int min = INT_MAX, min_index = -1;
    for (int v = 0; v < V; v++) {
        if (!visitado[v] && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }
    return min_index;
}

void dijkstra(int grafo[V][V], int origem, int destino) {
    int dist[V];
    int visitado[V];
    int anterior[V];

    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        visitado[i] = 0;
        anterior[i] = -1;
    }

    dist[origem] = 0;

    for (int count = 0; count < V - 1; count++) {
        int u = minDistancia(dist, visitado);
        if (u == -1) break;
        visitado[u] = 1;
        for (int v = 0; v < V; v++) {
            if (!visitado[v] && grafo[u][v] && dist[u] != INT_MAX &&
                dist[u] + grafo[u][v] < dist[v]) {
                dist[v] = dist[u] + grafo[u][v];
                anterior[v] = u;
            }
        }
    }

    if (dist[destino] == INT_MAX) {
        printf("\nNão há rota possível entre %d e %d.\n", origem, destino);
    } else {
        printf("\nTempo mínimo de viagem entre %d e %d: %d minutos\n", origem, destino, dist[destino]);
        printf("Caminho: ");
        int caminho[V];
        int tam = 0;
        for (int at = destino; at != -1; at = anterior[at]) {
            caminho[tam++] = at;
        }
        for (int i = tam - 1; i >= 0; i--) {
            printf("%d", caminho[i]);
            if (i > 0) printf(" -> ");
        }
        printf("\n");
    }
}

int main() {
    int grafo[V][V] = {
        { 0, 7, 9, 0, 0, 14},
        { 0, 0, 10,15, 0, 0 },
        { 0, 0, 0, 11, 0, 2  },
        { 0, 0, 0, 0, 6, 0  },
        { 0, 0, 0, 0, 0, 9  },
        { 0, 0, 0, 0, 0, 0  }
    };

    int origem, destino;
    printf("Sistema de Rotas de Transporte Público\n");
    printf("Número de paradas: %d (identificadas de 0 a %d)\n", V, V - 1);

    printf("Digite o ponto de partida (0 a %d): ", V - 1);
    scanf("%d", &origem);
    printf("Digite o ponto de destino (0 a %d): ", V - 1);
    scanf("%d", &destino);

    if (origem < 0 || origem >= V || destino < 0 || destino >= V) {
        printf("Entradas inválidas. Use apenas números entre 0 e %d.\n", V - 1);
        return 1;
    }

    dijkstra(grafo, origem, destino);

    return 0;
}
