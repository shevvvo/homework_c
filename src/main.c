#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>

#include "functions.h"
#include "input.h"

#define SUCCESS 0
#define FAILURE -12

int main(int argc, const char **argv) {
  if (argv[1] == 0) {
    printf("Filename error\n");
  }
  struct timespec start, finish;
  long size = init_file_size(argv[1]);
  if (size == 0) {
    fprintf(stderr, "Size error\n");
    return FAILURE;
  }
  char *file_mass = init_massive_from_file(size, argv[1]);
  if (file_mass == NULL) {
    fprintf(stderr, "File error\n");
    return FAILURE;
  }
  clock_gettime(CLOCK_MONOTONIC, &start);
  int res = pre_working_initialize(file_mass, size);
  if (res == 1) {
    printf("Good\n");
  } else if (res == 0) {
    printf("Normal\n");
  } else if (res == -1) {
    printf("Bad\n");
  }
  free(file_mass);
  clock_gettime(CLOCK_MONOTONIC, &finish);
  printf("Time: %ld\n", finish.tv_sec - start.tv_sec);
  return SUCCESS;
}
