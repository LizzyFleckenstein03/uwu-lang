#include <stdlib.h>
#include "common/str.h"
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

int uwuint_get(UwUVMValue vm_value)
{
	return *(int *) vm_value.data;
}

void *uwuint_clone(void *data)
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
	.clone = &uwuint_clone,
	.delet = &free,
	.print = &uwuint_print,
};
