#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bool.h"
#include "nil.h"

UwUVMValue uwubool_create(bool value)
{
	UwUVMValue vm_value = {
		.type = VT_NAT,
		.value = {
			.nat_value = {
				.type = &uwubool_type,
				.data = malloc(sizeof(bool))
			},
		},
	};

	*(bool *) vm_value.value.nat_value.data = value;
	return vm_value;
}

bool uwubool_get(UwUVMValue vm_value)
{
	if (vm_value.type != VT_NAT)
		return true;
	else if (vm_value.value.nat_value.type == &uwunil_type)
		return false;
	else if (vm_value.value.nat_value.type == &uwubool_type)
		return *(bool *) vm_value.value.nat_value.data;
	else
		return true;
}

static void *uwubool_copy(void *data)
{
	bool *copy = malloc(sizeof(*copy));
	*copy = *(bool *) data;
	return 	copy;
}

static char *uwubool_print(void *data)
{
	return strdup(((bool *) data) ? "true" : "false");
}

UwUVMNativeType uwubool_type = {
	.copy = &uwubool_copy,
	.delete = &free,
	.print = &uwubool_print,
};
