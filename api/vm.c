#include <stdio.h>
#include <stdlib.h>
#include "../src/err.h"
#include "vm.h"
#include "str.h"
#include "int.h"

void uwuvm_free_value(UwUVMValue value)
{
	if (value.type == VT_STR)
		free(value.value.str_value);
	else if (value.type == VT_NAT)
		value.value.nat_value.type->delete(value.value.nat_value.data);
}

void uwuvm_free_args(UwUVMArgs *args)
{
	if (args->evaluated) {
		for (size_t i = 0; i < args->num; i++) {
			UwUVMValue *value = args->evaluated[i];

			if (value) {
				uwuvm_free_value(*value);
				free(value);
			}
		}

		free(args->evaluated);
	}
}

UwUVMValue uwuvm_copy_value(UwUVMValue value)
{
	if (value.type == VT_STR)
		return uwustr_create(value.value.str_value);
	else if (value.type == VT_NAT)
		return (UwUVMValue) {
			.type = value.type,
			.value = {
				.nat_value = {
					.type = value.value.nat_value.type,
					.data = value.value.nat_value.type->copy(value.value.nat_value.data),
				}
			}
		};
	else
		return value;
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
			if ((size_t) expression->value.int_value >= args->num) 
				error("error: not enough arguments (accessed argument $%d, but only %lu arguments were passed)\n", expression->value.int_value, args->num);

			return uwuvm_copy_value(uwuvm_get_arg(args, expression->value.int_value));

		case EX_FNNAME:
			return (UwUVMValue) {
				.type = VT_REF,
				.value = {
					.ref_value = expression->value.ref_value,
				},
			};

		case EX_FNCALL:
			return uwuvm_run_function(expression->value.cll_value.function, (UwUVMArgs) {
				.num = expression->value.cll_value.num_args,
				.evaluated = expression->value.cll_value.num_args == 0 ? NULL : calloc(expression->value.cll_value.num_args, sizeof(UwUVMValue *)),
				.unevaluated = expression->value.cll_value.args,
				.super = args,
			});

		default:
			return (UwUVMValue) {};
	}
}

UwUVMValue uwuvm_run_function(UwUVMFunction *function, UwUVMArgs args)
{
	UwUVMValue value = function->type == MODULE_PLAIN
		? uwuvm_evaluate_expression(function->value.plain, &args)
		: function->value.native(&args);

	uwuvm_free_args(&args);
	return value;
}
