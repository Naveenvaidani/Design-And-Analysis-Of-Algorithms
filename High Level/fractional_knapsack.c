#include <stdio.h>
#include <time.h>

void fractional_knapsack(int n, float weight[], float profit[], float capacity) {
    float ratio[20], x[20], total_profit = 0, remaining_capacity = capacity;
    int i, j;
    clock_t start, end;
    double time_taken;

    start = clock();

    for (i = 0; i < n; i++)
        ratio[i] = profit[i] / weight[i];

    // Sorting by profit/weight ratio (descending)
    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if (ratio[i] < ratio[j]) {
                float temp;
                temp = ratio[i]; ratio[i] = ratio[j]; ratio[j] = temp;
                temp = weight[i]; weight[i] = weight[j]; weight[j] = temp;
                temp = profit[i]; profit[i] = profit[j]; profit[j] = temp;
            }
        }
    }

    for (i = 0; i < n; i++)
        x[i] = 0.0f;

    for (i = 0; i < n; i++) {
        if (weight[i] > remaining_capacity)
            break;
        x[i] = 1.0f;
        total_profit += profit[i];
        remaining_capacity -= weight[i];
    }

    if (i < n && weight[i] > 0.0f) {
        x[i] = remaining_capacity / weight[i];
        total_profit += x[i] * profit[i];
    }

    end = clock();
    time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("\nItem\tWeight\tProfit\tTaken\n");
    for (i = 0; i < n; i++)
        printf("%d\t%.2f\t%.2f\t%.2f\n", i + 1, weight[i], profit[i], x[i]);

    printf("\nMaximum Profit = %.2f\n", total_profit);
    printf("Execution Time: %f seconds\n", time_taken);
}

int main() {
    int n;
    float weight[20], profit[20], capacity;

    printf("Enter number of items (max 20): ");
    if (scanf("%d", &n) != 1) return 1;
    if (n <= 0 || n > 20) {
        printf("Number of items must be between 1 and 20.\n");
        return 1;
    }

    printf("Enter weights of items:\n");
    for (int i = 0; i < n; i++) {
        if (scanf("%f", &weight[i]) != 1) return 1;
        if (weight[i] <= 0.0f) {
            printf("Weights must be positive.\n");
            return 1;
        }
    }

    printf("Enter profits of items:\n");
    for (int i = 0; i < n; i++) {
        if (scanf("%f", &profit[i]) != 1) return 1;
        if (profit[i] < 0.0f) {
            printf("Profits must be non-negative.\n");
            return 1;
        }
    }

    printf("Enter knapsack capacity: ");
    if (scanf("%f", &capacity) != 1) return 1;
    if (capacity < 0.0f) {
        printf("Capacity must be non-negative.\n");
        return 1;
    }

    fractional_knapsack(n, weight, profit, capacity);

    return 0;
}
