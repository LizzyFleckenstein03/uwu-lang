#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bool.h"
#include "nil.h"

UwUVMValue uwubool_create(bool value)
{
	UwUVMValue vm_value = {
		.type = &uwubool_type,
		.data = malloc(sizeof(bool)),
	};

	*(bool *) vm_value.data = value;
	return vm_value;
}

bool uwubool_get(UwUVMValue vm_value)
{
	if (vm_value.type == &uwunil_type)
		return false;
	else if (vm_value.type == &uwubool_type)
		return *(bool *) vm_value.data;
	else
		return true;
}

static void *uwubool_clone(void *data)
{
	bool *copy = malloc(sizeof(*copy));
	*copy = *(bool *) data;
	return copy;
}

static char *uwubool_print(void *data)
{
	return strdup(((bool *) data) ? "true" : "false");
}

UwUVMType uwubool_type = {
	.clone = &uwubool_clone,
	.delet = &free,
	.print = &uwubool_print,
};
