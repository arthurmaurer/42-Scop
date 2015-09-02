#include <stdlib.h>
#include "ftlst.h"
#include "obj_internal.h"

int			parse_color(const char **tokens)
{
	t_vec2	*new_color;

	new_color = NULL;
	if (!tokens_are_enough(tokens, 2))
		parser_die("A texture needs two arguments.");
	else if (!(new_color = (t_vec2*)malloc(sizeof(t_vec2))))
		return (0);
	new_color->x = (float)atof(tokens[0]);
	new_color->y = (float)atof(tokens[1]);
	lst_push_back(g_current_data->uvs, new_color);
	return (1);
}
