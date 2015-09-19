/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_normal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/14 21:35:57 by amaurer           #+#    #+#             */
/*   Updated: 2015/09/19 23:39:13 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
