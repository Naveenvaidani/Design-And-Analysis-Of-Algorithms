#include <stdio.h>
#include <time.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

int main() {
    int n, W;
    int weight[51], profit[51];
    clock_t start, end;
    double time_taken;

    printf("Enter number of items (<=50): ");
    if (scanf("%d", &n) != 1) return 1;
    if (n <= 0 || n > 50) {
        printf("Number of items must be between 1 and 50.\n");
        return 1;
    }

    printf("Enter the weights of items (1..%d): ", n);
    for (int i = 1; i <= n; i++) {
        if (scanf("%d", &weight[i]) != 1) return 1;
    }

    printf("Enter the profits of items (1..%d): ", n);
    for (int i = 1; i <= n; i++) {
        if (scanf("%d", &profit[i]) != 1) return 1;
    }

    printf("Enter the capacity of knapsack: ");
    if (scanf("%d", &W) != 1) return 1;
    if (W < 0) {
        printf("Capacity must be non-negative.\n");
        return 1;
    }

    // Use a VLA for the DP table sized to (n+1) x (W+1)
    int V[n + 1][W + 1];

    start = clock();

    // Dynamic Programming Table Construction
    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            if (i == 0 || w == 0)
                V[i][w] = 0;
            else if (weight[i] <= w)
                V[i][w] = max(profit[i] + V[i - 1][w - weight[i]], V[i - 1][w]);
            else
                V[i][w] = V[i - 1][w];
        }
    }

    end = clock();
    time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("\nMaximum Profit = %d\n", V[n][W]);
    printf("Execution Time (DP table build): %f seconds\n", time_taken);

    // Display selected items (optional)
    int res = V[n][W];
    int w = W;
    printf("Selected item indices (1-based): ");
    for (int i = n; i > 0 && res > 0; i--) {
        if (res == V[i - 1][w])
            continue;
        else {
            printf("%d ", i);
            res -= profit[i];
            w -= weight[i];
        }
    }
    printf("\n");

    return 0;
}
