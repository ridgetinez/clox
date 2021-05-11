#include <stdlib.h>
#include <assert.h>

#include "chunk.h"
#include "memory.h"

static void initLines(Lines *lines)
{
    lines->count = 0;
    lines->capacity = 0;
    lines->spans = NULL;
}

static void writeLine(Lines *lines, int line, int instructionIndex)
{
    if (lines->count > 0 && lines->spans[lines->count-1].line == line) {
        lines->spans[lines->count-1].end = instructionIndex;
        return;
    }

    if (lines->capacity < lines->count + 1) {
        int oldCapacity = lines->capacity;
        lines->capacity = GROW_CAPACITY(oldCapacity);
        lines->spans = GROW_ARRAY(LineSpan, lines->spans,
            oldCapacity, lines->capacity);
    }
    lines->spans[lines->count].line = line;
    lines->spans[lines->count].start = instructionIndex;
    lines->spans[lines->count++].end = instructionIndex;
}

static void freeLines(Lines *lines)
{
    FREE_ARRAY(LineSpan, lines->spans, lines->capacity);
    initLines(lines);
}

void initChunk(Chunk *chunk)
{
    chunk->count = 0;
    chunk->capacity = 0;
    chunk->code = NULL;
    initLines(&chunk->lines);
    initValueArray(&chunk->constants);
}

void writeChunk(Chunk *chunk, uint8_t byte, int line)
{
    writeLine(&chunk->lines, line, chunk->count);
    if (chunk->capacity < chunk->count + 1) {
        int oldCapacity = chunk->capacity;
        chunk->capacity = GROW_CAPACITY(oldCapacity);
        chunk->code = GROW_ARRAY(uint8_t, chunk->code,
            oldCapacity, chunk->capacity);
    }
    chunk->code[chunk->count++] = byte;
}

void freeChunk(Chunk *chunk)
{
    FREE_ARRAY(uint8_t, chunk->code, chunk->capacity);
    freeLines(&chunk->lines);
    freeValueArray(&chunk->constants);
    initChunk(chunk);
}

static int writeConstantToValueArray(Chunk *chunk, Value value)
{
    writeValueArray(&chunk->constants, value);
    return chunk->constants.count - 1;
}

static void addLongConstant(Chunk *chunk, int index, int line)
{
    writeChunk(chunk, OP_CONSTANT_LONG, line);
    assert((255 & (255 << 8)) == 0);
    writeChunk(chunk, (index & (255 << 16)) >> 16, line);
    printf("%d DEBUG1: %d %d\n", index, chunk->code[chunk->count-1], (index & (255 << 16)) >> 16);
    writeChunk(chunk, (index & (255 << 8)) >> 8, line);
    printf("%d DEBUG2: %d %d\n", index, chunk->code[chunk->count-1], (index & (255 << 8)) >> 8);
    writeChunk(chunk, index & 255, line);
    printf("%d DEBUG3: %d %d\n", index, chunk->code[chunk->count-1], index & (255));
}

static void addShortConstant(Chunk *chunk, int index, int line)
{
    writeChunk(chunk, OP_CONSTANT, line);
    writeChunk(chunk, index, line);
}

void writeConstant(Chunk *chunk, Value value, int line)
{
    int constantIndex = writeConstantToValueArray(chunk, value);
    if (constantIndex < 256) addShortConstant(chunk, constantIndex, line);
    else addLongConstant(chunk, constantIndex, line);
}

// TODO(amartinez): Since the line spans increase monotonically, can speed this up 
// (if needed) with binary search.
int getLine(Chunk *chunk, int instrNo)
{
    for (int i = 0; i < chunk->lines.count; i++) {
        int instrNoStart = chunk->lines.spans[i].start, instrNoEnd = chunk->lines.spans[i].end;
        if (instrNoStart <= instrNo && instrNo <= instrNoEnd) return chunk->lines.spans[i].line;
    }
    return -1;
}