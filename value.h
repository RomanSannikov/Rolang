#ifndef rolang_value_h
#define rolang_value_h

#include <stdlib.h>

typedef double Value;

typedef struct
{
	unsigned int capacity;
	unsigned int count;
	Value* values;
} ValueArray;

void initValues(ValueArray*);
void expandValues(ValueArray*);
int addValue(ValueArray*, Value value);
void freeValues(ValueArray*);

#endif