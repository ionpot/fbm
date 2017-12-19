#ifndef OPTIONS_H
#define OPTIONS_H

struct Options {
	char always_print_number;
	long max;
};

void options_parse(const char *);

#endif
