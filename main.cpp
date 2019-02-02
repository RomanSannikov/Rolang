#include <string.h>
#include <assert.h>

#include "vm.h"
#include "bucket.h"
#include "disassembler.h"
#include "token.h"

void scanFile(Bucket* bt, const char* fileName)
{
#define SIZE_OF_WORD 256
	char word[SIZE_OF_WORD];
	FILE* file = fopen(fileName, "r");

	assert(file);

	for (int i = 0; !feof(file); i++)
	{
		word[i] = fgetc(file);

		if ((word[i] == ' ' || word[i] == '\n') && i != 0)
		{
			char* tempData = (char*)malloc(sizeof(char) * i);
			strncpy(tempData, word, i + 1);
			addTokenData(&bt->tokens, tempData);
			i = -1;
		}
	}

	addTokenData(&bt->tokens, NULL);

	fclose(file);

#undef SIZE_OF_WORD
}


int main(int argc, char* argv[])
{
	Bucket bucket;

	scanFile(&bucket, "code.txt");

	initVM();
	initBucket(&bucket);

	if (recognize(&bucket, &bucket.tokens) != COMPILED_WELL)
	{
		printf("Cannot recognize...\n");
		exit(1);
	}
	
	disassemble(&bucket);

	run(&bucket);

	freeBucket(&bucket);

	return (0);
}