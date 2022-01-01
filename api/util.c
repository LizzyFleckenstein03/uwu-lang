#include "common/err.h"
#include "util.h"
#include "bool.h"

UwUVMValue uwuutil_is_type(const char *fnname, UwUVMArgs *args, UwUVMType *type)
{
	uwuutil_require_min(fnname, args, 1);

	for (size_t i = 0; i < args->num; i++)
		if (uwuvm_get_arg(args, i).type != type)
			return uwubool_create(false);

	return uwubool_create(true);
}

void uwuutil_require_min(const char *fnname, UwUVMArgs *args, size_t n)
{
	if (args->num < n) {
		if (n == 1)
			error("type error: %s requires at least one argument, but none were given\n", fnname);
		else
			error("type error: %s requires at least %d arguments, but only %d were given\n", fnname, n, args->num);
	}
}

void uwuutil_require_max(const char *fnname, UwUVMArgs *args, size_t n)
{
	if (args->num > n) {
		if (n == 1)
			error("type error: %s accepts one optional argument, but %d were given\n", fnname, args->num);
		else
			error("type error: %s does not take more than %d arguments, but %d were given\n", fnname, args->num);
	}
}

void uwuutil_require_exact(const char *fnname, UwUVMArgs *args, size_t n)
{
	if (args->num != n) {
		if (n == 0)
			error("type error: %s does not take any arguments, but %d were given\n", fnname, args->num);
		else if (n == 1)
			error("type error: %s requires exactly one argument, but %d were given\n", fnname, args->num);
		else
			error("type error: %s requires exactly %d arguments, but %d were given\n", fnname, n, args->num);
	}
}
