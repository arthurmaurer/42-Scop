#include <stdlib.h>
#include <stdio.h>
#include "obj_internal.h"
#include <Windows.h>

void	parser_die(const char *msg)
{
	char	lol[400];
	sprintf(lol, "Parse error at line %u !\n%s\n", g_current_line, msg);
	OutputDebugString(lol);
	exit(EXIT_FAILURE);
}
