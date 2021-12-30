#include "../src/err.h"
#include "../api/nil.h"
#include "../api/util.h"

UwUVMValue uwu_nil(UwUVMArgs *args)
{
	if (args->num != 0)
		error(":nil:nil does not accept any arguments\n");

	return uwunil_create();
}

UwUVMValue uwu_is(UwUVMArgs *args)
{
	return uwuutil_is_type(":nil:is", args, &uwunil_type);
}
