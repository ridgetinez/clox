#pragma once

#include "common.h"

typedef enum {
    VAL_BOOL,
    VAL_NIL,
    VAL_NUMBER,
} ValueType;

typedef struct {
    ValueType type;
    union {
        bool boolean;
        double number;
    } as;
} Value;

typedef struct {
    int capacity;
    int count;
    Value *values;
} ValueArray;

#define IS_BOOL(value)    ((value).type == VAL_BOOL)
#define IS_NIL(value)     ((value).type == VAL_NIL)
#define IS_NUMBER(value)  ((value).type == VAL_NUMBER)

#define AS_BOOL(value)   ((value).as.boolean)
#define AS_NUMBER(value) ((value).as.number)

#define BOOL_VAL(value)   ((Value){VAL_BOOL, {.boolean = value}})
#define NIL_VAL           ((Value){VAL_NIL, {.number = 0}})
#define NUMBER_VAL(value) ((Value){VAL_NUMBER, {.number = value}})

// valuesEqual compares to value objects
bool valuesEqual(Value a, Value b);

// initValueArray initialises a ValueArray.
void initValueArray(ValueArray *array);

// writeValueArray appends a value to the ValueArray.
void writeValueArray(ValueArray* array, Value value);

// freeValueArray releases allocated memory from the ValueArray.
void freeValueArray(ValueArray* array);

// printValue prints a human readable format of value.
void printValue(Value value);