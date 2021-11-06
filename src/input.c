#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "input.h"

long init_file_size(const char filename[]) {
  if (filename == 0) {
    fprintf(stderr, "Filename error\n");
    return 0;
  }
  FILE *file = fopen(filename, "r");
  if (file == NULL) {
    return 0;
  }
  fclose(file);
  struct stat filestat;
  stat(filename, &filestat);
  return (filestat.st_size);
}

char *init_massive_from_file(long size, const char filename[]) {
  char *data = (char *)calloc(size, sizeof(char));
  if (data == NULL) {
    fprintf(stderr, "Memory error\n");
    return NULL;
  }
  FILE *file = fopen(filename, "r");
  if (file == NULL) {
    free(data);
    fprintf(stderr, "File error\n");
    return NULL;
  }
  char *buf = (char *)calloc(120, sizeof(char));
  if (buf == NULL) {
    fclose(file);
    free(data);
    fprintf(stderr, "Memory error");
    return NULL;
  }
  int i = 0;
  while (fgets(buf, 120, file) != NULL) {
    int j = 0;
    while (j < strlen(buf) && buf[j] != '\n') {
      data[i] = buf[j];
      i++;
      j++;
    }
  }
  free(buf);
  fclose(file);
  return data;
}
