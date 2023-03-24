#include <stdio.h>
#include <limits.h>

#define INF INT_MAX // Valor para representar infinito

// Estrutura para representar uma aresta do grafo
struct Edge {
    int src, dest, weight;
};

// Estrutura para representar o grafo
struct Graph {
    int V, E;
    struct Edge* edges;
};

// Função para inicializar o grafo
struct Graph* createGraph(int V, int E) {
    struct Graph* graph = (struct Graph*) malloc(sizeof(struct Graph));
    graph->V = V;
    graph->E = E;
    graph->edges = (struct Edge*) malloc(E * sizeof(struct Edge));
    return graph;
}

// Função para relaxar uma aresta
void relax(int u, int v, int weight, int dist[]) {
    if (dist[u] != INF && dist[v] > dist[u] + weight) {
        dist[v] = dist[u] + weight;
    }
}

// Função para encontrar o menor caminho a partir da origem
void bellmanFord(struct Graph* graph, int src, int dist[]) {
    // Inicializa a distância de todos os vértices como infinito
    for (int i = 0; i < graph->V; i++) {
        dist[i] = INF;
    }

    // A distância da origem para ela mesma é sempre 0
    dist[src] = 0;

    // Relaxa todas as arestas V - 1 vezes
    for (int i = 1; i <= graph->V - 1; i++) {
        for (int j = 0; j < graph->E; j++) {
            int u = graph->edges[j].src;
            int v = graph->edges[j].dest;
            int weight = graph->edges[j].weight;
            relax(u, v, weight, dist);
        }
    }
}

int main() {
    // Exemplo de grafo
    int V = 6;
    int E = 11;
    struct Graph* graph = createGraph(V, E);
    graph->edges[0].src = 0;
    graph->edges[0].dest = 1;
    graph->edges[0].weight = 12;
    
    graph->edges[1].src = 0;
    graph->edges[1].dest = 2;
    graph->edges[1].weight = 4;
    
    graph->edges[2].src = 1;
    graph->edges[2].dest = 2;
    graph->edges[2].weight = 6;
    
    graph->edges[3].src = 1;
    graph->edges[3].dest = 3;
    graph->edges[3].weight = 6;
    
    graph->edges[4].src = 2;
    graph->edges[4].dest = 1;
    graph->edges[4].weight = 10;
    
    graph->edges[5].src = 2;
    graph->edges[5].dest = 3;
    graph->edges[5].weight = 2;
    
    graph->edges[6].src = 2;
    graph->edges[6].dest = 4;
    graph->edges[6].weight = 2;
    
    graph->edges[7].src = 3;
    graph->edges[7].dest = 2;
    graph->edges[7].weight = 8;
    
    graph->edges[8].src = 3;
    graph->edges[8].dest = 5;
    graph->edges[8].weight = 6;
    
    graph->edges[9].src = 4;
    graph->edges[9].dest = 1;
    graph->edges[9].weight = 2;
    
    graph->edges[10].src = 4;
    graph->edges[10].dest = 5;
    graph->edges[10].weight = 6;

    // Executa o algoritmo de Bellman-Ford a partir do vértice 0
    int dist[V];
    bellmanFord(graph, 0, dist);

    // Imprime as distâncias mínimas a partir da origem
    for (int i = 0; i < V; i++) {
        printf("Distância mínima do vértice %d para a origem: %d\n", i, dist[i]);
    }

    return 0;
}

