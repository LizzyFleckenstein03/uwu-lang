#ifndef _API_VM_H_
#define _API_VM_H_

#include <stddef.h>
#include <stdbool.h>

typedef enum
{
	MODULE_PLAIN,
	MODULE_NATIVE,
} UwUVMModuleType;

typedef enum
{
	EX_UNINIT,
	EX_INTLIT,
	EX_STRLIT,
	EX_ARGNUM,
	EX_FNNAME,
	EX_FNCALL,
} UwUVMExpressionType;

typedef struct
{
	void *(*clone)(void *data);
	void  (*delet)(void *data);
	char *(*print)(void *data);
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
	UwUVMExpressionType type;
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

UwUVMValue uwuvm_clone_value(UwUVMValue value);
void       uwuvm_delet_value(UwUVMValue value);
char      *uwuvm_print_value(UwUVMValue value);
UwUVMValue uwuvm_get_arg(UwUVMArgs *args, size_t i);
UwUVMValue uwuvm_evaluate_expression(UwUVMExpression *expression, UwUVMArgs *args);
UwUVMValue uwuvm_call_function(UwUVMFunction *function, size_t num_args, UwUVMExpression *unevaluated_args, UwUVMArgs *super_args);

#endif
