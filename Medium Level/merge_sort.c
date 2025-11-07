#include <stdio.h>
#include <time.h>

void merge(int arr[], int low, int mid, int high) {
    int n1 = mid - low + 1;
    int n2 = high - mid;
    int left[n1], right[n2];
    int i, j, k;

    for(i = 0; i < n1; i++)
        left[i] = arr[low + i];
    for(j = 0; j < n2; j++)
        right[j] = arr[mid + 1 + j];

    i = 0; 
    j = 0; 
    k = low;

    while(i < n1 && j < n2) {
        if(left[i] <= right[j])
            arr[k++] = left[i++];
        else
            arr[k++] = right[j++];
    }

    while(i < n1)
        arr[k++] = left[i++];
    while(j < n2)
        arr[k++] = right[j++];
}

void mergeSort(int arr[], int low, int high) {
    if(low < high) {
        int mid = (low + high) / 2;
        mergeSort(arr, low, mid);
        mergeSort(arr, mid + 1, high);
        merge(arr, low, mid, high);
    }
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
    for(i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    start = clock();

    mergeSort(arr, 0, n - 1);

    end = clock();
    time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("Sorted array:\n");
    for(i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\nExecution Time: %f seconds\n", time_taken);

    return 0;
}
