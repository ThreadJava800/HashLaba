#include <time.h>
#include <chrono>

#define MAKE_CHECKS 0
#include "hash.h"
#include "tests.h"

// int funcs
void *intCopyFunc(void *value) {
    return value;
}

void intFreeFunc(void *value) {
    free((int*) value);
};

// bool intCmpFunc(void *value1, void* value2) {
//     ON_ERROR(!value1 || !value2, "Nullptr", false);

//     int *intVal1 = (int*) ((Pair_t*) value1)->key;
//     int *intVal2 = (int*) ((Pair_t*) value2)->key;

//     printf("%d\n", *intVal2);

//     return (intVal1) && (intVal2) && (*intVal1 == *intVal2);
// }


int main() {
    time((unsigned) NULL);

    measureHashMapTime(crcHash);

    // HashMap_t *hashMap = hashMapNew(crcHash);

    // auto start = std::chrono::high_resolution_clock::now(); 
    // for (int i = 0; i < 10000; i++) {
    //     hashMapInsert(hashMap, "test", "Test");
    // }
    // auto end   = std::chrono::high_resolution_clock::now(); 
    // auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    // printf("%lld\n", duration.count());

    // HashMap_t *hashMap = hashMapNew(crcHash);




    // HashFunc_t hashFuncs[4] = {
    //     lenHash,
    //     sumHash,
    //     polHash,
    //     crcHash
    // };

    // measureHashDistribution(hashFuncs, 4);

    // hashMapDelete(hashMap);

    // int val1 = 15, val2 = 15;
    // printf("%d %d\n", mulHashi(&val1), mulHashi(&val2));

    // for (int i = 0; i < 1000; i++) {
    //     printf("%d ", testArr[i]);
    // }

    return 0;
}