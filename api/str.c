#include <string.h>
#include <stdlib.h>
#include "str.h"

UwUVMValue uwustr_create(const char *value)
{
	return (UwUVMValue) {
		.type = &uwustr_type,
		.data = strdup(value),
	};
}

char *uwustr_get(UwUVMValue vm_value)
{
	vm_value.type->print(vm_value.data);
}

static void *uwustr_copy(void *data)
{
	return strdup(data);
}

static char *uwustr_print(void *data)
{
	return strdup(data);
}

UwUVMType uwustr_type = {
	.copy = &uwustr_copy,
	.delete = &free,
	.print = &uwustr_print,
};
