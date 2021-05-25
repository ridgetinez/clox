#include <stdio.h>

#include "common.h"
#include "compiler.h"
#include "debug.h"
#include "vm.h"

#define READ_BYTE() (*vm.ip++)
#define READ_SHORT_CONSTANT() (vm.chunk->constants.values[READ_BYTE()])
#define READ_LONG_CONSTANT() (vm.chunk->constants.values[READ_BYTE() << 16 | READ_BYTE() << 8 | READ_BYTE()])
#define BINARY_OP(op) \
    do { \
        double a = pop(); \
        double b = pop(); \
        push(a op b); \
    } while (false)

VM vm;

static void resetStack()
{
    vm.stackTop = vm.stack;
}

/*
static void inplace_modify(Value (*f)(Value))
{
    *(vm.stackTop - 1) = f(*(vm.stackTop - 1));
}

static Value negate(Value x)
{
    return -x;
}
*/

void initVM()
{
    resetStack();
}

void freeVM()
{
}

/*
static InterpretResult run()
{
    while (true) {
#ifdef DEBUG_TRACE_EXECUTION
        printf("          ");
        for (Value* slot = vm.stack; slot < vm.stackTop; slot++) {
            printf("[ ");
            printValue(*slot);
            printf(" ]");
        }
        printf("\n");        
        disassembleInstruction(vm.chunk, (int)(vm.ip - vm.chunk->code));
#endif
        uint8_t instruction = READ_BYTE();
        switch (instruction) {
            case OP_RETURN: {
                printValue(pop());
                printf("\n");
                return INTERPRET_OK;
            }
            case OP_CONSTANT: {
                push(READ_SHORT_CONSTANT());
                break;
            }
            case OP_CONSTANT_LONG: {
                push(READ_LONG_CONSTANT());
                break;
            }
            case OP_NEGATE: {
                inplace_modify(negate);
                break;
            }
            case OP_ADD:      BINARY_OP(+); break;
            case OP_SUBTRACT: BINARY_OP(-); break;
            case OP_MULTIPLY: BINARY_OP(*); break;
            case OP_DIVIDE:   BINARY_OP(/); break;
            default: {
                return INTERPRET_COMPILE_ERROR;
            }
        }
    }
}
*/

InterpretResult interpret(const char *source)
{
  compile(source);
  return INTERPRET_OK;;
}

void push(Value value)
{
    *(vm.stackTop++) = value;
}

Value pop()
{
    return *(--vm.stackTop);
}

#undef READ_BYTE
#undef READ_SHORT_CONSTANT
#undef READ_LONG_CONSTANT
#undef BINARY_OP