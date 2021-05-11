#pragma once

#include "common.h"

typedef double Value;

typedef struct {
    int capacity;
    int count;
    Value *values;
} ValueArray;

// initValueArray initialises a ValueArray.
void initValueArray(ValueArray *array);

// writeValueArray appends a value to the ValueArray.
void writeValueArray(ValueArray* array, Value value);

// freeValueArray releases allocated memory from the ValueArray.
void freeValueArray(ValueArray* array);

// printValue prints a human readable format of value.
void printValue(Value value);