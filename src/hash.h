#ifndef HASH_H
#define HASH_H

#include <immintrin.h>
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

//==========CONSTANT SECTION==========
static const size_t POISON_HASH           = 0xDEADBEEF;
static const size_t DEFAULT_GNU_HASH      = 0xDED;
static const size_t DEFAULT_ARR_SIZE      = 127;
static const int    SEARCH_TEST_CNT       = 1e5;
//====================================

typedef size_t (*HashFunc_t)(void *value);
typedef void*  (*CopyFunc_t)(void *value);
typedef void   (*FreeFunc_t)(void *value);

struct HashMap_t {
    List_t *listArr     = nullptr;
    size_t  listCnt     = 0;

    HashFunc_t    hashFunc    = nullptr;
    CompareFunc_t compareFunc = nullptr;
    CopyFunc_t    copyFunc    = nullptr;
    FreeFunc_t    freeFunc    = nullptr;
};
//=========HASHMAP FUNCS=======
HashMap_t  *hashMapNew   (HashFunc_t hashFunc, CompareFunc_t compFunc, 
                          CopyFunc_t copyFunc, FreeFunc_t    freeFunc);
void        hashMapCtor  (HashMap_t *hashMap, HashFunc_t hashFunc, CompareFunc_t compFunc, 
                                              CopyFunc_t copyFunc, FreeFunc_t    freeFunc);
void        hashMapDelete(HashMap_t *hashMap);
void        hashMapDtor  (HashMap_t *hashMap);

void  hashMapInsert(HashMap_t *hashMap, void *key, void *value);
void *hashMapSearch(HashMap_t *hashMap, void *key);

//=========INT HASHES=======
static const int MOD_CONST = 1000;
int      modHashi(void *value);
unsigned bitHashi(void *value);

static const int   N = 1000000;
static const float A = 0.34;
int      mulHashi(void *value);

//=======FLOAT HASHES=======
int      intHashf(void *value);
unsigned bitHashf(void *value);

//======STRING HASHES=======
unsigned int lenHash(void *value);
unsigned int sumHash(void *value);
unsigned int polHash(void *value);

static const int HASH_MOD     = 33554432 - 1; // 2^25 - 1
static const int POLYNOMIAL_P = 7;
unsigned int crcHash(void *value);

#endif