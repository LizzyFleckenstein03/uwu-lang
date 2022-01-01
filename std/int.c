#include <stdio.h>
#include <stdlib.h>
#include "common/err.h"
#include "api/vm.h"
#include "api/int.h"
#include "api/bool.h"
#include "api/util.h"

typedef enum
{
	BOP_SUB,
	BOP_DIV,
	BOP_MOD,
	BOP_SML,
	BOP_GRT,
	BOP_EQU,
} BinaryOP;

static long binary(const char *fnname, UwUVMArgs *args, BinaryOP op)
{
	uwuutil_require_exact(fnname, args, 2);

	UwUVMValue value0 = uwuvm_get_arg(args, 0);

	if (value0.type != &uwuint_type)
		error("type error: %s requires an integer as $1\n", fnname);

	UwUVMValue value1 = uwuvm_get_arg(args, 1);

	if (value1.type != &uwuint_type)
		error("type error: %s requires an integer as $2\n", fnname);

	long a = uwuint_get(value0);
	long b = uwuint_get(value1);

	switch (op) {
		case BOP_SUB: return a - b;
		case BOP_DIV: return a / b;
		case BOP_MOD: return a % b;
		case BOP_SML: return a < b;
		case BOP_GRT: return a > b;
		case BOP_EQU: return a == b;
	}

	return 0;
}

typedef enum
{
	ROP_ADD,
	ROP_MUL,
	ROP_EQU,
} ReduceOP;

static long reduce(const char *fnname, UwUVMArgs *args, ReduceOP op, long result)
{
	long first;

	for (size_t i = 0; i < args->num; i++) {
		UwUVMValue value = uwuvm_get_arg(args, i);

		if (value.type != &uwuint_type)
			error("type error: %s only accepts integers as arguments (invalid argument: $%lu)\n", fnname, i + 1);

		long this = uwuint_get(value);

		switch (op) {
			case ROP_ADD: result += this; break;
			case ROP_MUL: result *= this; break;
			case ROP_EQU:
				if (i == 0)
					first = this;
				else if (this != first)
					return 0;

				break;
		}
	}

	return result;
}

UwUVMValue uwu_add(UwUVMArgs *args)
{
	return uwuint_create(reduce(":int:add", args, ROP_ADD, 0));
}

UwUVMValue uwu_sub(UwUVMArgs *args)
{
	return uwuint_create(binary(":int:sub", args, BOP_SUB));
}

UwUVMValue uwu_mul(UwUVMArgs *args)
{
	return uwuint_create(reduce(":int:mul", args, ROP_MUL, 1));
}

UwUVMValue uwu_div(UwUVMArgs *args)
{
	return uwuint_create(binary(":int:div", args, BOP_DIV));
}

UwUVMValue uwu_mod(UwUVMArgs *args)
{
	return uwuint_create(binary(":int:mod", args, BOP_MOD));
}

UwUVMValue uwu_smaller(UwUVMArgs *args)
{
	return uwubool_create(binary(":int:smaller", args, BOP_SML) == 1);
}

UwUVMValue uwu_greater(UwUVMArgs *args)
{
	return uwubool_create(binary(":int:greater", args, BOP_GRT) == 1);
}

UwUVMValue uwu_equal(UwUVMArgs *args)
{
	uwuutil_require_min(":int:equal", args, 2);
	return uwubool_create(reduce(":int:equal", args, ROP_EQU, 1) == 1);
}

UwUVMValue uwu_is(UwUVMArgs *args)
{
	return uwuutil_is_type(":int:is", args, &uwuint_type);
}
