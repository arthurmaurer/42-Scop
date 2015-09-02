#include <stdlib.h>
#include "obj_internal.h"

int		parse_vec2(const char **tokens, t_vec3 *vector)
{
	if (!tokens_are_enough(tokens, 2))
		return (0);
	vector->x = (float)atof(tokens[0]);
	vector->y = (float)atof(tokens[1]);
	return (1);
}
