#ifndef HASH_H
#define HASH_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../LinkedList/list.h"

#if MAKE_CHECKS
#define ON_ERROR(expr, errStr, retVal) {                 \
    if (expr) {                                           \
        fprintf(stderr, "FATAL ERROR: %s\n", errStr);      \
        return retVal;                                      \
    }                                                        \
}                                                             \


#else
#define ON_ERROR(expr, errStr, retVal) {}
#endif

static int testArr[1000] = {0};

//==========CONSTANT SECTION==========
static const size_t POISON_HASH           = 0xDEADBEEF;
static const size_t DEFAULT_GNU_HASH      = 0xDED;
static const size_t DEFAULT_ARR_SIZE      = 1000;
static const int    SEARCH_TEST_CNT       = 1e5;
//====================================

typedef size_t (*HashFunc_t)(char* value);

struct HashMap_t {
    List_t *listArr     = nullptr;
    size_t  listCnt     = 0;

    HashFunc_t hashFunc = nullptr;
};
//=========HASHMAP FUNCS=======
HashMap_t  *hashMapNew   (HashFunc_t hashFunc);
void        hashMapCtor  (HashMap_t *hashMap, HashFunc_t hashFunc);
void        hashMapDelete(HashMap_t *hashMap);
void        hashMapDtor  (HashMap_t *hashMap);

void        hashMapInsert(HashMap_t *hashMap, char* key, char* value);
char* hashMapSearch(HashMap_t *hashMap, char* key);

//=========INT HASHES=======
static const int MOD_CONST = 1000;
size_t modHashi(int value);
size_t bitHashi(int value);

static const int   N = 1000000;
static const float A = 0.34;
size_t mulHashi(int value);

//=======FLOAT HASHES=======
size_t intHashf(float value);
size_t bitHashf(float value);

//======STRING HASHES=======
size_t lenHash(char* value);
size_t sumHash(char* value);
size_t polHash(char* value);

static const int HASH_MOD     = 33554432 - 1; // 2^25 - 1
static const int POLYNOMIAL_P = 7;
size_t crcHash(char* value);

#endif