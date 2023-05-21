#include "tests.h"

#include <chrono>

// void countDeviation(HashMap_t *hashMapArr[], size_t arrSize) {
//     double median = 0;
//     double deviations[arrSize] = {};

//     // count median
//     for (int i = 0; i < DEFAULT_ARR_SIZE; i++) {
//         median += hashMapArr[0]->listArr[i].size;
//     }
//     median /= DEFAULT_ARR_SIZE;

//     // count deviation
//     for (int i = 0; i < DEFAULT_ARR_SIZE; i++) {
//         for (int j = 0; j < arrSize; j++) {
//             deviations[j] += (hashMapArr[j]->listArr[i].size - median) * 
//                                                 (hashMapArr[j]->listArr[i].size - median);
//         }
//     }

//     // print deviations and median for each hashMap
//     for (int i = 0; i < arrSize; i++) {
//         deviations[i] /= DEFAULT_ARR_SIZE;
//         printf("%lf %lf\n", sqrt(deviations[i]), median);
//     }
// }

// HashMap_t *createHashMapRandData(const int testCount, HashFunc_t hashFunc) {
//     ON_ERROR(!randFunc, "Nullptr", nullptr);

//     HashMap_t *hashMap = hashMapNew(hashFunc);

//     for (int i = 0; i < testCount; i++) {
//         int wordLen = rand() % 100;
//         char *word = (char*) calloc(wordLen, sizeof(char));
//         for (int j = 0; j < wordLen; j++) {
//             word[j] = rand() % CHAR_MAX;
//         }
//         hashMapInsert(hashMap, word, word);
//     }

//     return hashMap;
// }

// void measureHashDistribution(HashFunc_t funcs[], size_t arrSize) {

//     ON_ERROR(!randFunc || !hashFunc || !compFunc || !copyFunc || !freeFunc, "Nullptr", nullptr);

//     HashMap_t *hashMaps[arrSize]   = {};

//     for (size_t i = 0; i < arrSize; i++) {
//         hashMaps[i] = createHashMapRandData(TEST_COUNT, funcs[i]);
//     }

//     // printing results
//     FILE *file = fopen("hashTests.csv", "wb");
//     fprintf(file, "\n");

//     for (int i = 0; i < DEFAULT_ARR_SIZE; i++) {
//         for (int j = 0; j < arrSize; j++) {
//             fprintf(file, "%ld,", hashMaps[j]->listArr[i].size);
//         }
//         fprintf(file, "\n");
//     }
//     fclose(file);

//     countDeviation(hashMaps, arrSize);

//     // delete hashMaps
//     // for (int i = 0; i < arrSize; i++) {
//     //     hashMapDelete(hashMaps[i]);
//     // }
// } 

void measureHashMapTime(HashFunc_t hashFunc) {
    ON_ERROR(!hashFunc, "Nullptr", );

    HashMap_t *hashMap = hashMapNew(hashFunc);

    char *randArr[1000000] = {};
    for (int i = 0; i < 1000000; i++) {
        int wordLen = rand() % 100;
        char *word = (char*) calloc(wordLen+1, sizeof(char));

        for (int j = 0; j < wordLen; j++) {
            word[j] = rand() % CHAR_MAX;
        }
        word[wordLen] = '\0';

        randArr[i] = word;
    }

    auto start = std::chrono::high_resolution_clock::now(); 

    double tempTime = 0;

    for (int i = 10000; i <= 1000000; i += 10000) {
        fprintf(stderr, "%d %lld\n", i, tempTime);
        for (int j = 0; j < i; j++) {
            int oper = rand() % 3;
            int index = rand() % 1000000;


            if (oper == 0) {
                hashMapInsert(hashMap, randArr[index], randArr[index]);
            } else if (oper == 1) {
                hashMapDelete(hashMap, randArr[index]);
            } else {
                hashMapSearch(hashMap, randArr[index]);
            }
        }

        auto end   = std::chrono::high_resolution_clock::now(); 
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

        tempTime += duration.count();
    }

    auto end   = std::chrono::high_resolution_clock::now(); 
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    printf("%lld\n", duration.count());
}

void measureHashMapTime2(HashFunc_t hashFunc) {
    ON_ERROR(!hashFunc, "Nullptr", );

    HashMap_t *hashMap = hashMapNew(hashFunc);

    char *randArr[1000000] = {};
    for (int i = 0; i < 1000000; i++) {
        int wordLen = rand() % 100;
        char *word = (char*) calloc(wordLen+1, sizeof(char));

        for (int j = 0; j < wordLen; j++) {
            word[j] = rand() % CHAR_MAX;
        }
        word[wordLen] = '\0';

        randArr[i] = word;
    }

    auto start = std::chrono::high_resolution_clock::now(); 

    double tempTime = 0;

    for (int i = 10000; i <= 1000000; i += 10000) {
        fprintf(stderr, "%d %lld\n", i, tempTime);
        for (int j = 0; j < i; j += 4) {
            int index = rand() % 1000000;
            hashMapInsert(hashMap, randArr[index], randArr[index]);

            index = rand() % 1000000;
            hashMapInsert(hashMap, randArr[index], randArr[index]);

            index = rand() % 1000000;
            hashMapSearch(hashMap, randArr[index]);

            index = rand() % 1000000;
            hashMapDelete(hashMap, randArr[index]);
        }

        auto end   = std::chrono::high_resolution_clock::now(); 
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

        tempTime += duration.count();
    }

    auto end   = std::chrono::high_resolution_clock::now(); 
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    printf("%lld\n", duration.count());
}