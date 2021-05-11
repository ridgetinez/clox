#include "common.h"
#include "debug.h"
#include "chunk.h"

int main(int argc, const char *argv[])
{
    Chunk chunk;
    initChunk(&chunk);
    // writeConstant(&chunk, 1.2, 123);
    // writeConstant(&chunk, 500, 124);    
    for (int i = 0; i <= 256; i++) writeConstant(&chunk, i, i);
    writeChunk(&chunk, OP_RETURN, 257);
    disassembleChunk(&chunk, "test chunk");
    freeChunk(&chunk);

    return 0;
}