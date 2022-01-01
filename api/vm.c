#include <stdio.h>
#include <stdlib.h>
#include "common/err.h"
#include "vm.h"
#include "str.h"
#include "ref.h"
#include "int.h"

UwUVMValue uwuvm_clone_value(UwUVMValue value)
{
	return (UwUVMValue) {
		.type = value.type,
		.data = value.type->clone(value.data),
	};
}

void uwuvm_delet_value(UwUVMValue value)
{
	value.type->delet(value.data);
}

char *uwuvm_print_value(UwUVMValue value)
{
	return value.type->print(value.data);
}

UwUVMValue uwuvm_get_arg(UwUVMArgs *args, size_t i)
{
	if (! args->evaluated[i]) {
		args->evaluated[i] = malloc(sizeof(UwUVMValue));
		*(args->evaluated[i]) = uwuvm_evaluate_expression(&args->unevaluated[i], args->super);
	}

	return *(args->evaluated[i]);
}

UwUVMValue uwuvm_evaluate_expression(UwUVMExpression *expression, UwUVMArgs *args)
{
	switch (expression->type) {
		case EX_INTLIT:
			return uwuint_create(expression->value.int_value);

		case EX_STRLIT:
			return uwustr_create(expression->value.str_value);

		case EX_ARGNUM:
			if (expression->value.int_value == 0)
				error("type error: trying to access argument $0\n");
			if ((size_t) expression->value.int_value > args->num)
				error("type error: trying to access argument $%d, but only %lu arguments were passed)\n", expression->value.int_value, args->num);

			return uwuvm_clone_value(uwuvm_get_arg(args, expression->value.int_value - 1));

		case EX_FNNAME:
			return uwuref_create(expression->value.ref_value);

		case EX_FNCALL:
			return uwuvm_call_function(
				expression->value.cll_value.function,
				expression->value.cll_value.num_args,
				expression->value.cll_value.args,
				args
			);

		default:
			return (UwUVMValue) {};
	}
}

UwUVMValue uwuvm_call_function(UwUVMFunction *function, size_t num_args, UwUVMExpression *unevaluated_args, UwUVMArgs *super_args)
{
	UwUVMValue *evaluated_args[num_args];

	for (size_t i = 0; i < num_args; i++)
		evaluated_args[i] = NULL;

	UwUVMArgs args = {
		.num = num_args,
		.evaluated = evaluated_args,
		.unevaluated = unevaluated_args,
		.super = super_args,
	};

	UwUVMValue return_value = function->type == MODULE_PLAIN
		? uwuvm_evaluate_expression(function->value.plain, &args)
		: function->value.native(&args);

	if (num_args > 0) {
		for (size_t i = 0; i < num_args; i++) {
			UwUVMValue *value = evaluated_args[i];

			if (value) {
				uwuvm_delet_value(*value);
				free(value);
			}
		}

	}

	return return_value;
}
