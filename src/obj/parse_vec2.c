#include <stdlib.h>
#include "obj_internal.h"

int		parse_vec2(const char **tokens, t_vec3 *vector)
{
	if (!tokens_are_enough(tokens, 2))
		return (0);
	vector->x = atof(tokens[0]);
	vector->y = atof(tokens[1]);
	return (1);
}
