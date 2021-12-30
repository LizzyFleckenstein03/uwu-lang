#include <dlfcn.h>
#include <stdlib.h>
#include <stdio.h>
#include "collect.h"
#include "vm.h"

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

void vm_run_file(const char *progname, const char *modname)
{
	UwUVMProgram program = create_program(progname, modname);
	UwUVMValue result = ((UwUVMValue (*)(UwUVMFunction *, size_t, UwUVMExpression *, UwUVMArgs *)) dlsym(program.api_library, "uwuvm_call_function"))(program.main_function, 0, NULL, NULL);

	char *str = ((char *(*)(UwUVMValue)) dlsym(program.api_library, "uwuvm_print_value"))(result);

	printf("%s\n", str);
	free(str);

	((void (*)(UwUVMValue)) dlsym(program.api_library, "uwuvm_delet_value"))(result);

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
