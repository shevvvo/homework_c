#include <stdio.h>
#include <stdlib.h>
#include "functions.h"
#include "input.h"

int bad_or_good = -2;

void* main_func(void* arg) {
    file_data* mass = (file_data*)arg;
    if (mass == NULL) {
        bad_or_good = -2;
        fprintf(stderr, "Memory error");
        return NULL;
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
        bad_or_good = 1;
    } else if (bad == good) {
        bad_or_good = 0;
    } else {
        bad_or_good = -1;
    }

    return NULL;
}

int start_work(const char filename[]) {
    if (filename == 0) {
        fprintf(stderr, "Filename error\n");
        return FILE_ERROR;
    }
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "File error\n");
        return FILE_ERROR;
    }
    long size = init_file_size(filename);
    if (size == 0) {
        fclose(file);
        fprintf(stderr, "Size of file is 0\n");
        return FILE_ERROR;
    }
    char* mass = init_massive_from_file(size, filename);
    if (mass == NULL) {
        fclose(file);
        fprintf(stderr, "Memory error\n");
        return MEMORY_ERROR;
    }
    file_data* main_data = (file_data*)malloc(sizeof(file_data));
    if (main_data == NULL) {
        fclose(file);
        free(mass);
        fprintf(stderr, "Memory error\n");
        return MEMORY_ERROR;
    }
    main_data->data = mass;
    main_data->end = size;
    main_func(main_data);
    if (bad_or_good == -2) {
        fclose(file);
        free(main_data->data);
        free(main_data);
        return MEMORY_ERROR;
    }
    fclose(file);
    free(main_data->data);
    free(main_data);
    return bad_or_good;
}
