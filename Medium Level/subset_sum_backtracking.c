#include <stdio.h>
#include <time.h>

int n, target_sum, total = 0;
int set[20], subset[20];

void sum_of_subsets(int i, int current_sum, int remaining_sum) {
    if (current_sum == target_sum) {
        printf("Subset: ");
        for (int j = 0; j < i; j++) {
            if (subset[j])
                printf("%d ", set[j]);
        }
        printf("\n");
        return;
    }

    if (i >= n || current_sum + remaining_sum < target_sum)
        return;

    subset[i] = 1;
    sum_of_subsets(i + 1, current_sum + set[i], remaining_sum - set[i]);

    subset[i] = 0;
    sum_of_subsets(i + 1, current_sum, remaining_sum - set[i]);
}

int main() {
    clock_t start, end;
    double time_taken;

    printf("Enter number of elements (max 20): ");
    if (scanf("%d", &n) != 1) return 1;

    if (n <= 0 || n > 20) {
        printf("Number of elements must be between 1 and 20.\n");
        return 1;
    }

    total = 0;
    printf("Enter the elements in non-decreasing order:\n");
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &set[i]) != 1) return 1;
        total += set[i];
    }

    printf("Enter the target sum: ");
    if (scanf("%d", &target_sum) != 1) return 1;

    start = clock();
    printf("\nPossible subsets that sum to %d:\n", target_sum);
    sum_of_subsets(0, 0, total);
    end = clock();

    time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("\nExecution Time: %f seconds\n", time_taken);

    return 0;
}
