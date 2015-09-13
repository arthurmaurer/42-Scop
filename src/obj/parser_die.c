#include <stdlib.h>
#include <stdio.h>
#include "obj_internal.h"

void	parser_die(const char *msg)
{
	char	lol[400];
	sprintf(lol, "Parse error at line %u !\n%s\n", g_current_line, msg);
	#ifdef _WIN32
	OutputDebugString(lol);
	#else
		printf("%s", lol);
	#endif
	exit(EXIT_FAILURE);
}
