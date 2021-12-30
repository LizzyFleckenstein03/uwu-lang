#ifndef _PARSE_H_
#define _PARSE_H_

#include <stddef.h>
#include <stdbool.h>
#include "api/vm.h"

typedef struct ParseExpression
{
	UwUVMExpressionType type;
	union
	{
		int   int_value;
		char *str_value;
	} value;
	size_t num_children;
	struct ParseExpression **children;
	struct ParseExpression *parent;
} ParseExpression;

typedef struct
{
	char *name;
	ParseExpression *expression;
} ParseFunction;

typedef struct
{
	size_t num_functions;
	ParseFunction **functions;
} AbstractSyntaxTree;

typedef struct
{
	AbstractSyntaxTree tree;

	size_t buffer_size;
	char *buffer;

	ParseExpression *expression;

	int lines;
	bool success;
} ParseState;

AbstractSyntaxTree parse_file(const char *filename);

#endif
