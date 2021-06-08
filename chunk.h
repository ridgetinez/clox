#pragma once

#include "common.h"
#include "value.h"

// OpCode corresponds to bytecode instruction codes.
typedef enum {
    OP_RETURN,
    OP_CONSTANT,
    OP_CONSTANT_LONG,
    OP_NIL,
    OP_TRUE,
    OP_FALSE,
    OP_NOT,
    OP_NEGATE,
    OP_EQUAL,
    OP_GREATER,
    OP_LESS,
    OP_ADD,
    OP_SUBTRACT,
    OP_MULTIPLY,
    OP_DIVIDE,
} OpCode;

typedef struct {
    int line;
    int start;
    int end;
} LineSpan;

typedef struct {
    int count;
    int capacity;
    LineSpan *spans;
} Lines;

// Chunk is a dynamically sized array of bytecode instructions.
typedef struct {
    int count;
    int capacity;
    uint8_t *code;
    Lines lines;
    ValueArray constants;
} Chunk;

// initChunk initialises a non-null chunk pointer.
void initChunk(Chunk *chunk);

// writeChunk appends an instruction to the chunk with OpCode corresponding to byte.
void writeChunk(Chunk *chunk, uint8_t byte, int line);

// freeChunk releases the allocated memory associated with the chunk.
void freeChunk(Chunk *chunk);

// writeConstant appends a constant to the Chunk's constant pool AND
// writes the OP_CONSTANT* instruction.
void writeConstant(Chunk *chunk, Value value, int line);

// getLine gets the code line corresponding to a bytecode instruction within the chunk.
int getLine(Chunk *chunk, int instructionIndex);