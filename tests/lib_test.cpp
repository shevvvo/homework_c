#include "gtest/gtest.h"

extern "C" {
#include "parallel_or_consistent.h"
#include "input.h"
}

TEST(LIB_TEST, wrong_filename) {
  long size = init_file_size("error");
  char *mass = init_massive_from_file(size, "error");
  EXPECT_EQ(pre_working_initialize(mass, size), FILE_ERROR);
  free(mass);
}


TEST(LIB_TEST, test) {
  long size = init_file_size("../data/1.txt");
  char *mass = init_massive_from_file(size, "../data/1.txt");
  EXPECT_EQ(pre_working_initialize(mass, size), 1);
    free(mass);
}

TEST(LIB_TEST, test1) {
  long size = init_file_size("../data/2.txt");
  char *mass = init_massive_from_file(size, "../data/2.txt");
  EXPECT_EQ(pre_working_initialize(mass, size), 1);
  free(mass);
}

TEST(LIB_TEST, test2) {
  long size = init_file_size("../data/3.txt");
  char *mass = init_massive_from_file(size, "../data/3.txt");
  EXPECT_EQ(pre_working_initialize(mass, size), 1);
  free(mass);
}

TEST(LIB_TEST, test3) {
  long size = init_file_size("../data/4.txt");
  char *mass = init_massive_from_file(size, "../data/4.txt");
  EXPECT_EQ(pre_working_initialize(mass, size), 1);
  free(mass);
}

TEST(LIB_TEST, test4) {
  long size = init_file_size("../data/5.txt");
  char *mass = init_massive_from_file(size, "../data/5.txt");
  EXPECT_EQ(pre_working_initialize(mass, size), 1);
  free(mass);
}

TEST(LIB_TEST, test5) {
  long size = init_file_size("../data/6.txt");
  char *mass = init_massive_from_file(size, "../data/6.txt");
  EXPECT_EQ(pre_working_initialize(mass, size), -1);
  free(mass);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
