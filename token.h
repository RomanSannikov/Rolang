#ifndef rolang_token_h
#define rolang_token_h

#include <stdlib.h>
#include <string.h>

typedef enum
{
	TOKEN_NUMBER,
	TOKEN_STRING,
	
	TOKEN_VAR,

	TOKEN_LPARENTHESES, // (
	TOKEN_RPARENTHESES, // )

	TOKEN_SEMICOLON,

	// don't shift
	TOKEN_EQUAL,
	TOKEN_PLUS,
	TOKEN_MINUS,
	TOKEN_ASTERISK,
	TOKEN_SLASH,
	// don't shift

	TOKEN_EOT // End Of array of Tokens
} TokenType;

typedef struct Token
{
	char* data;
	struct Token* next;
	TokenType type;
} Token;

typedef struct
{
	Token* first;
	Token* current;
} TokenArray;

TokenArray* initTokenArray();
void addTokenData(TokenArray*, char*);
void freeTokenArray(TokenArray*);

#endif