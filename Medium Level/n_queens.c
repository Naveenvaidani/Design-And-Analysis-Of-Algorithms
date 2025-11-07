#include <stdio.h>
#include <math.h>
#include <time.h>

#define MAX 20

int board[MAX], n;

int place(int row, int column) {
    for (int i = 1; i <= row - 1; i++) {
        if (board[i] == column || abs(board[i] - column) == abs(i - row))
            return 0;
    }
    return 1;
}

void print_solution() {
    printf("\nSolution:\n");
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (board[i] == j)
                printf("Q ");
            else
                printf("* ");
        }
        printf("\n");
    }
}

void n_queens(int row) {
    if (row > n)
        print_solution();
    else {
        for (int column = 1; column <= n; column++) {
            if (place(row, column)) {
                board[row] = column;
                n_queens(row + 1);
            }
        }
    }
}

int main() {
    clock_t start, end;
    double time_taken;

    printf("Enter the number of queens: ");
    if (scanf("%d", &n) != 1) return 1;

    if (n <= 0 || n > MAX) {
        printf("Number of queens must be between 1 and %d.\n", MAX);
        return 1;
    }

    start = clock();
    n_queens(1);
    end = clock();

    time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("\nExecution Time: %f seconds\n", time_taken);

    return 0;
}
