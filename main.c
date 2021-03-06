#include "args.h"
#include "list.h"
#include "options.h"
#include "print.h"

#include <stdio.h>

extern void usage_print(void);

static void
begin(void)
{
	if (!options.max) {
		puts("No max provided.");
		return;
	}

	if (list_count()) {
		list_sort();
		list_findlcm();

		print_list();

	} else {
		print_nums();
	}
}

int
main(int argc, char **argv)
{
	if (argc > 1) {
		if (list_init(argc - 1)) {
			args_parse(argc, argv);
			begin();
			list_free();
		}

	} else {
		usage_print();
	}

	return 0;
}
