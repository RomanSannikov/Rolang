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
	newToken->next = NULL;

	if (data == NULL)
	{
		newToken->type = TOKEN_EOT;
		newToken->data = NULL;
	}
	else
	{
		newToken->data = data;
	}

	if (ta->current == NULL)
	{
		ta->current = newToken;
	}
	else
	{
		ta->current->next = newToken;
		ta->current = ta->current->next;
	}

	if (ta->first == NULL)
		ta->first = newToken;
}

void freeTokenArray(TokenArray* ta)
{
	Token* current = ta->first, *last = NULL;

	while (current != NULL)
	{
		if(current->data != NULL)
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