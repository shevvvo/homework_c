#ifndef HW_1_PROJECT_MINOR_MATRIX_H_
#define HW_1_PROJECT_MINOR_MATRIX_H_

void free_memory(int** matrix, size_t rows);
int** finding_minor(int** matrix, size_t rows, size_t cols, size_t index_i, size_t index_j);
int** init_memory(size_t rows, size_t cols);

#endif    //  HW_1_PROJECT_MINOR_MATRIX_H_
