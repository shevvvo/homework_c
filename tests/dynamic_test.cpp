#include "gtest/gtest.h"

extern "C" {
#include "functions.h"
}

TEST(STATIS_TEST, wrong_filename) {
    EXPECT_EQ(start_work("error"), FILE_ERROR);
}

TEST(STATIC_TEST, zero_size) {
    EXPECT_EQ(start_work("../tests/3.txt"), FILE_ERROR);
}

TEST(STATIC_TEST, test1) {
    EXPECT_EQ(start_work("../tests/2.txt"), 1);
}

TEST(STATIC_TEST, test2) {
    EXPECT_EQ(start_work("../tests/4.txt"), 1);
}

TEST(STATIC_TEST, test3) {
    EXPECT_EQ(start_work("../tests/5.txt"), -1);
}

TEST(STATIC_TEST, test4) {
    EXPECT_EQ(start_work("../tests/6.txt"), 1);
}

TEST(STATIC_TEST, test5) {
    EXPECT_EQ(start_work("../tests/7.txt"), 1);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}