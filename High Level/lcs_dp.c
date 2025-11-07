#include <stdio.h>
#include <string.h>
#include <time.h>

#define MAX 50

int max(int a, int b) {
    return (a > b) ? a : b;
}

int main() {
    char X[MAX], Y[MAX];
    int m, n;
    int L[MAX][MAX];
    clock_t start, end;
    double time_taken;

    printf("Enter first sequence: ");
    if (scanf("%49s", X) != 1) return 1;
    printf("Enter second sequence: ");
    if (scanf("%49s", Y) != 1) return 1;

    m = strlen(X);
    n = strlen(Y);

    if (m >= MAX || n >= MAX) {
        printf("Input strings must be shorter than %d characters.\n", MAX);
        return 1;
    }

    start = clock();

    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0 || j == 0)
                L[i][j] = 0;
            else if (X[i - 1] == Y[j - 1])
                L[i][j] = L[i - 1][j - 1] + 1;
            else
                L[i][j] = max(L[i - 1][j], L[i][j - 1]);
        }
    }

    end = clock();
    time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;

    // Backtrack to find the actual LCS
    int index = L[m][n];
    char lcs[index + 1];
    lcs[index] = '\0';

    int i = m, j = n;
    while (i > 0 && j > 0) {
        if (X[i - 1] == Y[j - 1]) {
            lcs[index - 1] = X[i - 1];
            i--;
            j--;
            index--;
        } else if (L[i - 1][j] > L[i][j - 1])
            i--;
        else
            j--;
    }

    printf("\nLongest Common Subsequence: %s\n", lcs);
    printf("Length of LCS = %d\n", L[m][n]);
    printf("Execution Time: %f seconds\n", time_taken);

    return 0;
}
