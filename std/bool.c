#include <stdio.h>
#include <stdlib.h>
#include "../src/err.h"
#include "../api/vm.h"
#include "../api/bool.h"

static inline bool get_bool_arg(UwUVMArgs *args, size_t i)
{
	return uwubool_get(uwuvm_get_arg(args, i));
}

#include "../api/str.h"
UwUVMValue uwu_if(UwUVMArgs *args)
{
	if (args->num != 3)
		error("error: :bool:if requires exactly 3 arguments\n");

	return uwuvm_copy_value(get_bool_arg(args, 0)
		? uwuvm_get_arg(args, 1)
		: uwuvm_get_arg(args, 2)
	);
}

UwUVMValue uwu_and(UwUVMArgs *args)
{
	if (args->num < 1)
		error("error: :bool:and requires at least one argument\n");

	for (size_t i = 0; i < args->num; i++)
		if (! get_bool_arg(args, i))
			return uwubool_create(false);

	return uwubool_create(true);
}

UwUVMValue uwu_or(UwUVMArgs *args)
{
	if (args->num < 1)
		error("error: :bool:or requires at least one argument\n");

	for (size_t i = 0; i < args->num; i++)
		if (get_bool_arg(args, i))
			return uwubool_create(true);

	return uwubool_create(false);
}

UwUVMValue uwu_equal(UwUVMArgs *args)
{
	if (args->num < 2)
		error("error: :bool:equal requires at least 2 arguments\n");

	bool value = get_bool_arg(args, 0);

	for (size_t i = 1; i < args->num; i++)
		if (get_bool_arg(args, i) != value)
			return uwubool_create(false);
	
	return uwubool_create(true);
}

UwUVMValue uwu_not(UwUVMArgs *args)
{
	if (args->num != 1)
		error("error: :bool:not requires exactly 1 argument\n");

	return uwubool_create(! get_bool_arg(args, 0));
}

UwUVMValue uwu_true(UwUVMArgs *args)
{
	if (args->num != 0)
		error("error: :bool:true does not take any arguments\n");
	
	return uwubool_create(true);
}

UwUVMValue uwu_false(UwUVMArgs *args)
{
	if (args->num != 0)
		error("error: :bool:false does not take any arguments\n");

	return uwubool_create(false);
}

UwUVMValue uwu_is(UwUVMArgs *args)
{
	if (args->num < 1)
		error("error: :bool:is requires at least 1 argument\n");

	for (size_t i = 0; i < args->num; i++) {
		UwUVMValue value = uwuvm_get_arg(args, i);
		return uwubool_create(value.type != VT_NAT || value.value.nat_value.type != &uwubool_type);
	}

	return uwubool_create(true);
}
