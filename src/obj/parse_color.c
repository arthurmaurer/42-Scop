/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/14 21:35:57 by amaurer           #+#    #+#             */
/*   Updated: 2015/09/19 23:39:07 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ftlst.h"
#include "obj_internal.h"

int			parse_color(const char **tokens)
{
	t_vec2	*new_color;

	new_color = NULL;
	if (!tokens_are_enough(tokens, 2))
		parser_die("A texture needs two arguments.");
	else if (!(new_color = malloc(sizeof(t_vec2))))
		return (0);
	new_color->x = atof(tokens[0]);
	new_color->y = atof(tokens[1]);
	lst_push_back(g_current_data->uvs, new_color);
	return (1);
}
