#include "common/err.h"
#include "run.h"

int main(int argc, char *argv[])
{
	if (argc < 2)
		error("usage: %s <module>\n", argv[0]);

	run_module(argv[0], argv[1], argc > 2 ? (size_t) argc - 2 : 0, &argv[2]);
	return 0;
}
