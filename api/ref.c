#include "../src/util.h"
#include "ref.h"

UwUVMValue uwuref_create(UwUVMFunction *value)
{
	return (UwUVMValue) {
		.type = &uwuref_type,
		.data = value,
	};
}

UwUVMFunction *uwuref_get(UwUVMValue value)
{
	return value.data;
}

static void *uwuref_clone(void *data)
{
	return data;
}

static void uwuref_delet(void *data)
{
	(void) data;
}

static char *uwuref_print(void *data)
{
	return asprintf_wrapper("[Function reference: %p]", data);
}

UwUVMType uwuref_type = {
	.clone = &uwuref_clone,
	.delet = &uwuref_delet,
	.print = &uwuref_print,
};
