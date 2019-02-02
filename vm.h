#ifndef rolang_vm_h 
#define rolang_vm_h

#include "value.h"
#include "bucket.h"
#include "token.h"

#define MAX_SIZE_OF_STACK 256

typedef enum
{
	COMPILED_WELL,
	COMPILATION_FELT
} CompilerError;

typedef struct
{
	Value stack[MAX_SIZE_OF_STACK];
	Value* stackTop;
} VM;

void resetStack();
void initVM();
CompilerError recognize(Bucket*);
// translator
void run(Bucket*);
void push(Value);
Value pop();
static bool isNumber(char*);

#endif 
