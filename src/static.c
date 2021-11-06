#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "functions.h"

int algorithm_for_massive(void *arg) {
  file_data *mass = (file_data *)arg;
  if (mass == NULL) {
    fprintf(stderr, "Memory error");
    return MEMORY_ERROR;
  }
  long good = 0;
  long bad = 0;
  int flag = 0;
  for (long i = 0; i < mass->end; ++i) {
    if (flag == 1) {
      if (mass->data[i] == ')') {
        good++;
        flag = 0;
      } else if (mass->data[i] == '(') {
        bad++;
        flag = 0;
      }
    }
    if (mass->data[i] == ':') {
      flag = 1;
    }
  }
  if (good > bad) {
    return 1;
  } else if (bad == good) {
    return 0;
  } else {
    return -1;
  }
}

int pre_working_initialize(char *file_mass, long size) {
  if (size == 0) {
    fprintf(stderr, "Size of file is 0\n");
    return FILE_ERROR;
  }
  if (file_mass == NULL) {
    fprintf(stderr, "Memory error\n");
    return MEMORY_ERROR;
  }
  file_data *main_data = (file_data *)malloc(sizeof(file_data));
  if (main_data == NULL) {
    fprintf(stderr, "Memory error\n");
    return MEMORY_ERROR;
  }
  main_data->data = file_mass;
  main_data->end = size;
  int res = algorithm_for_massive(main_data);
  free(main_data);
  return res;
}
