#include <string.h>
#include "../src/util.h"
#include "str.h"

UwUVMValue uwustr_create(const char *value)
{
	return (UwUVMValue) {
		.type = VT_STR,
		.value = {
			.str_value = strdup(value),	
		},
	};
}

char *uwustr_get(UwUVMValue vm_value)
{
	switch (vm_value.type) {
		case VT_INT:
			return asprintf_wrapper("%d", vm_value.value.int_value);

		case VT_STR:
			return strdup(vm_value.value.str_value);

		case VT_REF:
			return asprintf_wrapper("[Function reference: %p]", vm_value.value.ref_value);
		
		case VT_NAT:
			return vm_value.value.nat_value.type->print
				? vm_value.value.nat_value.type->print(vm_value.value.nat_value.data)
				: asprintf_wrapper("[Native value: %p: %p]", vm_value.value.nat_value.data, vm_value.value.nat_value.type);
	}
}
