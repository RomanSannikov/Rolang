#include "disassembler.h"

static int disassembleInstruction(Bucket* bt, uint8_t byte, int offset)
{
	switch (byte)
	{
	case OP_PUSH:
		printf("OP_PUSH\t\t%g\n", bt->values.values[bt->code[offset + 1]]);
		return offset + 2;
	case OP_ADD:
		printf("OP_ADD\n");
		return offset + 1;
	case OP_SUB:
		printf("OP_SUB\n");
		return offset + 1;
	case OP_MUL:
		printf("OP_MUL\n");
		return offset + 1;
	case OP_DIV:
		printf("OP_DIV\n");
		return offset + 1;
	case OP_RETURN:
		printf("OP_RETURN\t%g\n", bt->values.values[bt->code[offset + 1]]);
		return offset + 2;
	default:
		printf("Unknown Instruction\n");
		return offset + 1;
	}
}

void disassemble(Bucket* bt)
{
	printf("--- Disassembling ---\n");
	for (unsigned int offset = 0; offset < bt->count;)
	{
		printf("%04d\t", offset);
		offset = disassembleInstruction(bt, bt->code[offset], offset);
	}
}