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
	UwUVMValue result = ((UwUVMValue (*)(UwUVMFunction *, UwUVMArgs args)) dlsym(program.api_library, "uwuvm_run_function"))(program.main_function, (UwUVMArgs) {.num = 0, .evaluated = NULL, .unevaluated = NULL, .super = NULL});

	char *str = ((char *(*)(UwUVMValue)) dlsym(program.api_library, "uwustr_get"))(result);

	printf("%s\n", str);
	free(str);

	((void (*)(UwUVMValue)) dlsym(program.api_library, "uwuvm_free_value"))(result);

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
