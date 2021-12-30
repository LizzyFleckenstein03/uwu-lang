#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "common/err.h"
#include "parse.h"

#define DEBUG 0

#if DEBUG
#define DBG(FN) printf("%s %s %s\n", FN, expression_types[state->expression->type], (state->expression->type == EX_FNCALL && state->expression->value.str_value) ? state->expression->value.str_value : "");
#else
#define DBG(FN)
#endif

#if DEBUG
static char *expression_types[EX_FNCALL + 1] = {
	"uninitialized",
	"integer-literal",
	"string-literal",
	"argument-number",
	"function-name",
	"function-call",
};

static void print_expression(ParseExpression *expr, int indent)
{
	for (int i = 0; i < indent; i++)
		printf("\t");

	printf("%s ", expression_types[expr->type]);

	if (expr->type == EX_INTLIT || expr->type == EX_ARGNUM)
		printf("%d\n", expr->value.int_value);
	else
		printf("\"%s\"\n", expr->value.str_value);

	if (expr->type == EX_FNCALL)
		for (size_t i = 0; i < expr->num_children; i++)
			print_expression(expr->children[i], indent + 1);
}

static void print_ast(AbstractSyntaxTree tree)
{
	printf("\n[Abstract Syntax Tree]\n\n");

	for (size_t f = 0; f < tree.num_functions; f++) {
		ParseFunction *function = tree.functions[f];

		printf("function %s\n", function->name);
		print_expression(function->expression, 1);
	}
}
#endif

static void buffer_append(ParseState *state, char c)
{
	state->buffer = realloc(state->buffer, ++state->buffer_size);
	state->buffer[state->buffer_size - 1] = c;
}

static char *buffer_terminate(ParseState *state)
{
	buffer_append(state, '\0');

	char *buffer = state->buffer;

	state->buffer = NULL;
	state->buffer_size = 0;

	return buffer;
}

static void start_arg(ParseState *state)
{
	DBG(__FUNCTION__)

	ParseExpression *parent = state->expression;
	parent->children = realloc(parent->children, sizeof *parent->children * ++parent->num_children);
	ParseExpression *child = parent->children[parent->num_children - 1] = malloc(sizeof *child);

	child->type = EX_UNINIT;
	child->parent = parent;

	state->expression = child;
}

static bool continue_arg(ParseState *state, char c)
{
	DBG(__FUNCTION__)

	if (c == ',')
		start_arg(state);
	else if (c == ')')
		state->expression = state->expression->parent;
	else if (! isspace(c))
		return false;

	return true;
}

static bool finish_arg(ParseState *state, char c)
{
	state->expression = state->expression->parent;

	if (state->expression)
		continue_arg(state, c);
	else if (! isspace(c))
		return false;

	return true;
}

static bool parse_expression_init(ParseState *state, char c)
{
	DBG(__FUNCTION__)

	if (c == ',')
		return false;

	if (isspace(c))
		return true;

	switch (c) {
		case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':
			state->expression->type = EX_INTLIT;
			buffer_append(state, c);
			return true;

		case '"':
			state->expression->type = EX_STRLIT;
			return true;

		case '$':
			state->expression->type = EX_ARGNUM;
			return true;

		case '&':
			state->expression->type = EX_FNNAME;
			return true;

		default:
			state->expression->type = EX_FNCALL;
			state->expression->value.str_value = NULL;
			buffer_append(state, c);
			return true;
	}
}

static bool parse_expression_finish(ParseState *state, char c)
{
	DBG(__FUNCTION__)

	if (state->expression->type == EX_ARGNUM && state->buffer_size == 0)
		return false;

	char *buffer_read = buffer_terminate(state);

	if (state->expression->type == EX_INTLIT || state->expression->type == EX_ARGNUM) {
		state->expression->value.int_value = atoi(buffer_read);
		free(buffer_read);
	} else {
		state->expression->value.str_value = buffer_read;
	}

	if (state->expression->type == EX_FNCALL) {
		state->expression->num_children = 0;
		state->expression->children = NULL;

		if (c == '(')
			start_arg(state);
		else
			return finish_arg(state, c);
	} else {
		if (c == ',' || c == ')')
			return finish_arg(state, c);
		else
			state->expression = state->expression->parent;
	}

	return true;
}

static bool parse_expression_continue(ParseState *state, char c)
{
	DBG(__FUNCTION__)

	if (state->expression->type == EX_FNCALL && state->expression->value.str_value)
		return continue_arg(state, c);

	if (
		state->expression->type == EX_STRLIT
		? c == '"'
		: (
			(state->expression->type == EX_FNCALL && c == '(')
			|| isspace(c) || c == ',' || c == ')'
		)
	) {
		return parse_expression_finish(state, c);
	} else {
		if ((state->expression->type == EX_INTLIT || state->expression->type == EX_ARGNUM) && ! isdigit(c))
			return false;

		if ((state->expression->type == EX_FNNAME || state->expression->type == EX_FNCALL) && (c == '&' || c == '$'))
			return false;

		buffer_append(state, c);
	}

	return true;
}

static bool parse_expression(ParseState *state, char c)
{
	DBG(__FUNCTION__)

	return state->expression->type == EX_UNINIT
		? parse_expression_init(state, c)
		: parse_expression_continue(state, c);
}

static bool parse_function(ParseState *state, char c)
{
#if DEBUG
	printf("%s\n", __FUNCTION__);
#endif

	if (c == '\"' || c == '$' || c == ':' || c == ',' || c == '&' || c == '(' || c == ')' || isdigit(c))
		return false;

	if (! isspace(c)) {
		buffer_append(state, c);
		return true;
	}

	if (state->buffer_size == 0)
		return true;

	char *name = buffer_terminate(state);

	state->expression = malloc(sizeof *state->expression);
	state->expression->type = EX_UNINIT;
	state->expression->parent = NULL;

	state->tree.functions = realloc(state->tree.functions, sizeof *state->tree.functions * ++state->tree.num_functions);
	*(state->tree.functions[state->tree.num_functions - 1] = malloc(sizeof(ParseFunction))) = (ParseFunction) {
		.name = name,
		.expression = state->expression,
	};

	return true;
}

static bool parse_character(ParseState *state, char c)
{
#if DEBUG
	printf("\nparse_character ");

	if (isspace(c))
		printf("<SPACE>");
	else
		printf("%c", c);

	 printf("\n");
#endif

	return state->expression
		? parse_expression(state, c)
		: parse_function(state, c);
}

AbstractSyntaxTree parse_file(const char *filename)
{
	ParseState state = {
		.tree = {
			.num_functions = 0,
			.functions = NULL,
		},
		.buffer_size = 0,
		.buffer = NULL,
		.expression = NULL,
	};

	int lines = 1;

	FILE *f = fopen(filename, "r");

	if (! f)
		syserror("fopen", f);

#if DEBUG
	printf("[File %s]\n[Line %d]\n", filename, lines);
#endif

	while (true) {
		char c = getc(f);

		if (feof(f))
			break;

		if (ferror(f))
			syserror("getc", f);

		if (c == '\n')
			++lines;

#if DEBUG
		if (c == '\n')
			printf("\n[Line %d]\n", lines);
#endif

		if (! parse_character(&state, c))
			error("syntax error: in file %s, line %d\n", filename, lines);
	}

	if (state.buffer || state.expression)
		error("syntax error: at end of file %s\n", filename);

	fclose(f);

#if DEBUG
	print_ast(state.tree);
#endif

	return state.tree;
}
