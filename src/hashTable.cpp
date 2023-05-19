#include "hash.h"

HashMap_t *hashMapNew(HashFunc_t hashFunc, CompareFunc_t compFunc, 
                      CopyFunc_t copyFunc, FreeFunc_t    freeFunc) {
    ON_ERROR(!hashFunc, "Nullptr", nullptr);

    HashMap_t *hashMap = (HashMap_t*) calloc(1, sizeof(HashMap_t));
    ON_ERROR(!hashMap, "Unable to alloc memory", nullptr);

    hashMapCtor(hashMap, hashFunc, compFunc, copyFunc, freeFunc);

    return hashMap;
}

void hashMapCtor(HashMap_t *hashMap, HashFunc_t hashFunc, CompareFunc_t compFunc, 
                                     CopyFunc_t copyFunc, FreeFunc_t    freeFunc) {

    ON_ERROR(!hashFunc || !hashMap || !compFunc || !copyFunc || !freeFunc, "Nullptr",);

    List_t *listArr = (List_t *) calloc(DEFAULT_ARR_SIZE, sizeof(List_t));
    ON_ERROR(!listArr, "Unable to alloc memory", );

    for (size_t i = 0; i < DEFAULT_ARR_SIZE; i++) {
        _listCtor(&listArr[i], 1, 0);
    }

    hashMap->listArr  = listArr;
    hashMap->listCnt  = DEFAULT_ARR_SIZE;  

    hashMap->hashFunc    = hashFunc;
    hashMap->compareFunc = compFunc;
    hashMap->copyFunc    = copyFunc;
    hashMap->freeFunc    = freeFunc;
}

void hashMapDelete(HashMap_t *hashMap) {
    ON_ERROR(!hashMap, "Nullptr",);

    hashMapDtor(hashMap);
    free(hashMap);
}

void hashMapDtor(HashMap_t *hashMap) {
    ON_ERROR(!hashMap, "Nullptr",);
    ON_ERROR(!hashMap->listArr, "Nullptr",);

    for (size_t i = 0; i < hashMap->listCnt; i++) {
        List_t listToFree = hashMap->listArr[i];

        for (size_t j = 0; j < listToFree.size + 1; j++) {
            free((char*) listToFree.values[j].value.key);
            free((char*) listToFree.values[j].value.value);
        }

        listDtor(&listToFree);
    }

    free(hashMap->listArr);
}

void hashMapInsert(HashMap_t *hashMap, void *key, void *value) {
    ON_ERROR(!hashMap || !key || !value, "Nullptr",);

    size_t hashSum = hashMap->hashFunc(key) % hashMap->listCnt;
    
    Pair_t addPair = {
        .key       = hashMap->copyFunc(key),
        .value     = hashMap->copyFunc(value)
    };
    listPushBack(&(hashMap->listArr[hashSum]), addPair);
}

void *hashMapSearch(HashMap_t *hashMap, void *key) {
    ON_ERROR(!hashMap || !(hashMap->listArr) || !key, "Nullptr", nullptr);

    size_t  hashSum    = hashMap->hashFunc(key) % hashMap->listCnt;
    List_t  searchList = hashMap->listArr[hashSum];

    Elem_t compareElement = {
        .key = key,
    };

    return listFind(&searchList, &compareElement, hashMap->compareFunc)->value.value;
}