#include <stdlib.h>
#include "obj_internal.h"

int		parse_vec3(const char **tokens, t_vec3 *vector)
{
	if (!tokens_are_enough(tokens, 3))
		return (0);
	vector->x = atof(tokens[0]);
	vector->y = atof(tokens[1]);
	vector->z = atof(tokens[2]);
	return (1);
}
