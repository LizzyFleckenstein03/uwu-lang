#include "../src/err.h"
#include "../api/nil.h"

UwUVMValue uwu_nil(UwUVMArgs *args)
{
	if (args->num != 0)
		error(":nil:nil does not accept any arguments\n");

	return uwunil_create();
}
