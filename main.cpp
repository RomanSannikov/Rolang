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
	int counter;
	bool isWord = false;

	assert(file);

	for (counter = 0; !feof(file); counter++)
	{
		word[counter] = fgetc(file);

		if ((word[counter] == ' ' || word[counter] == '\n' || word[counter] == ';' || word[counter] == EOF) && isWord)
		{
			char* tempData = (char*)malloc(sizeof(char) * counter + 1);
			char lastChar = word[counter];
			
			word[counter] = '\0';
			strcpy(tempData, word);
			addTokenData(bt->tokens, tempData);
			counter = -1;
			isWord = false;

			if (lastChar == ';')
			{
				char* semicolon = (char*)malloc(sizeof(char) * 2);

				semicolon[0] = lastChar;
				semicolon[1] = '\0';
				addTokenData(bt->tokens, strcpy((char*)malloc(sizeof(char) * 2), semicolon));

				free(semicolon);
			}
		}
		else
			isWord = true;
	}

	addTokenData(bt->tokens, NULL);

	fclose(file);

#undef SIZE_OF_WORD
}


int main(int argc, char* argv[])
{
	Bucket bucket;

	initVM();
	initBucket(&bucket);

	scanFile(&bucket, "code.txt");

	if (recognize(&bucket) != COMPILED_WELL)
	{
		printf("Cannot recognize...\n");
		freeBucket(&bucket);
		exit(1);
	}

	translate(&bucket);
	
	disassemble(&bucket);

	run(&bucket);

	freeBucket(&bucket);

	return (0);
}