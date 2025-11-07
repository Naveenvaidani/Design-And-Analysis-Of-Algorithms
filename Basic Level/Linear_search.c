#include <stdio.h>
#include <time.h>

int main() {
    int n, i, key, found = 0;
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

    for(i = 0; i < n; i++) {
        if(arr[i] == key) {
            found = 1;
            break;
        }
    }

    end = clock();
    time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;

    if(found)
        printf("Element %d found at position %d\n", key, i + 1);
    else
        printf("Element %d not found\n", key);

    printf("Execution Time: %f seconds\n", time_taken);

    return 0;
}
