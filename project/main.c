#include <stdio.h>
#include "minor_matrix.h"

#define MEMORY_ERROR 124
#define ENTRY_ERROR 123

int main() {
    size_t cols, rows;
    printf("Enter cols and rows: \n");
    if (scanf("%zu%zu", &rows, &cols) != 2) {
        fprintf(stderr, "Entry error\n");
        return ENTRY_ERROR;
    }

    int **matrix = init_memory(rows, cols);
    if (matrix == NULL) {
        return MEMORY_ERROR;
    }

    printf("Insert matrix coeffs: \n");
    for (siz_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            if (scanf("%d", &matrix[i][j]) != 1) {
                fprintf(stderr, "Entry error");
                return ENTRY_ERROR;
            }
        }
    }

    printf("\n\n");
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    printf("Insert coeffs for minor: \n");
    size_t index_i, index_j;
    if (scanf("%zu%zu", &index_i, &index_j) != 2) {
        fprintf(stderr, "Entry error");
        return ENTRY_ERROR;
    }

    int **new_matrix = finding_minor(matrix, rows, cols, index_i, index_j);
    if (new_matrix == NULL) {
        return MEMORY_ERROR;
    }

    printf("\n\n");
    for (size_t i = 0; i < rows - 1; ++i) {
        for (size_t j = 0; j < cols - 1; ++j) {
            printf("%d ", new_matrix[i][j]);
        }
        printf("\n");
    }

    //free_memory(matrix, rows);
    //free_memory(new_matrix, rows - 1);

    return 0;
}
