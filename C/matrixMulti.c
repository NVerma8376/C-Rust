#include <stdio.h>

#define ROW1 3  // Number of rows in first matrix
#define COL1 2  // Number of columns in first matrix
#define ROW2 2  // Number of rows in second matrix (must equal COL1)
#define COL2 4  // Number of columns in second matrix

void multiplyMatrix(int mat1[ROW1][COL1], int mat2[ROW2][COL2], int result[ROW1][COL2]) {
    // Initialize result matrix with zeros
    for(int i = 0; i < ROW1; i++) {
        for(int j = 0; j < COL2; j++) {
            result[i][j] = 0;
        }
    }

    // Multiply matrices
    for(int i = 0; i < ROW1; i++) {
        for(int j = 0; j < COL2; j++) {
            for(int k = 0; k < COL1; k++) {
                result[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    }
}

void printMatrix1(int matrix[ROW1][COL1]) {
    for(int i = 0; i < ROW1; i++) {
        for(int j = 0; j < COL1; j++) {
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }
}

void printMatrix2(int matrix[ROW2][COL2]) {
    for(int i = 0; i < ROW2; i++) {
        for(int j = 0; j < COL2; j++) {
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }
}

void printResult(int matrix[ROW1][COL2]) {
    for(int i = 0; i < ROW1; i++) {
        for(int j = 0; j < COL2; j++) {
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    // First matrix (3x2)
    int matrix1[ROW1][COL1] = {
        {1, 2},
        {3, 4},
        {5, 6}
    };

    // Second matrix (2x4)
    int matrix2[ROW2][COL2] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8}
    };

    // Result matrix (3x4)
    int result[ROW1][COL2];

    // Check if multiplication is possible
    if (COL1 != ROW2) {
        printf("Error: The number of columns in first matrix must equal the number of rows in second matrix\n");
        return 1;
    }

    printf("First Matrix (%dx%d):\n", ROW1, COL1);
    printMatrix1(matrix1);

    printf("\nSecond Matrix (%dx%d):\n", ROW2, COL2);
    printMatrix2(matrix2);

    // Multiply matrices
    multiplyMatrix(matrix1, matrix2, result);

    printf("\nResult Matrix (%dx%d):\n", ROW1, COL2);
    printResult(result);

    return 0;
}
