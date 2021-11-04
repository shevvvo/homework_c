#include "gtest/gtest.h"

extern "C" {
#include "functions.h"
#include "input.h"
}
/*
TEST(LIB_TEST, wrong_filename) {
    long size = init_file_size("error");
    char* mass = init_massive_from_file(size, "error");
    EXPECT_EQ(pre_working_initialize(mass, size), FILE_ERROR);
}

TEST(LIB_TEST, zero_size) {
    long size = init_file_size("1.txt");
    char* mass = init_massive_from_file(size, "1.txt");
    EXPECT_EQ(pre_working_initialize(mass, size), 1);
}

TEST(LIB_TEST, test1) {
    long size = init_file_size("2.txt");
    char* mass = init_massive_from_file(size, "2.txt");
    EXPECT_EQ(pre_working_initialize(mass, size), 1);
}

TEST(LIB_TEST, test2) {
    long size = init_file_size("3.txt");
    char* mass = init_massive_from_file(size, "3.txt");
    EXPECT_EQ(pre_working_initialize(mass, size), 1);
}

TEST(LIB_TEST, test3) {
    long size = init_file_size("4.txt");
    char* mass = init_massive_from_file(size, "4.txt");
    EXPECT_EQ(pre_working_initialize(mass, size), 1);
}

TEST(LIB_TEST, test4) {
    long size = init_file_size("5.txt");
    char* mass = init_massive_from_file(size, "5.txt");
    EXPECT_EQ(pre_working_initialize(mass, size), 1);
}*/

TEST(LIB_TEST, test5) {
    long size = init_file_size("6.txt");
    char* mass = init_massive_from_file(size, "6.txt");
    EXPECT_EQ(pre_working_initialize(mass, size), -1);
    //free(mass);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
