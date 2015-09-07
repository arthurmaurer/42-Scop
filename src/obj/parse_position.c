#include <stdlib.h>
#include "ftlst.h"
#include "obj_internal.h"

int			parse_position(const char **tokens)
{
	t_vec3	*new_position;

	if (!(new_position = malloc(sizeof(t_vec3))))
		return (0);
	else if (!parse_vec3(tokens, new_position))
	{
		free(new_position);
		return (0);
	}
	lst_push_back(g_current_data->positions, new_position);
	return (1);
}
