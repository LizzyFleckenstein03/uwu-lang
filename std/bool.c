#include <stdio.h>
#include <stdlib.h>
#include "common/err.h"
#include "api/vm.h"
#include "api/util.h"
#include "api/bool.h"

static inline bool get_bool_arg(UwUVMArgs *args, size_t i)
{
	return uwubool_get(uwuvm_get_arg(args, i));
}

UwUVMValue uwu_if(UwUVMArgs *args)
{
	uwuutil_require_exact(":bool:if", args, 3);

	return uwuvm_clone_value(get_bool_arg(args, 0)
		? uwuvm_get_arg(args, 1)
		: uwuvm_get_arg(args, 2)
	);
}

UwUVMValue uwu_and(UwUVMArgs *args)
{
	uwuutil_require_min(":bool:and", args, 1);

	for (size_t i = 0; i < args->num; i++)
		if (! get_bool_arg(args, i))
			return uwubool_create(false);

	return uwubool_create(true);
}

UwUVMValue uwu_or(UwUVMArgs *args)
{
	uwuutil_require_min(":bool:or", args, 1);

	for (size_t i = 0; i < args->num; i++)
		if (get_bool_arg(args, i))
			return uwubool_create(true);

	return uwubool_create(false);
}

UwUVMValue uwu_equal(UwUVMArgs *args)
{
	uwuutil_require_min(":bool:equal", args, 2);

	bool value = get_bool_arg(args, 0);

	for (size_t i = 1; i < args->num; i++)
		if (get_bool_arg(args, i) != value)
			return uwubool_create(false);

	return uwubool_create(true);
}

UwUVMValue uwu_not(UwUVMArgs *args)
{
	uwuutil_require_exact(":bool:not", args, 1);
	return uwubool_create(! get_bool_arg(args, 0));
}

UwUVMValue uwu_true(UwUVMArgs *args)
{
	uwuutil_require_exact(":bool:true", args, 0);
	return uwubool_create(true);
}

UwUVMValue uwu_false(UwUVMArgs *args)
{
	uwuutil_require_exact(":bool:false", args, 0);
	return uwubool_create(false);
}

UwUVMValue uwu_is(UwUVMArgs *args)
{
	return uwuutil_is_type(":bool:is", args, &uwubool_type);
}
