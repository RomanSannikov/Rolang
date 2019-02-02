#include "value.h"

void initValues(ValueArray* va)
{
	va->capacity = 8;
	va->count = 0;
	va->values = (Value*)malloc(sizeof(Value) * 8);
}

void expandValues(ValueArray* va)
{
	va->values = (Value*)realloc(va->values, sizeof(Value) * va->capacity * 2);
	va->capacity *= 2;
}

int addValue(ValueArray* va, Value value)
{
	if (va->capacity < va->count + 1)
		expandValues(va);
	va->values[va->count] = value;
	va->count++;
	return va->count - 1;
}

void freeValues(ValueArray* va)
{
	free(va->values);
}