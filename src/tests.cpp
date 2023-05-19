#include "tests.h"

int *createRandomIntArr  (const int testCount) {
    int *arr = (int*) calloc(testCount, sizeof(int));
    ON_ERROR(!arr, "Unable to alloc mem", nullptr);

    for (int i = 0; i < testCount; i++) {
        arr[i] = rand();
    }

    return arr;
}

float *createRandomFloatArr(const int testCount) {
    float *arr = (float*) calloc(testCount, sizeof(float));
    ON_ERROR(!arr, "Unable to alloc mem", nullptr);

    for (int i = 0; i < testCount; i++) {
        int delValue = rand();
        arr[i] = ((float) rand()) / ((float) RAND_MAX / delValue);
    }

    return arr;
}

char *createRandomCharArr (const int testCount) {
    char *arr = (char*) calloc(testCount, sizeof(char));
    ON_ERROR(!arr, "Unable to alloc mem", nullptr);

    for (int i = 0; i < testCount; i++) {
        arr[i] = (char) (rand() % CHAR_MAX);
    }

    return arr;
}