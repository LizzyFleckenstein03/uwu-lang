#include "../src/err.h"
#include "util.h"
#include "bool.h"

UwUVMValue uwuutil_is_type(const char *fnname, UwUVMArgs *args, UwUVMType *type)
{
	if (args->num < 1)
		error("error: %s requires at least one argument\n", fnname);

	for (size_t i = 0; i < args->num; i++)
		if (uwuvm_get_arg(args, i).type != type)
			return uwubool_create(false);

	return uwubool_create(true);
}
