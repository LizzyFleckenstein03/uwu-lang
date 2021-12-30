#include "../src/util.h"
#include "ref.h"

UwUVMValue uwuref_create(UwUVMFunction *function)
{
	return (UwUVMValue) {
		.type = &uwuref_type,
		.data = function,
	};
}

static void *uwuref_copy(void *data)
{
	return data;
}

static void uwuref_delete(void *data)
{
	(void) data;
}

static char *uwuref_print(void *data)
{
	return asprintf_wrapper("[Function reference: %p]", data);
}

UwUVMType uwuref_type = {
	.copy = &uwuref_copy,
	.delete = &uwuref_delete,
	.print = &uwuref_print,
};
