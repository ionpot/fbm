#include "options.h"

#include <assert.h>
#include <stddef.h>

struct Options options;

void
options_parse(const char *ch)
{
	assert(ch != NULL);

	switch (*ch) {
	case 'p':
		options.always_print_number = 1;
		break;

	case '\0':
		return;

	default:
		options_parse(ch + 1);
	}
}
