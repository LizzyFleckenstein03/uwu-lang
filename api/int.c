#include "int.h"

UwUVMValue uwuint_create(int value)
{
	return (UwUVMValue) {
		.type = VT_INT,
		.value = {
			.int_value = value,	
		},
	};
}
