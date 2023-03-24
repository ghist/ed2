#include <stdio.h>
#include <limits.h>
#include <time.h>

#define MAX_VERTICES 100

int dist[MAX_VERTICES][MAX_VERTICES]; // matriz de distâncias
int n; // número de vértices do grafo

void floyd_warshall() {
    int i, j, k;
    
    // inicializa a matriz de distâncias
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            scanf("%d", &dist[i][j]);
        }
    }
    
    clock_t start_time = clock(); // marca o início da execução
    
    // executa o algoritmo
    for (k = 0; k < n; k++) {
        for (i = 0; i < n; i++) {
            for (j = 0; j < n; j++) {
                if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX
                    && dist[i][j] > dist[i][k] + dist[k][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }
    
    clock_t end_time = clock(); // marca o fim da execução
    
    printf("Tempo de execução: %.10f segundos\n", (double)(end_time - start_time) / CLOCKS_PER_SEC);
}

int main() {
    scanf("%d", &n);
    floyd_warshall();
    
    // imprime a matriz de distâncias resultante
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            printf("%d ", dist[i][j]);
        }
        printf("\n");
    }
    
    return 0;
}

