#include "../src/err.h"
#include "../api/ref.h"
#include "../api/util.h"

UwUVMValue uwu_call(UwUVMArgs *args)
{
	if (args->num < 1)
		error(":ref:call requires at least one argument\n");

	UwUVMValue value = uwuvm_get_arg(args, 0);

	if (value.type != &uwuref_type)
		error(":ref:call requires a function reference as $0\n");

	return uwuvm_call_function(value.data, args->num - 1, &args->unevaluated[1], args->super);
}

UwUVMValue uwu_is(UwUVMArgs *args)
{
	return uwuutil_is_type(":ref:is", args, &uwuref_type);
}
