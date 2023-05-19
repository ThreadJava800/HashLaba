#ifndef TESTS_H
#define TESTS_H

#include <limits.h>

#include "hash.h"

static const int TEST_COUNT = 1e6;

int   *createRandomIntArr  (const int testCount);
float *createRandomFloatArr(const int testCount);
char  *createRandomCharArr (const int testCount);

void countDeviation         (HashMap_t *hashMapArr[]);
void measureHashDistribution();

#endif