#include <stdio.h>

#include "debug.h"

void disassembleChunk(Chunk *chunk, const char *name)
{
    printf("== %s == \n", name);

    for (int offset = 0; offset < chunk->count;) {
        offset = disassembleInstruction(chunk, offset);
    }
}

// simpleInstruction operates on instructions where control flow has one outgoing edge,
// with the next instruction being the next byte.
static int simpleInstruction(const char *name, int offset)
{
    printf("%s\n", name);
    return offset + 1;
}

// constantInstruction prints out information relating to the constant instruction.
static int constantInstruction(const char *name, Chunk *chunk, int offset)
{
    uint8_t constantIndex = chunk->code[offset + 1];
    printf("%-16s %4d '", name, constantIndex);
    printValue(chunk->constants.values[constantIndex]);
    printf("'\n");
    return offset + 2;
}

// constantInstruction prints out information relating to the constant instruction.
static int constantLongInstruction(const char *name, Chunk *chunk, int offset)
{
    int constantIndex = (chunk->code[offset+1] << 16) \
        | (chunk->code[offset+2] << 8) \
        | (chunk->code[offset+3]);
    printf("%-16s %4d '", name, constantIndex);
    printValue(chunk->constants.values[constantIndex]);
    printf("'\n");
    return offset + 4;
}

int disassembleInstruction(Chunk *chunk, int offset)
{
    printf("%04d ", offset);

    // print out the line number, if the same hasn't been printed previously.
    int lineNoCurr = getLine(chunk, offset), lineNoPrev = getLine(chunk, offset-1);
    if (offset > 0 && lineNoCurr == lineNoPrev) printf("   | ");
    else printf("%4d ", lineNoCurr);

    uint8_t instruction = chunk->code[offset];
    switch (instruction) {
        case OP_RETURN:
            return simpleInstruction("OP_RETURN", offset);
        case OP_CONSTANT:
            return constantInstruction("OP_CONSTANT", chunk, offset);
        case OP_CONSTANT_LONG:
            return constantLongInstruction("OP_CONSTANT_LONG", chunk, offset);
        default:
            printf("Unknown opcode %d\n", instruction);
            return offset + 1;
    }
}