#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "functions.h"
#include "input.h"

static long good = 0;
static long bad = 0;
static int flag = 0;
pthread_mutex_t mutex;

void *main_func(void *arg) {
    file_data *data = (file_data *) arg;
    for (long i = 0; i < data->end; ++i) {
        if (flag == 1) {
            if (data->data[i] == ')') {
                pthread_mutex_lock(&mutex);
                good++;
                flag = 0;
                pthread_mutex_unlock(&mutex);
            } else if (data->data[i] == '(') {
                pthread_mutex_lock(&mutex);
                bad++;
                flag = 0;
                pthread_mutex_unlock(&mutex);
            }
        }
        if (data->data[i] == ':') {
            pthread_mutex_lock(&mutex);
            flag = 1;
            pthread_mutex_unlock(&mutex);
        }
    }
    return NULL;
}

int start_work(const char filename[]) {
    bad = 0;
    good = 0;
    if (filename == 0) {
        printf("Filename error\n");
        return FILE_ERROR;
    }
    long ncpus = sysconf(_SC_NPROCESSORS_CONF);
    if (ncpus == -1) {
        printf("CPUs error\n");
        return CPU_ERROR;
    }
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("File error\n");
        return FILE_ERROR;
    }
    long size = init_file_size(filename);
    if (size == 0) {
        fclose(file);
        printf("Size error\n");
        return FILE_ERROR;
    }
    size--;
    if (size < ncpus) {
        ncpus = size;
    }
    char *mass = init_massive_from_file(size, filename);
    if (mass == NULL) {
        fclose(file);
        printf("Memory error\n");
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
        free(mass);
        fclose(file);
        printf("Memory error\n");
        return MEMORY_ERROR;
    }

    file_data *data_for_thread = (file_data *) malloc(ncpus * sizeof(file_data));
    if (data_for_thread == NULL) {
        free(mass);
        free(threads);
        fclose(file);
        printf("Memory error\n");
        return MEMORY_ERROR;
    }


    for (long i = 0; i < ncpus; ++i) {
        data_for_thread[i].data = (char *) malloc(sizeof(char) * thread_data_size);
        if (data_for_thread[i].data == NULL) {
            for (int j = 0; j < i; ++j) {
                free(data_for_thread[i].data);
            }
            free(data_for_thread);
            free(mass);
            free(threads);
            fclose(file);
            printf("Memory error\n");
            return MEMORY_ERROR;
        }
    }
    long start = 0;
    long end = thread_data_size;
    long delta = thread_data_size * ncpus - size;
    for (long i = 0; i < ncpus; ++i) {
        /*printf("START FOR %ld: %ld\n", i, start);
        printf("END FOR %ld: %ld\n", i, end);*/
        for (long j = start; j < end; ++j) {
            data_for_thread[i].data[j - start] = mass[j];
        }
        if (i == ncpus - 1 && size % ncpus != 0) {
            data_for_thread[i].end = delta;
        } else {
            data_for_thread[i].end = thread_data_size;
        }
        start = end;
        if (size % ncpus != 0 && i == ncpus - 2) {
            end += delta;
        } else {
            end += thread_data_size;
        }
        if (pthread_create(&(threads[i]), NULL, main_func, &data_for_thread[i]) != 0) {
            for (int j = 0; j < ncpus; ++j) {
                free(data_for_thread[j].data);
            }
            free(data_for_thread);
            free(mass);
            free(threads);
            fclose(file);
            printf("Thread error\n");
            return THREAD_ERROR;
        }
    }

    for (long i = 0; i < ncpus; ++i) {
        pthread_join(threads[i], NULL);
    }

    free(threads);
    for (int i = 0; i < ncpus; ++i) {
        free(data_for_thread[i].data);
    }

    free(data_for_thread);
    fclose(file);
    free(mass);
    if (good > bad) {
        return 1;
    } else if (bad == good) {
        return 0;
    } else {
        return -1;
    }
}
