#include "hash.h"

HashMap_t *hashMapNew(HashFunc_t hashFunc) {
    ON_ERROR(!hashFunc, "Nullptr", nullptr);

    HashMap_t *hashMap = (HashMap_t*) calloc(1, sizeof(HashMap_t));
    ON_ERROR(!hashMap, "Unable to alloc memory", nullptr);

    hashMapCtor(hashMap, hashFunc);

    return hashMap;
}

void hashMapCtor(HashMap_t *hashMap, HashFunc_t hashFunc) {
    ON_ERROR(!hashFunc || !hashMap, "Nullptr",);

    hashMap->hashFunc = hashFunc; 
}

void hashMapDelete(HashMap_t *hashMap) {
    ON_ERROR(!hashMap, "Nullptr",);

    hashMapDtor(hashMap);
    free(hashMap);
}

void hashMapDtor(HashMap_t *hashMap) {
    ON_ERROR(!hashMap, "Nullptr",);
    ON_ERROR(!hashMap->listArr, "Nullptr",);

    hashMap->hashFunc = nullptr;
}

void hashMapInsert(HashMap_t *hashMap, char* key, char* value) {
    ON_ERROR(!hashMap, "Nullptr", );

    size_t hashSum = hashMap->hashFunc(key) % SEARCH_TEST_CNT;

    while (hashSum < SEARCH_TEST_CNT && hashMap->arr[hashSum])
    {
        hashSum++;
    }

    if (hashSum < SEARCH_TEST_CNT) hashMap->arr[hashSum] = key;
}

void hashMapDelete(HashMap_t *hashMap, char* key) {
    ON_ERROR(!hashMap, "Nullptr", );

    size_t hashSum = hashMap->hashFunc(key) % SEARCH_TEST_CNT;

    while (hashSum < SEARCH_TEST_CNT)
    {
        if (hashMap->arr[hashSum] && !strcmp(hashMap->arr[hashSum], key)) {
            hashMap->arr[hashSum] = nullptr;
            return;
        }

        hashSum++;
    }
}

char* hashMapSearch(HashMap_t *hashMap, char* key) {
    ON_ERROR(!hashMap, "Nullptr", nullptr);

    size_t hashSum = hashMap->hashFunc(key) % SEARCH_TEST_CNT;

    while (hashSum < SEARCH_TEST_CNT)
    {
        if (hashMap->arr[hashSum] && !strcmp(hashMap->arr[hashSum], key)) return key;

        hashSum++;
    }
    
    return nullptr;
}