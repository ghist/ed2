#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <time.h>

#define V 6 // número de vértices no grafo

int minDistance(int dist[], bool sptSet[]) {
   int min = INT_MAX, min_index;
   for (int v = 0; v < V; v++)
     if (sptSet[v] == false && dist[v] <= min)
         min = dist[v], min_index = v;
   return min_index;
}

void dijkstra(int graph[V][V], int src) {
     int dist[V];
     bool sptSet[V];

     for (int i = 0; i < V; i++)
        dist[i] = INT_MAX, sptSet[i] = false;

     dist[src] = 0;
     
     clock_t start_time = clock(); // marca o início da execução

     for (int count = 0; count < V-1; count++) {
       int u = minDistance(dist, sptSet);
       sptSet[u] = true;
       for (int v = 0; v < V; v++)
         if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX 
                                       && dist[u]+graph[u][v] < dist[v])
            dist[v] = dist[u] + graph[u][v];
     }
     
     clock_t end_time = clock(); // marca o fim da execução

     printf("Distância mínima do nó %d para todos os outros nós:\n", src);
     for (int i = 0; i < V; i++)
        printf("%d -> %d\n", i, dist[i]);
        
    printf("Tempo de execução: %.10f segundos\n", (double)(end_time - start_time) / CLOCKS_PER_SEC);
}

int main() {
    int graph[V][V] = { { 0, 12, 4, 0, 0, 0 },
						{ 0, 0, 6, 6, 0, 0 },
						{ 0, 10, 0, 2, 2, 0 },
						{ 0, 0, 8, 0, 0, 6 },
						{ 0, 2, 0, 0, 0, 6 },
						{ 0, 0, 0, 0, 0, 0 } };

    dijkstra(graph, 0);

    return 0;
}


// entrada questao 4
//						{ 0, 6, 8, 10, 0, 0, 0, 0, 0, 0},
//						{ 6, 0, 12, 14, 18, 0, 0, 0, 0, 0 },
//						{ 8, 12, 0, 22, 24, 28, 30, 0, 0, 0 },
//						{ 10, 14, 22, 0, 18, 16, 14, 0, 0, 0 },
//						{ 0, 18, 24, 18, 0, 38, 40, 46, 52, 0 },
//						{ 0, 0, 28, 16, 38, 0, 54, 58, 60, 62 },
//						{ 0, 0, 30, 24, 40, 54, 0, 80, 82, 84},
//						{ 0, 0, 0, 0, 46, 58, 80, 0, 100, 110},
//						{ 0, 0, 0, 0, 52, 60, 82, 100, 0, 120},
//						{ 0, 0, 0, 0, 0, 62, 84, 110, 120, 0} };

