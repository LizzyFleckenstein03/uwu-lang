#include <string.h>
#include <stdlib.h>
#include "api/vm.h"
#include "api/str.h"
#include "api/util.h"

UwUVMValue uwu_cat(UwUVMArgs *args)
{
	size_t total_len = 0;
	size_t lengths[args->num];
	char  *substrs[args->num];

	for (size_t i = 0; i < args->num; i++) {
		substrs[i] = uwustr_get(uwuvm_get_arg(args, i));
		lengths[i] = strlen(substrs[i]);
		total_len += lengths[i];
	}

	char result[total_len + 1];
	char *result_ptr = result;

	for (size_t i = 0; i < args->num; i++) {
		strcpy(result_ptr, substrs[i]);
		free(substrs[i]);
		result_ptr += lengths[i];
	}

	*result_ptr = 0;

	return uwustr_create(result);
}

UwUVMValue uwu_is(UwUVMArgs *args)
{
	return uwuutil_is_type("str.is", args, &uwustr_type);
}
