#ifndef OPTIONS_H
#define OPTIONS_H

struct Options {
	char always_print_number;
	long max;
};

extern struct Options options;

void options_parse(const char *);

#endif
