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

    List_t *listArr = (List_t *) calloc(DEFAULT_ARR_SIZE, sizeof(List_t));
    ON_ERROR(!listArr, "Unable to alloc memory", );

    for (size_t i = 0; i < DEFAULT_ARR_SIZE; i++) {
        _listCtor(&listArr[i], 10, 0);
    }

    hashMap->listArr  = listArr;
    hashMap->hashFunc = hashFunc;
    hashMap->listCnt  = DEFAULT_ARR_SIZE;  
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

        // for (size_t j = 0; j < listToFree.size + 1; j++) {
        //     free((char*) listToFree.values[j].value.key);
        //     free((char*) listToFree.values[j].value.value);
        // }

        listDtor(&listToFree);
    }

    free(hashMap->listArr);
}

void hashMapInsert(HashMap_t *hashMap, char* key, char* value) {
    ON_ERROR(!hashMap || !key || !value, "Nullptr",);

    size_t hashSum = hashMap->hashFunc(key) % hashMap->listCnt;

    Pair_t addPair = {
        .key       = strdup(key),
        .value     = strdup(value)
    };
    listPushBack(&(hashMap->listArr[hashSum]), addPair);
}

bool comparator(Elem_t *val1, Elem_t *val2) {
    if (!val1->key || !val2->key) return false;
    return !strcmp(val1->key, val2->key);
}

void hashMapDelete(struct HashMap_t *hashMap, char* key) {
    ON_ERROR(!hashMap, "Nullptr", );

    int hashSum = hashMap->hashFunc(key) % hashMap->listCnt;

    Pair_t cmpElem = {
        .key = key
    };

    listDelete(&(hashMap->listArr[hashSum]), &cmpElem, comparator);

    // listDump(&(hashMap->listArr[hashSum]));
}

char* hashMapSearch(HashMap_t *hashMap, char* key) {
    ON_ERROR(!hashMap || !(hashMap->listArr) || !key, "Nullptr", nullptr);

    size_t  hashSum    = hashMap->hashFunc(key) % hashMap->listCnt;
    List_t  searchList = hashMap->listArr[hashSum];

    Elem_t compareElement = {
        .key = key,
    };

    ListElement_t *found = listFind(&searchList, &compareElement, comparator);

    if (found) return found->value.value;
    return nullptr;
}