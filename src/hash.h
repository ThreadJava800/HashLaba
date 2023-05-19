#ifndef HASH_H
#define HASH_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//=========INT HASHES=======
static const int MOD_CONST = 1000;
int      modHash(int value);
unsigned bitHash(int value);

static const int   N = 1000000;
static const float A = 0.34;
int      mulHash(int value);

//=======FLOAT HASHES=======
int      intHash(float value);
unsigned bitHash(float value);

//======STRING HASHES=======
unsigned int lenHash(const char *value);
unsigned int sumHash(const char *value);
unsigned int polHash(const char *value);

static const int HASH_MOD     = 33554432 - 1; // 2^25 - 1
static const int POLYNOMIAL_P = 7;
unsigned int crcHash(const char *value);

#endif