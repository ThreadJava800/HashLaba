#include "hash.h"

// INT HASHES
int modHash(int value) {
    return value % MOD_CONST;
}

unsigned bitHash(int value) {
    unsigned result = 0;
    unsigned mulInd = 1;

    for (int i = 0; i < 10; i++) {
        result += (value & 0x01) * mulInd;
        mulInd *= 10;

        value >>= 1;
    }
    
    return result;
}

int mulHash(int value) {
    float realPart = 0;
    float fracPart = modf(value * A, &realPart);

    return floor(N * fracPart);
}

// FLOAT HASHES
int intHash(float value) {
    return (int) value;
}

unsigned bitHash(float value) {
    int *bitValue = reinterpret_cast<int *>(&value);

    printf("%d\n", *bitValue);

    return bitHash(*bitValue);
}

// STRING HASHES
unsigned int lenHash(const char *value) {
    if (!value) return 0;

    return strlen(value);
}

unsigned int sumHash(const char *value) {
    if (!value) return 0;

    int sum = 0;

    while (*value != '\0') {
        sum += (*value);
        ++value;
    }
    
    return sum;
}

unsigned int polHash(const char *value) {
    int hash = 0;
    int p    = 1;

    size_t valueLen = strlen(value);

    for (size_t i = 0; i < valueLen; i++) {
        hash = (hash + ((unsigned int)value[valueLen - i - 1] * p) % HASH_MOD) % HASH_MOD;
        p    = (p * POLYNOMIAL_P) % HASH_MOD;
    }
    
    return hash;
}

unsigned int crcHash(const char *value) {
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