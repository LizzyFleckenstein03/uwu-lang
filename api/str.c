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
	return uwuvm_print_value(vm_value);
}

static void *uwustr_clone(void *data)
{
	return strdup(data);
}

static char *uwustr_print(void *data)
{
	return strdup(data);
}

UwUVMType uwustr_type = {
	.clone = &uwustr_clone,
	.delet = &free,
	.print = &uwustr_print,
};
