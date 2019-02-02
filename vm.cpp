#include <ctype.h>
#include <stdio.h>

#include "vm.h"

VM vm;

void resetStack()
{
	vm.stackTop = vm.stack;
}

void initVM()
{
	resetStack();
}

void push(Value value)
{
	*vm.stackTop = value;
	vm.stackTop++;
}

Value pop()
{
	vm.stackTop--;
	return *vm.stackTop;
}

static bool isNumber(char* string)
{
	for (int i = 0; string[i] != '\0'; i++)
		if (!isdigit(string[i]))
			return false;
	return true;
}

static Value doNumber(char string[])
{
	// The functoin doesn't return any error value because the number's passed all tests to be a number
	Value value = 0;
	for (int i = 0, k = 1; string[i] > '0' - 1 && string[i] < '9' + 1; i++, k *= 10)
		value += string[i] * k;
	return value;
}

CompilerError recognize(Bucket* bt, TokenArray* ta)
{
	Token* token = (Token*)ta->first;

	while (token->type != TOKEN_EOT)
	{
		if (isNumber(token->data))
		{
			token->type = TOKEN_NUMBER;
		}
		else if (token->data == "+")
		{
			token->type = TOKEN_PLUS;
		}
		else if (token->data == "-")
		{
			token->type = TOKEN_MINUS;
		}
		else if (token->data == "*")
		{
			token->type = TOKEN_ASTERISK;
		}
		else if (token->data == "/")
		{
			token->type = TOKEN_SLASH;
		}
		else if (token->data == "(")
		{
			token->type = TOKEN_LPARENTHESES;
		}
		else if (token->data == ")")
		{
			token->type = TOKEN_RPARENTHESES;
		}
		else if (token->data == "=")
		{
			token->type = TOKEN_EQUAL;
		}
		else if (token->data == ";")
		{
			token->type = TOKEN_SEMICOLON;
		}
		else if (token->data == NULL)
		{
			token->type = TOKEN_EOT;
		}
	}

	return COMPILED_WELL;
}

void translate(Bucket* bt, TokenArray* ta)
{
#define SIZE_OF_STACK
	Token* token = ta->first;

	while (token->type != TOKEN_EOT)
	{
		if (token->type == TOKEN_NUMBER)
		{
			// using Reverse Polish notation
			// https://en.wikipedia.org/wiki/Reverse_Polish_notation
			TokenType stack[100]; // stack for operators
			int sp = 0; // stack pointer
			
			while (token->type != TOKEN_EOT || token->type != TOKEN_SEMICOLON)
			{
				if (token->type == TOKEN_PLUS || token->type == TOKEN_MINUS 
								|| token->type == TOKEN_ASTERISK || token->type == TOKEN_SLASH || token->type == TOKEN_LPARENTHESES)
				{
					stack[sp] = token->type;
					sp++;
				}
				else if (token->type == TOKEN_RPARENTHESES)
				{
					while (stack[sp] != TOKEN_RPARENTHESES)
					{
						sp--;
						switch (stack[sp])
						{
							case TOKEN_PLUS: writeCode(bt, OP_ADD); break;
							case TOKEN_MINUS: writeCode(bt, OP_SUB); break;
							case TOKEN_ASTERISK: writeCode(bt, OP_MUL); break;
							case TOKEN_SLASH: writeCode(bt, OP_DIV); break;
						}
					}
					sp--;
				}
				else
				{
					writeCode(bt, OP_PUSH);
					writeCode(bt, addBucketValue(bt, doNumber(token->data))); // Dat's weird, I agree
				}

				token = token->next;
			}
		}

		token = token->next;
	}
#undef SIZE_OF_STACK
}

void run(Bucket* bt)
{
#define BINARY_OP(op) do { \
						Value b = pop(); \
						Value a = pop(); \
						push(a op b); \
					} while(false);

	for (unsigned int pc = 0; pc < bt->count; pc++)
	{
		switch (bt->code[pc])
		{
		case OP_PUSH:
			push(bt->values.values[bt->code[pc + 1]]);
			pc++;
			break;
		case OP_POP:
			pop();
			break;
		case OP_ADD:
			BINARY_OP(+);
			break;
		case OP_SUB:
			BINARY_OP(-);
			break;
		case OP_MUL:
			BINARY_OP(*);
			break;
		case OP_DIV:
			BINARY_OP(/);
			break;
		case OP_RETURN:
			printf("IT'S POPPED %g\n", pop()); // very first time
			pc++;
			break;
		default:
			break;
		}
	}
#undef BINARY_OP
}