#include <stdio.h>
#include <time.h>

int main() {
    int n, i, key, low, high, mid, found = 0;
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

    low = 0;
    high = n - 1;

    start = clock();

    while(low <= high) {
        mid = (low + high) / 2;
        if(arr[mid] == key) {
            found = 1;
            break;
        }
        else if(arr[mid] < key)
            low = mid + 1;
        else
            high = mid - 1;
    }

    end = clock();
    time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;

    if(found)
        printf("Element %d found at position %d\n", key, mid + 1);
    else
        printf("Element %d not found\n", key);

    printf("Execution Time: %f seconds\n", time_taken);

    return 0;
}
