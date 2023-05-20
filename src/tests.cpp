#include "tests.h"

void countDeviation(HashMap_t *hashMapArr[], size_t arrSize) {
    double median = 0;
    double deviations[arrSize] = {};

    // count median
    for (int i = 0; i < DEFAULT_ARR_SIZE; i++) {
        median += hashMapArr[0]->listArr[i].size;
    }
    median /= DEFAULT_ARR_SIZE;

    // count deviation
    for (int i = 0; i < DEFAULT_ARR_SIZE; i++) {
        for (int j = 0; j < arrSize; j++) {
            deviations[j] += (hashMapArr[j]->listArr[i].size - median) * 
                                                (hashMapArr[j]->listArr[i].size - median);
        }
    }

    // print deviations and median for each hashMap
    for (int i = 0; i < arrSize; i++) {
        deviations[i] /= DEFAULT_ARR_SIZE;
        printf("%lf %lf\n", sqrt(deviations[i]), median);
    }
}

HashMap_t *createHashMapRandData(const int testCount, HashFunc_t hashFunc) {
    ON_ERROR(!randFunc, "Nullptr", nullptr);

    HashMap_t *hashMap = hashMapNew(hashFunc);

    for (int i = 0; i < testCount; i++) {
        int wordLen = rand() % 100;
        char *word = (char*) calloc(wordLen, sizeof(char));
        for (int j = 0; j < wordLen; j++) {
            word[j] = rand() % CHAR_MAX;
        }
        hashMapInsert(hashMap, word, word);
    }

    return hashMap;
}

void measureHashDistribution(HashFunc_t funcs[], size_t arrSize) {

    ON_ERROR(!randFunc || !hashFunc || !compFunc || !copyFunc || !freeFunc, "Nullptr", nullptr);

    HashMap_t *hashMaps[arrSize]   = {};

    for (size_t i = 0; i < arrSize; i++) {
        hashMaps[i] = createHashMapRandData(TEST_COUNT, funcs[i]);
    }

    // printing results
    FILE *file = fopen("hashTests.csv", "wb");
    fprintf(file, "\n");

    for (int i = 0; i < DEFAULT_ARR_SIZE; i++) {
        for (int j = 0; j < arrSize; j++) {
            fprintf(file, "%ld,", hashMaps[j]->listArr[i].size);
        }
        fprintf(file, "\n");
    }
    fclose(file);

    countDeviation(hashMaps, arrSize);

    // delete hashMaps
    // for (int i = 0; i < arrSize; i++) {
    //     hashMapDelete(hashMaps[i]);
    // }
} 
