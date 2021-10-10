#include "gtest/gtest.h"
extern "C" {
#include "minor_matrix.h"
}

TEST(MINOR_TEST, Assert_zero_cols_rows) {
    EXPECT_TRUE(init_memory(0, 0) == nullptr);
}

TEST(MINOR_TEST, Assert_non_zero_cols_rows) {
    int** matrix = init_memory(3, 3);
    EXPECT_FALSE(matrix == nullptr);
    free_memory(matrix, 3);
}

TEST(MINOR_TEST, Assert_minor_1) {
    int matrix[2][2] = {1, 2, 4, 5};
    int** other_matrix = init_memory(3, 3);
    int flag = 1;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            other_matrix[i][j] = flag;
            flag++;
        }
    }
    int** result = finding_minor(other_matrix, 3, 3, 2, 2);
    for (size_t i = 0; i < 2; ++i) {
        for (size_t j = 0; j < 2; ++j) {
            EXPECT_EQ(result[i][j], matrix[i][j]);
        }
    }
    free_memory(other_matrix, 3);
    free_memory(result, 2);
}

TEST(MINOR_TEST, Assert_with_zero_index) {
    int** other_matrix = init_memory(3, 3);
    int flag = 1;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            other_matrix[i][j] = flag;
            flag++;
        }
    }
    int** result = finding_minor(other_matrix, 3, 3, 0, 0);
    EXPECT_EQ(result, nullptr);
    free_memory(other_matrix, 3);
}

TEST(MINOR_TEST, Assert_minor_2) {
    int matrix[4][4] = {1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4};
    int** other_matrix = init_memory(5, 5);
    int flag = 1;
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            other_matrix[i][j] = j + 1;
        }
    }
    int** result = finding_minor(other_matrix, 5, 5, 4, 4);
    for (size_t i = 0; i < 2; ++i) {
        for (size_t j = 0; j < 2; ++j) {
            EXPECT_EQ(result[i][j], matrix[i][j]);
        }
    }
    free_memory(other_matrix, 5);
    free_memory(result, 4);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}