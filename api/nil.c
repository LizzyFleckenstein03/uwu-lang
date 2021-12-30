#include <string.h>
#include "nil.h"

UwUVMValue uwunil_create()
{
	return (UwUVMValue) {
		.type = &uwunil_type,
		.data = NULL,
	};
}

static void *uwunil_copy(void *data)
{
	return data;
}

static void uwunil_delete(void *data)
{
	(void) data;
}

static char *uwunil_print(void *data)
{
	(void) data;
	return strdup("");
}

UwUVMType uwunil_type = {
	.copy = &uwunil_copy,
	.delete = &uwunil_delete,
	.print = &uwunil_print,
};
