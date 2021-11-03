#include "gtest/gtest.h"

extern "C" {
#include "input.h"
}

TEST(INPUT_TEST, file1) {
    EXPECT_TRUE(init_file_size("no file") == 0);
}

TEST(INPUT_TEST, file2) {
    EXPECT_EQ(init_file_size("1.txt"), 52);
}

TEST(INPUT_TEST, file3) {
    EXPECT_EQ(init_file_size("2.txt"), 52);
}

TEST(INPUT_TEST, file4) {
    EXPECT_EQ(init_file_size("6.txt"), 106000000);
}

TEST(INPUT_TEST, file_data1) {
    char data[] = ":):):):(::12";
    char* file_data = init_massive_from_file(12, "7.txt");
    for (size_t i = 0; i < 9; ++i) {
        EXPECT_EQ(file_data[i], data[i]);
    }
    free(file_data);
}

TEST(INPUT_TEST, file_data) {
    char data[] = ":):):):):):)12:(";
    char* file_data = init_massive_from_file(16, "8.txt");
    for (size_t i = 0; i < 16; ++i) {
        EXPECT_EQ(file_data[i], data[i]);
    }
    free(file_data);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}