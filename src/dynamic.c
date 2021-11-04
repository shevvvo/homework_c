#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "functions.h"
#include "input.h"

#define GOOD 1
#define BAD -1
#define NORMAL 0

void *algorithm_for_massive(void *arg) {
    file_data *data = (file_data *) arg;
    if (data == NULL) {
        return NULL;
    }
    data->res = 0;
    long local_flag = 0;
    int bad = 0;
    int good = 0;
    for (long i = 0; i < data->end - 1; ++i) {
        if ((data->data[i] == ')' || data->data[i] == '(') && i == 0) {
            continue;
        } else if (data->data[i] == ':' && i == data->end - 2) {
            if (data->data[i + 1] == ')') {
                good++;
            } else if (data->data[i + 1] == '(') {
                bad--;
            }
        } else if (data->data[i] == ':') {
            local_flag = 1;
        } else if (local_flag == 1) {
            if (data->data[i] == ')') {
                good++;
                local_flag = 0;
            } else if (data->data[i] == '(') {
                bad--;
                local_flag = 0;
            }
        }
    }
    data->res = bad + good;
    return NULL;
}

int pre_working_initialize(char* file_mass, long size) {
    long ncpus = sysconf(_SC_NPROCESSORS_CONF);
    if (ncpus == -1) {
        fprintf(stderr, "CPUs error\n");
        free(file_mass);
        return CPU_ERROR;
    }
    if (size == 0) {
        fprintf(stderr, "Size error\n");
        free(file_mass);
        return FILE_ERROR;
    }
    size--;
    if (size < ncpus) {
        ncpus = size;
    }
    if (file_mass == NULL) {
        fprintf(stderr, "Memory error\n");
        free(file_mass);
        return MEMORY_ERROR;
    }
    long thread_data_size;
    if (size % ncpus == 0) {
        thread_data_size = size / ncpus;
    } else {
        thread_data_size = size / ncpus + 1;
    }
    if ((thread_data_size * ncpus) > size) {
        if (size % thread_data_size == 0) {
            ncpus = size / thread_data_size;
        } else {
            ncpus = size / thread_data_size + 1;
        }
    }
    pthread_t *threads = (pthread_t *) malloc(ncpus * sizeof(pthread_t));
    if (threads == NULL) {
        fprintf(stderr, "Memory error\n");
        free(file_mass);
        return MEMORY_ERROR;
    }

    file_data *data_for_thread = (file_data *) malloc(ncpus * sizeof(file_data));
    if (data_for_thread == NULL) {
        free(threads);
        free(file_mass);
        fprintf(stderr, "Memory error\n");
        return MEMORY_ERROR;
    }


    for (long i = 0; i < ncpus; ++i) {
        data_for_thread[i].data = (char *) calloc((thread_data_size + 2), sizeof(char));
        if (data_for_thread[i].data == NULL) {
            for (long j = 0; j < i; ++j) {
                free(data_for_thread[i].data);
            }
            free(data_for_thread);
            free(threads);
            free(file_mass);
            fprintf(stderr, "Memory error\n");
            return MEMORY_ERROR;
        }
    }
    long start = 0;
    long end = thread_data_size + 1;
    long delta = thread_data_size * ncpus - size;
    for (long i = 0; i < ncpus; ++i) {
        if (i != ncpus - 1) {
            end++;
        }
        for (long j = start; j < end && j < size; ++j) {
            data_for_thread[i].data[j - start] = file_mass[j];
        }
        if (i == ncpus - 1 && size % ncpus != 0) {
            data_for_thread[i].end = thread_data_size - delta;
        } else if (i == ncpus - 1) {
            data_for_thread[i].end = thread_data_size;
        } else {
            data_for_thread[i].end = thread_data_size + 1;
        }
        start += thread_data_size;
        if (size % ncpus != 0 && i == ncpus - 2) {
            end += thread_data_size - delta;
        } else {
            end += thread_data_size;
            end--;
        }
        if (pthread_create(&(threads[i]), NULL, algorithm_for_massive, &data_for_thread[i]) != 0) {
            for (long j = 0; j < ncpus; ++j) {
                free(data_for_thread[j].data);
            }
            free(data_for_thread);
            free(file_mass);
            free(threads);
            fprintf(stderr, "Thread error\n");
            return THREAD_ERROR;
        }
    }
    long result = 0;
    for (long i = 0; i < ncpus; ++i) {
        pthread_join(threads[i], NULL);
        result += data_for_thread[i].res;
    }
    free(file_mass);
    free(threads);
    for (long i = 0; i < ncpus; ++i) {
        free(data_for_thread[i].data);
    }
    free(data_for_thread);
    if (result > 0) {
        return GOOD;
    } else if (result == 0) {
        return NORMAL;
    } else {
        return BAD;
    }
}
