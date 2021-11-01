#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "input.h"

long init_file_size(const char filename[]) {
    if (filename == 0) {
        printf("Filename error\n");
        return 0;
    }
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        return 0;
    }
    fclose(file);
    struct stat filestat;
    stat(filename, &filestat);
    return (filestat.st_size);
}

char *init_massive_from_file(long size, const char filename[]) {
    char *data = (char *) malloc(size);
    if (data == NULL) {
        printf("Memory error\n");
        return NULL;
    }
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        free(data);
        printf("File error\n");
        return NULL;
    }
    for (long i = 0; i < size; ++i) {
        data[i] = getc(file);
    }
    fclose(file);
    return data;
}
