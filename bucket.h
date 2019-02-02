// bucket is a place where b code and values are stored
// bucket sounds funny, doesn't it

#ifndef rolang_bucket_h 
#define rolang_bucket_h

#include <stdlib.h>
#include <stdint.h>

#include "value.h"
#include "token.h"

typedef enum
{
	OP_PUSH, // push a constant
	OP_POP, // pop a constant
	OP_ADD,
	OP_SUB,
	OP_MUL,
	OP_DIV,
	OP_RETURN // return op has a value
} OP;

typedef struct
{
	unsigned int capacity;
	unsigned int count;
	uint8_t* code;
	ValueArray values;
	TokenArray tokens;
} Bucket;

void initBucket(Bucket*);
void writeCode(Bucket*, uint8_t); // writes to code
int addBucketValue(Bucket*, Value); // writes to values
static void expandCode(Bucket*);
void freeBucket(Bucket*);

#endif 
