#include <float.h>
#include "obj_internal.h"

int		is_vec2_defined(t_vec2 *v)
{
	if (v->x == DBL_MAX && v->y == DBL_MAX)
		return (0);
	return (1);
}

int		is_vec3_defined(t_vec3 *v)
{
	if (is_vec2_defined((t_vec2 *)v) && v->z == DBL_MAX)
		return (0);
	return (1);
}
