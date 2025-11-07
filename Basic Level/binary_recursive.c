#include <stdio.h>
#include <time.h>

int binarySearchRecursive(int arr[], int low, int high, int key) {
    if(low > high)
        return -1;

    int mid = (low + high) / 2;

    if(arr[mid] == key)
        return mid;
    else if(arr[mid] > key)
        return binarySearchRecursive(arr, low, mid - 1, key);
    else
        return binarySearchRecursive(arr, mid + 1, high, key);
}

int main() {
    int n, i, key, result;
    clock_t start, end;
    double time_taken;

    printf("Enter number of elements (sorted order): ");
    if (scanf("%d", &n) != 1) return 1;

    int arr[n];
    printf("Enter %d sorted elements:\n", n);
    for(i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    printf("Enter element to search: ");
    if (scanf("%d", &key) != 1) return 1;

    start = clock();

    result = binarySearchRecursive(arr, 0, n - 1, key);

    end = clock();
    time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;

    if(result != -1)
        printf("Element %d found at position %d\n", key, result + 1);
    else
        printf("Element %d not found\n", key);

    printf("Execution Time: %f seconds\n", time_taken);

    return 0;
}
