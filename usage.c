#include <assert.h>
#include <stdio.h>

#define NAME "fbm"

#define FORMAT \
	NAME " [OPTIONS]... UNTIL [PAIR]..."

#define DESCR \
	"Prints space-separated numbers starting from 1 until UNTIL is reached (prints UNTIL itself as well). A PAIR is a number and a word mushed together, such as \"3fizz\" or \"5buzz\"."\
	"\n\n"\
	"If a PAIR can divide the current number, its word is printed instead of the current number. If multiple PAIRs can divide the number, all of their words are printed. PAIRs with smaller numbers are printed first."

#define OPTIONS \
	"  -p\tThe words append the number, instead of replacing it, so both are visible."

#define EX1 \
	"  " NAME " 16 3fizz 5buzz"

#define EX1_DESCR \
	"  This would output:\n"\
	"  1 2 fizz 4 buzz fizz 7 8 fizz buzz 11 fizz 13 14 fizzbuzz 16"

#define EX2 \
	"  " NAME " -p 15 2a 3b 5c"

#define EX2_DESCR \
	"  This would output:\n"\
	"  1 2a 3b 4a 5c 6ab 7 8a 9b 10ac 11 12ab 13 14a 15bc"

void
usage_print(void)
{
	puts("Usage:");
	puts(FORMAT);
	puts(DESCR);

	putchar('\n');
	puts("Options:");
	puts(OPTIONS);

	putchar('\n');
	puts("Examples:");
	puts(EX1);
	puts(EX1_DESCR);

	putchar('\n');
	puts(EX2);
	puts(EX2_DESCR);
}
