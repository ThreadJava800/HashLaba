#include "hash.h"

// INT HASHES
size_t modHashi(int value) {
    if (!value) return 0;

    return value % MOD_CONST;
}

size_t bitHashi(int value) {
    if (!value) return 0;

    size_t result = 0;
    size_t mulInd = 1;

    for (int i = 0; i < 10; i++) {
        result += (value & 0x01) * mulInd;
        mulInd *= 10;

        value >>= 1;
    }
    
    return result;
}

size_t mulHashi(int value) {
    if (!value) return 0;

    float realPart = 0;
    float fracPart = modf(value * A, &realPart);

    // printf("%lu\n", floor(N * fracPart));

    return floor(N * fracPart);
}

// FLOAT HASHES
size_t intHashf(float value) {
    return (size_t) (value);
}

size_t bitHashf(float value) {
    int *bitValue = reinterpret_cast<int *>(&value);

    return bitHashi(*bitValue);
}

// STRING HASHES
size_t lenHash(char *value) {
    if (!value) return 0;

    const char *sPtr = (const char *) value;

    return strlen(sPtr);
}

size_t sumHash(char *value) {
    if (!value) return 0;

    const char *sPtr = (const char *) value;

    size_t sum = 0;

    while (*sPtr != '\0') {
        sum += (*sPtr);
        ++sPtr;
    }
    
    return sum;
}

size_t polHash(char *value) {
    if (!value) return 0;

    const char *sPtr = (const char *) value;

    int hash = 0;
    int p    = 1;

    size_t valueLen = strlen(sPtr);

    for (size_t i = 0; i < valueLen; i++) {
        hash = (hash + ((size_t) sPtr[valueLen - i - 1] * p) % HASH_MOD) % HASH_MOD;
        p    = (p * POLYNOMIAL_P) % HASH_MOD;
    }
    
    return hash;
}

size_t crcHash(char *value) {
    if (!value) return 0;

    int hash = 0xFFFFFFFF, mask = 0;

    while (*value != '\0') {
        hash = hash ^ (*value);

        for (int j = 7; j >= 0; j--) {
            mask = -(hash & 1);
            hash = (hash >> 1) ^ (0xEDB88320UL & mask);
        }

        value++;
    }

    return ~hash;
}