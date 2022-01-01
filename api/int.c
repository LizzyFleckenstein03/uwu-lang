#include <stdlib.h>
#include "common/str.h"
#include "int.h"

UwUVMValue uwuint_create(long value)
{
	UwUVMValue vm_value = {
		.type = &uwuint_type,
		.data = malloc(sizeof(long))
	};
	*(long *) vm_value.data = value;

	return vm_value;
}

int uwuint_get(UwUVMValue vm_value)
{
	return *(long *) vm_value.data;
}

void *uwuint_clone(void *data)
{
	long *copy = malloc(sizeof(*copy));
	*copy = *(long *) data;
	return copy;
}

char *uwuint_print(void *data)
{
	return asprintf_wrapper("%ld", *(long *) data);
}

UwUVMType uwuint_type = {
	.clone = &uwuint_clone,
	.delet = &free,
	.print = &uwuint_print,
};
