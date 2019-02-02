#include "bucket.h"

static void expandCode(Bucket* bt)
{
	bt->code = (uint8_t*)realloc(bt->code, sizeof(uint8_t) * bt->capacity * 2);
	bt->capacity *= 2;
}

void initBucket(Bucket* bt)
{
	bt->capacity = 8;
	bt->count = 0;
	bt->code = (uint8_t*)malloc(sizeof(uint8_t) * 8);
	bt->tokens = initTokenArray();

	initValues(&bt->values);
}

void writeCode(Bucket* bt, uint8_t byte)
{
	if (bt->capacity < bt->count + 1)
		expandCode(bt);
	bt->code[bt->count] = byte;
	bt->count++;
}

int addBucketValue(Bucket* bt, Value value)
{
	return addValue(&bt->values, value);
}

void freeBucket(Bucket* bt)
{
	freeTokenArray(bt->tokens);
	freeValues(&bt->values);
	free(bt->code);
}