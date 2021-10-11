#include <stdio.h>
#include <stdlib.h>
#include "minor_matrix.h"

void free_memory(int** matrix, size_t rows) {
    for (size_t i = 0; i < rows; ++i) {
        free(matrix[i]);
    }
    free(matrix);
}

int** init_memory(size_t rows, size_t cols) {
    if (rows == 0 || cols == 0) {
        printf("Use non-zero arguments");
        return NULL;
    }
    int** new_matrix = (int**) malloc((rows) * sizeof(int*));
    if (new_matrix == NULL) {
        printf("Memory error new matrix");
        free(new_matrix);
        return NULL;
    }
    for (size_t i = 0; i < rows; ++i) {
        new_matrix[i] = (int*) malloc((cols) * sizeof(int));
        if (new_matrix[i] == NULL) {
            printf("Memory error");
            free_memory(new_matrix, i);
            return NULL;
        }
    }
    return new_matrix;
}

int** finding_minor(int** matrix, size_t rows, size_t cols, size_t index_i, size_t index_j) {
    if (cols == 0 || rows == 0) {
        printf("Try with other arguments\n");
        return NULL;
    }
    if (index_i < 1 || index_j < 1) {
        printf("Try with other arguments");
        return NULL;
    }
    int** new_matrix = init_memory(rows - 1, cols - 1);
    if (new_matrix == NULL) {
        printf("Memory error");
        return NULL;
    }

    size_t flag_i = 0;
    size_t flag_j = 0;
    for (size_t i = 0; i < rows; ++i) {
        if (i == index_i) {
            flag_i++;
        }
        for (size_t j = 0; j < cols; ++j) {
            if (i == index_i && j == index_j) {
                flag_j++;
            } else if (i == index_i) {
            } else if (j == index_j) {
                flag_j++;
            } else {
                new_matrix[i - flag_i][j - flag_j] = matrix[i][j];
            }
        }
        flag_j = 0;
    }
    return new_matrix;
}
