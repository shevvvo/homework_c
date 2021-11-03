#include <stdio.h>
#include <stdlib.h>

#include "functions.h"
#include "input.h"

int bad_or_good = -2;

void* algorithm_for_massive(void* arg) {
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

int pre_working_initialize(char* file_mass, long size) {
    if (size == 0) {
        free(file_mass);
        fprintf(stderr, "Size of file is 0\n");
        return FILE_ERROR;
    }
    if (file_mass == NULL) {
        free(file_mass);
        fprintf(stderr, "Memory error\n");
        return MEMORY_ERROR;
    }
    file_data* main_data = (file_data*)malloc(sizeof(file_data));
    if (main_data == NULL) {
        free(file_mass);
        fprintf(stderr, "Memory error\n");
        return MEMORY_ERROR;
    }
    main_data->data = file_mass;
    main_data->end = size;
    algorithm_for_massive(main_data);
    if (bad_or_good == -2) {
        free(main_data->data);
        free(main_data);
        return MEMORY_ERROR;
    }
    free(main_data->data);
    free(main_data);
    return bad_or_good;
}
