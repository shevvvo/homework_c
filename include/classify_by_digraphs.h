#ifndef INCLUDE_CLASSIFY_BY_DIGRAPHS_H_
#define INCLUDE_CLASSIFY_BY_DIGRAPHS_H_
#define FILE_ERROR 124
#define MEMORY_ERROR 123
#define CPU_ERROR 122
#define THREAD_ERROR 121

typedef struct {
  long end;
  long res;
  char *data;
} file_data;

int classify_by_digraphs(char *file_data, long size);

#endif  // INCLUDE_CLASSIFY_BY_DIGRAPHS_H_
