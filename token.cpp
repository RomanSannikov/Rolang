#include "token.h"

TokenArray* initTokenArray()
{
	TokenArray* ta = (TokenArray*)malloc(sizeof(TokenArray));

	ta->first = NULL;
	ta->current = NULL;

	return ta;
}

void addTokenData(TokenArray* ta, char* data)
{
	Token* newToken = (Token*)malloc(sizeof(Token));
	newToken->data = (char*)malloc(sizeof(char) * strlen(data) + 1);

	if (ta->current == NULL || ta->current == (Token*)0xcccccccc)
		ta->current = newToken;
	else
	{
		ta->current->next = newToken;
		ta->current = ta->current->next;
	}

	if (ta->first == NULL)
	{
		ta->first = newToken;
	}

	strcpy(newToken->data, data);
}

void freeTokenArray(TokenArray* ta)
{
	Token* current = ta->first, *last = NULL;

	while (current != NULL)
	{
		free(current->data);

		if (last != NULL)
			free(last);

		last = current;
		current = current->next;
	}

	if (last != NULL)
		free(last);

	free(ta);
}