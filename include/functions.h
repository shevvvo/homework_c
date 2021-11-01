#ifndef INCLUDE_FUNCTIONS_H_
#define INCLUDE_FUNCTIONS_H_

#define FILE_ERROR 124
#define MEMORY_ERROR 123
#define CPU_ERROR 122
#define THREAD_ERROR 121

typedef struct {
    long end;
    char *data;
} file_data;

int start_work(const char filename[]);

void* main_func(void* arg);

#endif  // INCLUDE_FUNCTIONS_H_
