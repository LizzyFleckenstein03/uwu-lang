#include <stdlib.h>
#include "../src/util.h"
#include "int.h"

UwUVMValue uwuint_create(int value)
{
	UwUVMValue vm_value = {
		.type = &uwuint_type,
		.data = malloc(sizeof(int))
	};
	*(int *) vm_value.data = value;

	return vm_value;
}

void *uwuint_copy(void *data)
{
	int *copy = malloc(sizeof(*copy));
	*copy = *(int *) data;
	return copy;
}

char *uwuint_print(void *data)
{
	return asprintf_wrapper("%d", *(int *) data);
}

UwUVMType uwuint_type = {
	.copy = &uwuint_copy,
	.delete = &free,
	.print = &uwuint_print,
};
