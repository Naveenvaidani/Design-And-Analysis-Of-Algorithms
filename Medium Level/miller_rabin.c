#include <stdio.h>
#include <stdlib.h>
#include <time.h>

long long power_mod(long long a, long long d, long long n) {
    long long result = 1;
    a = a % n;
    while (d > 0) {
        if (d & 1)
            result = (result * a) % n;
        d >>= 1;
        a = (a * a) % n;
    }
    return result;
}

int miller_test(long long d, long long n) {
    long long a = 2 + rand() % (n - 4);
    long long x = power_mod(a, d, n);
    if (x == 1 || x == n - 1)
        return 1;
    while (d != n - 1) {
        x = (x * x) % n;
        d <<= 1;
        if (x == 1)
            return 0;
        if (x == n - 1)
            return 1;
    }
    return 0;
}

int is_prime(long long n, int k) {
    if (n <= 1 || n == 4)
        return 0;
    if (n <= 3)
        return 1;

    long long d = n - 1;
    while ((d & 1) == 0)
        d >>= 1;

    for (int i = 0; i < k; i++)
        if (!miller_test(d, n))
            return 0;
    return 1;
}

int main() {
    long long n;
    int k;
    clock_t start, end;
    double total_time;

    printf("Enter number to test primality: ");
    if (scanf("%lld", &n) != 1) return 1;
    printf("Enter number of iterations (accuracy factor, e.g. 5-10): ");
    if (scanf("%d", &k) != 1) return 1;
    if (k <= 0) k = 5;

    srand((unsigned)time(NULL));

    start = clock();
    if (is_prime(n, k))
        printf("%lld is probably prime.\n", n);
    else
        printf("%lld is composite.\n", n);
    end = clock();

    total_time = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Execution Time: %f seconds\n", total_time);

    return 0;
}
