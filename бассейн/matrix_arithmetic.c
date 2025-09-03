#include <stdio.h>
#include <stdlib.h>
void input_matrix(int matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (scanf("%d", &matrix[i][j]) != 1) {
                printf("n/a\n");
                return 0;
            }
        }
    }
}
void print_matrix(int matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d", matrix[i][j]);
            if (j < cols - 1) {
                printf(" ");
            }
        }
        if (i < rows - 1) {
            printf("\n");
        }
    }
}
int allocate_matrix(int rows, int cols) {
    int matrix = (int )malloc(rows  sizeof(int ));
    for (int i = 0; i < rows; i++) {
        matrix[i] = (int )malloc(cols  sizeof(int));
    }
    return matrix;
}
void free_matrix(int matrix, int rows) {
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}
void add_matrices(int A, int B, int C, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}
void multiply_matrices(int A, int B, int C, int rowsA, int colsA, int colsB) {
    for (int i = 0; i < rowsA; i++) {
        for (int j = 0; j < colsB; j++) {
            C[i][j] = 0;
            for (int k = 0; k < colsA; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

int transpose_matrix(int matrix, int rows, int cols) {
    int transposed = allocate_matrix(cols, rows);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            transposed[j][i] = matrix[i][j];
        }
    }
    return transposed;
}

int main() {
    int operation;
    
    if (scanf("%d", &operation) != 1 || operation < 1 || operation > 3) {
        printf("n/a\n");
        return 1;
    }
    int rowsA, colsA, rowsB, colsB;
    int A, B, C;

    if (operation == 1) {
        if (scanf("%d %d", &rowsA, &colsA) != 2 || rowsA <= 0 || colsA <= 0) {
            printf("n/a\n");
            return 1;
        }
        A = allocate_matrix(rowsA, colsA);

        input_matrix(A, rowsA, colsA);

        if (scanf("%d %d", &rowsB, &colsB) != 2 || rowsB != rowsA || colsB != colsA) {
            printf("n/a\n");
            free_matrix(A, rowsA);
            return 1;
        }
        B = allocate_matrix(rowsB, colsB);

        input_matrix(B, rowsB, colsB);

        C = allocate_matrix(rowsA, colsA);
        add_matrices(A, B, C, rowsA, colsA);

        print_matrix(C, rowsA, colsA);

        free_matrix(A, rowsA);
        free_matrix(B, rowsB);
        free_matrix(C, rowsA);

    } else if (operation == 2) { 
        if (scanf("%d %d", &rowsA, &colsA) != 2 || rowsA <= 0 || colsA <= 0) {
            printf("n/a\n");
            return 1;
        }
        A = allocate_matrix(rowsA, colsA);
        input_matrix(A, rowsA, colsA);

        if (scanf("%d %d", &rowsB, &colsB) != 2 || rowsB <= 0 || colsB <= 0 || colsA != rowsB) {
            printf("n/a\n");
            free_matrix(A, rowsA);
            return 1;
        }
        B = allocate_matrix(rowsB, colsB);
        input_matrix(B, rowsB, colsB);
        C = allocate_matrix(rowsA, colsB);
        multiply_matrices(A, B, C, rowsA, colsA, colsB);
        print_matrix(C, rowsA, colsB);
        free_matrix(A, rowsA);
        free_matrix(B, rowsB);
        free_matrix(C, rowsA);

    } else if (operation == 3) { 
        if (scanf("%d %d", &rowsA, &colsA) != 2 || rowsA <= 0 || colsA <= 0) {
            printf("n/a\n");
            return 1;
        }
        A = allocate_matrix(rowsA, colsA);
        input_matrix(A, rowsA, colsA);
        C = transpose_matrix(A, rowsA, colsA);
        print_matrix(C, colsA, rowsA);
        free_matrix(A, rowsA);
        free_matrix(C, colsA);
    }
    return 0;
}