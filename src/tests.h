#ifndef TESTS_H
#define TESTS_H

#include <limits.h>

#include "hash.h"

static const int TEST_COUNT = 1e6;

void countDeviation(HashMap_t *hashMapArr[], size_t arrSize);
HashMap_t *createHashMapRandData(const int testCount, HashFunc_t hashFunc);
void measureHashDistribution(HashFunc_t funcs[], size_t arrSize);

void measureHashMapTime (HashFunc_t hashFunc);
void measureHashMapTime2(HashFunc_t hashFunc);

#endif