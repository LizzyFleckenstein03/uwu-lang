#ifndef _API_VM_H_
#define _API_VM_H_

#include <stddef.h>
#include <stdbool.h>
#include "../src/expression.h"

typedef enum
{
	MODULE_PLAIN,
	MODULE_NATIVE,
} UwUVMModuleType;

typedef struct
{
	void *(*copy  )(void *data);
	void  (*delete)(void *data);
	char *(*print )(void *data);
} UwUVMType;

typedef struct
{
	void *data;
	UwUVMType *type;
} UwUVMValue;

typedef struct UwUVMArgs
{
	size_t num;
	UwUVMValue              **evaluated;
	struct UwUVMExpression *unevaluated;
	struct UwUVMArgs *super;
} UwUVMArgs;

typedef UwUVMValue (*UwUVMNativeFunction)(UwUVMArgs *args);

typedef struct
{
	UwUVMModuleType type;
	union
	{
		struct UwUVMExpression *plain;
		UwUVMNativeFunction native;
	} value;
} UwUVMFunction;

typedef struct UwUVMExpression
{
	ExpressionType type;
	union
	{
		struct
		{
			UwUVMFunction *function;
			struct UwUVMExpression *args;
			size_t           num_args;
		}           cll_value;
		int         int_value;
		char       *str_value;
		UwUVMFunction *ref_value;
	} value;
} UwUVMExpression;

typedef struct
{
	void *api_library;
	UwUVMFunction *main_function;
	UwUVMFunction     **functions;
	size_t          num_functions;
	void     **libraries;
	size_t num_libraries;
} UwUVMProgram;

void uwuvm_free_value(UwUVMValue value);
void uwuvm_free_args(UwUVMArgs *args);
UwUVMValue uwuvm_copy_value(UwUVMValue value);
UwUVMValue uwuvm_get_arg(UwUVMArgs *args, size_t i);
UwUVMValue uwuvm_evaluate_expression(UwUVMExpression *expression, UwUVMArgs *args);
UwUVMValue uwuvm_run_function(UwUVMFunction *function, UwUVMArgs args);

#endif
