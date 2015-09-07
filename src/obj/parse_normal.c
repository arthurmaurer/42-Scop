#include <stdlib.h>
#include "ftlst.h"
#include "obj_internal.h"

int			parse_normal(const char **tokens)
{
	t_vec3	*new_normal;

	if (!(new_normal = malloc(sizeof(t_vec3))))
		return (0);
	else if (!parse_vec3(tokens, new_normal))
	{
		free(new_normal);
		parser_die("A normal needs three arguments.");
	}
	lst_push_back(g_current_data->normals, new_normal);
	return (1);
}
