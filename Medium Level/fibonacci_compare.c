#include <stdio.h>
#include <time.h>

int fibonacci_recursive(int n) {
    if (n == 0) return 0;
    if (n == 1) return 1;
    return fibonacci_recursive(n - 1) + fibonacci_recursive(n - 2);
}

void fibonacci_iterative(int n) {
    int a = 0, b = 1, c;
    printf("Fibonacci Series (Iterative): ");
    if (n >= 1) printf("%d ", a);
    if (n >= 2) printf("%d ", b);
    for (int i = 3; i <= n; i++) {
        c = a + b;
        printf("%d ", c);
        a = b;
        b = c;
    }
    printf("\n");
}

int main() {
    int n;
    clock_t start, end;
    double time_taken;

    printf("Enter number of terms: ");
    if (scanf("%d", &n) != 1) return 1;

    if (n <= 0) {
        printf("Number of terms must be positive.\n");
        return 1;
    }

    // Iterative version
    start = clock();
    fibonacci_iterative(n);
    end = clock();
    time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Iterative Execution Time: %f seconds\n", time_taken);

    // Recursive version
    // Keep n reasonably small for recursive timings to avoid long runtimes
    if (n > 40) {
        printf("Skipping recursive timing for n > 40 to avoid very long runtime.\n");
    } else {
        start = clock();
        printf("Fibonacci Series (Recursive): ");
        for (int i = 0; i < n; i++)
            printf("%d ", fibonacci_recursive(i));
        printf("\n");
        end = clock();
        time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("Recursive Execution Time: %f seconds\n", time_taken);
    }

    return 0;
}
