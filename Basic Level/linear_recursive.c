#include <stdio.h>
#include <time.h>

int linearSearchRecursive(int arr[], int n, int key, int index) {
    if(index == n)
        return -1;
    if(arr[index] == key)
        return index;
    return linearSearchRecursive(arr, n, key, index + 1);
}

int main() {
    int n, i, key, result;
    clock_t start, end;
    double time_taken;

    printf("Enter number of elements: ");
    if (scanf("%d", &n) != 1) return 1;

    int arr[n];
    printf("Enter %d elements:\n", n);
    for(i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    printf("Enter element to search: ");
    scanf("%d", &key);

    start = clock();

    result = linearSearchRecursive(arr, n, key, 0);

    end = clock();
    time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;

    if(result != -1)
        printf("Element %d found at position %d\n", key, result + 1);
    else
        printf("Element %d not found\n", key);

    printf("Execution Time: %f seconds\n", time_taken);

    return 0;
}
