#include <stdlib.h>
#include <stdio.h>
#include "obj_internal.h"

void	parser_die(const char *msg)
{
	printf("Parse error at line %u !\n%s\n", g_current_line, msg);
	exit(EXIT_FAILURE);
}
