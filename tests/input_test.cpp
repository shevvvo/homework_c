#include "gtest/gtest.h"

extern "C" {
#include "input.h"
}

TEST(INPUT_TEST, file_error) {
    EXPECT_TRUE(init_file_size("no file") == 0);
}

TEST(INPUT_TEST, file_size) {
    EXPECT_EQ(init_file_size("../tests/1.txt"), 10);
}

TEST(INPUT_TEST, file_size2) {
    EXPECT_EQ(init_file_size("../tests/2.txt"), 94935024);
}

TEST(INPUT_TEST, file_data) {
    char data[] = "123123123";
    char* file_data = init_massive_from_file(9, "../tests/1.txt");
    for (size_t i = 0; i < 9; ++i) {
        EXPECT_EQ(file_data[i], data[i]);
    }
    free(file_data);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}