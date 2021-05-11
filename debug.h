#pragma once

#include "chunk.h"

// disassembleChunk outputs the human readable representation of the chunk's instructions
// where chunk is labelled as the name parameter.
void disassembleChunk(Chunk *chunk, const char *name);

// diassembleInstruction outputs the human readable representation of instruction at index 
// offset in the chunk's instruction list. Returns the next instruction's index.
int disassembleInstruction(Chunk *chunk, int offset);