#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 30

typedef struct {
    int u, v, w;
} Edge;

int parent[MAX];

// Find function for Union-Find (with path compression)
int find_set(int i) {
    if (parent[i] != i)
        parent[i] = find_set(parent[i]);
    return parent[i];
}

// Union function for Union-Find
void union_set(int i, int j) {
    int a = find_set(i);
    int b = find_set(j);
    parent[a] = b;
}

int main() {
    int n, e;
    Edge edge[MAX];
    Edge temp;
    int total_cost = 0;
    clock_t start, end;
    double time_taken;

    printf("Enter number of vertices (<= %d): ", MAX);
    if (scanf("%d", &n) != 1) return 1;
    if (n <= 0 || n > MAX) {
        printf("Number of vertices must be between 1 and %d.\n", MAX);
        return 1;
    }

    printf("Enter number of edges (<= %d): ", MAX);
    if (scanf("%d", &e) != 1) return 1;
    if (e < 0 || e > MAX) {
        printf("Number of edges must be between 0 and %d.\n", MAX);
        return 1;
    }

    printf("Enter edges (u v w) with vertices in 0..%d:\n", n - 1);
    for (int i = 0; i < e; i++) {
        if (scanf("%d %d %d", &edge[i].u, &edge[i].v, &edge[i].w) != 3) return 1;
        if (edge[i].u < 0 || edge[i].u >= n || edge[i].v < 0 || edge[i].v >= n) {
            printf("Invalid vertex in edge %d. Vertices must be in 0..%d.\n", i + 1, n - 1);
            return 1;
        }
    }

    start = clock();

    // Initialize parent for each vertex
    for (int i = 0; i < n; i++)
        parent[i] = i;

    // Sort edges by weight (ascending) - simple bubble sort (sufficient for small inputs)
    for (int i = 0; i < e - 1; i++) {
        for (int j = 0; j < e - i - 1; j++) {
            if (edge[j].w > edge[j + 1].w) {
                temp = edge[j];
                edge[j] = edge[j + 1];
                edge[j + 1] = temp;
            }
        }
    }

    printf("\nEdges in Minimum Spanning Tree:\n");
    for (int i = 0, count = 0; count < n - 1 && i < e; i++) {
        int a = find_set(edge[i].u);
        int b = find_set(edge[i].v);

        if (a != b) {
            printf("%d - %d : %d\n", edge[i].u, edge[i].v, edge[i].w);
            total_cost += edge[i].w;
            union_set(a, b);
            count++;
        }
    }

    end = clock();
    time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("\nTotal Cost of MST = %d\n", total_cost);
    printf("Execution Time: %f seconds\n", time_taken);

    return 0;
}
