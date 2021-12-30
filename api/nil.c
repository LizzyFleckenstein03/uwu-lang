#include <string.h>
#include "nil.h"

UwUVMValue uwunil_create()
{
	return (UwUVMValue) {
		.type = &uwunil_type,
		.data = NULL,
	};
}

static void *uwunil_clone(void *data)
{
	return data;
}

static void uwunil_delet(void *data)
{
	(void) data;
}

static char *uwunil_print(void *data)
{
	(void) data;
	return strdup("");
}

UwUVMType uwunil_type = {
	.clone = &uwunil_clone,
	.delet = &uwunil_delet,
	.print = &uwunil_print,
};
