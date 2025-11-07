#include <stdio.h>
#include <limits.h>
#include <time.h>

#define MAX 10
#define INF 9999

int n;
int cost[MAX][MAX];

void dijkstra(int start) {
    int dist[MAX], visited[MAX] = {0}, count, min_dist, next_node;

    for (int i = 0; i < n; i++)
        dist[i] = cost[start][i];

    visited[start] = 1;
    dist[start] = 0;
    count = 1;

    while (count < n - 1) {
        min_dist = INF;
        next_node = -1;

        // Find the unvisited node with the smallest distance
        for (int i = 0; i < n; i++) {
            if (!visited[i] && dist[i] < min_dist) {
                min_dist = dist[i];
                next_node = i;
            }
        }

        if (next_node == -1) // no reachable unvisited node
            break;

        visited[next_node] = 1;

        // Update distances of the neighboring nodes
        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                if (min_dist + cost[next_node][i] < dist[i])
                    dist[i] = min_dist + cost[next_node][i];
            }
        }
        count++;
    }

    // Print the shortest distances
    printf("\nShortest distances from source vertex %d:\n", start);
    for (int i = 0; i < n; i++)
        printf("To vertex %d: %d\n", i, dist[i]);
}

int main() {
    clock_t start_t, end_t;
    double total_time;

    printf("Enter number of vertices (<= %d): ", MAX);
    if (scanf("%d", &n) != 1) return 1;
    if (n <= 0 || n > MAX) {
        printf("Number of vertices must be between 1 and %d.\n", MAX);
        return 1;
    }

    printf("Enter the cost adjacency matrix (enter %d for infinity):\n", INF);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (scanf("%d", &cost[i][j]) != 1) return 1;

    int source;
    printf("Enter the source vertex (0 to %d): ", n - 1);
    if (scanf("%d", &source) != 1) return 1;
    if (source < 0 || source >= n) {
        printf("Invalid source vertex.\n");
        return 1;
    }

    start_t = clock();
    dijkstra(source);
    end_t = clock();

    total_time = ((double)(end_t - start_t)) / CLOCKS_PER_SEC;
    printf("\nExecution Time: %f seconds\n", total_time);

    return 0;
}
