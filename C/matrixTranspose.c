#include <stdio.h>

#define ROWS 4
#define COLS 3

void transposeMatrix(int original[ROWS][COLS], int transposed[COLS][ROWS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            transposed[j][i] = original[i][j];
        }
    }
}

void printOriginal(int matrix[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void printTransposed(int matrix[COLS][ROWS]) {
    for (int i = 0; i < COLS; i++) {
        for (int j = 0; j < ROWS; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int matrix[ROWS][COLS] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9},
        {10, 11, 12}
    };

    int transposed[COLS][ROWS]; // Transposed matrix will have dimensions 3x4

    printf("Original %dx%d Matrix:\n", ROWS, COLS);
    printOriginal(matrix);

    transposeMatrix(matrix, transposed);

    printf("\nTransposed %dx%d Matrix:\n", COLS, ROWS);
    printTransposed(transposed);

    return 0;
}
