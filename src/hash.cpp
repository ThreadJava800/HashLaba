#include "hash.h"

// INT HASHES
int modHashi(void *value) {
    if (!value) return 0;

    int *intPtr = (int*) value;

    return (*intPtr) % MOD_CONST;
}

unsigned bitHashi(void *value) {
    if (!value) return 0;

    int *intPtr = (int*) value;

    unsigned result = 0;
    unsigned mulInd = 1;

    for (int i = 0; i < 10; i++) {
        result += (*(intPtr) & 0x01) * mulInd;
        mulInd *= 10;

        (*intPtr) >>= 1;
    }
    
    return result;
}

int mulHashi(void *value) {
    if (!value) return 0;

    int *intPtr = (int*) value;

    float realPart = 0;
    float fracPart = modf((*intPtr) * A, &realPart);

    return floor(N * fracPart);
}

// FLOAT HASHES
int intHashf(void *value) {
    float *fPtr = (float*) value;

    return (int) (*fPtr);
}

unsigned bitHashf(void *value) {
    int *bitValue = reinterpret_cast<int *>(&value);

    return bitHashi(bitValue);
}

// STRING HASHES
unsigned int lenHash(void *value) {
    if (!value) return 0;

    const char *sPtr = (const char *) value;

    return strlen(sPtr);
}

unsigned int sumHash(void *value) {
    if (!value) return 0;

    const char *sPtr = (const char *) value;

    int sum = 0;

    while (*sPtr != '\0') {
        sum += (*sPtr);
        ++sPtr;
    }
    
    return sum;
}

unsigned int polHash(void *value) {
    if (!value) return 0;

    const char *sPtr = (const char *) value;

    int hash = 0;
    int p    = 1;

    size_t valueLen = strlen(sPtr);

    for (size_t i = 0; i < valueLen; i++) {
        hash = (hash + ((unsigned int) sPtr[valueLen - i - 1] * p) % HASH_MOD) % HASH_MOD;
        p    = (p * POLYNOMIAL_P) % HASH_MOD;
    }
    
    return hash;
}

unsigned int crcHash(void *value) {
    if (!value) return 0;

    const char *sPtr = (const char *) value;

    int hash = 0xFFFFFFFF, mask = 0;

    while (*sPtr != '\0') {
        hash = hash ^ (*sPtr);

        for (int j = 7; j >= 0; j--) {
            mask = -(hash & 1);
            hash = (hash >> 1) ^ (0xEDB88320UL & mask);
        }

        sPtr++;
    }

    return ~hash;
}