#include <dlfcn.h>
#include <stdlib.h>
#include <stdio.h>
#include "common/err.h"
#include "common/dl.h"
#include "load.h"
#include "run.h"

static void free_expression(UwUVMExpression *expr)
{
	if (expr->type == EX_FNCALL) {
		for (size_t i = 0; i < expr->value.cll_value.num_args; i++)
			free_expression(&expr->value.cll_value.args[i]);

		free(expr->value.cll_value.args);
	}

	if (expr->type == EX_STRLIT)
		free(expr->value.str_value);
}

void run_module(const char *progname, const char *modname, size_t num_args, char *args[])
{
	(void) num_args;
	(void) args;

	Program program = load_program(progname, modname);

	UwUVMValue (*uwuvm_call_function)(UwUVMFunction *, size_t, UwUVMExpression *, UwUVMArgs *) = dlsym(program.api_library, "uwuvm_call_function");
	char      *(*uwuvm_print_value  )(UwUVMValue                                             ) = dlsym(program.api_library, "uwuvm_print_value"  );
	void       (*uwuvm_delet_value  )(UwUVMValue                                             ) = dlsym(program.api_library, "uwuvm_delet_value"  );

	check_dlerror();

	UwUVMExpression arg_expressions[num_args];

	for (size_t i = 0; i < num_args; i++)
		arg_expressions[i] = (UwUVMExpression) {
			.type = EX_STRLIT,
			.value = {
				.str_value = args[i],
			},
		};

	UwUVMValue result = uwuvm_call_function(program.main_function, num_args, arg_expressions, NULL);

	char *str = uwuvm_print_value(result);
	printf("%s\n", str);
	free(str);

	uwuvm_delet_value(result);

	for (size_t i = 0; i < program.num_functions; i++) {
		UwUVMFunction *function = program.functions[i];

		if (function->type == MODULE_PLAIN) {
			free_expression(function->value.plain);
			free(function->value.plain);
		}

		free(function);
	}

	free(program.functions);

	for (size_t i = 0; i < program.num_libraries; i++)
		dlclose(program.libraries[i]);

	if (program.libraries)
		free(program.libraries);

	dlclose(program.api_library);
}
