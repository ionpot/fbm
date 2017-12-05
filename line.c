#include "line.h"

#include <stdio.h>
#include <stdlib.h>

int
line_init(struct Line *line, size_t size)
{
	char *buf = malloc(size);

	if (buf == NULL)
		return 1;

	buf[size - 1] = '\0';

	line->buffer = buf;

	line_clear(line);

	return 0;
}

void
line_free(struct Line *line)
{
	free(line->buffer);
}

void
line_clear(struct Line *line)
{
	line->head = line->buffer + (line->size - 2);
}

void line_write(struct Line *, char *);

void
line_print(struct Line *line)
{
	printf("%s\n", line->head);
}
