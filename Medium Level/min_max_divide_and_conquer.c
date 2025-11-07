#include <stdio.h>
#include <time.h>

struct Pair {
    int min;
    int max;
};

struct Pair findMinMax(int arr[], int low, int high) {
    struct Pair minmax, left, right;
    int mid;

    if (low == high) {
        minmax.min = arr[low];
        minmax.max = arr[low];
        return minmax;
    }

    if (high == low + 1) {
        if (arr[low] < arr[high]) {
            minmax.min = arr[low];
            minmax.max = arr[high];
        } else {
            minmax.min = arr[high];
            minmax.max = arr[low];
        }
        return minmax;
    }

    mid = (low + high) / 2;
    left = findMinMax(arr, low, mid);
    right = findMinMax(arr, mid + 1, high);

    if (left.min < right.min)
        minmax.min = left.min;
    else
        minmax.min = right.min;

    if (left.max > right.max)
        minmax.max = left.max;
    else
        minmax.max = right.max;

    return minmax;
}

int main() {
    int n, i;
    clock_t start, end;
    double time_taken;

    printf("Enter number of elements: ");
    if (scanf("%d", &n) != 1) return 1;

    if (n <= 0) {
        printf("Number of elements must be positive.\n");
        return 1;
    }

    int arr[n];
    printf("Enter %d elements:\n", n);
    for (i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    start = clock();

    struct Pair result = findMinMax(arr, 0, n - 1);

    end = clock();
    time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("Minimum element: %d\n", result.min);
    printf("Maximum element: %d\n", result.max);
    printf("Execution Time: %f seconds\n", time_taken);

    return 0;
}
