#ifndef INCLUDE_FUNCTIONS_H_
#define INCLUDE_FUNCTIONS_H_

#define FILE_ERROR 124
#define MEMORY_ERROR 123
#define CPU_ERROR 122
#define THREAD_ERROR 121

typedef struct {
  long end;
  long res;
  char *data;
} file_data;

int init_before_threading(char *file_data, long size);

#endif  // INCLUDE_FUNCTIONS_H_
