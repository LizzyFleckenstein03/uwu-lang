#include "common/err.h"
#include "api/nil.h"
#include "api/util.h"

UwUVMValue uwu_nil(UwUVMArgs *args)
{
	uwuutil_require_exact("nil.nil", args, 0);
	return uwunil_create();
}

UwUVMValue uwu_is(UwUVMArgs *args)
{
	return uwuutil_is_type("nil.is", args, &uwunil_type);
}
