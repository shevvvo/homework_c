#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>
#include "functions.h"

int main(int argc, const char** argv) {
    if (argv[1] == 0) {
        printf("Filename error\n");
    }
    struct timespec start, finish;
    clock_gettime(CLOCK_MONOTONIC, &start);
    int res = start_work(argv[1]);
    if (res == 1) {
        printf("Good\n");
    } else if (res == 0) {
        printf("Normal\n");
    } else if (res == -1) {
        printf("Bad\n");
    }
    clock_gettime(CLOCK_MONOTONIC, &finish);
    printf("Time: %ld\n",  finish.tv_sec - start.tv_sec);
    return 0;
}
