/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangulate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/14 21:35:57 by amaurer           #+#    #+#             */
/*   Updated: 2015/09/20 00:04:01 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include <stdlib.h>

extern t_scop	g_scop;

static void	triangulate_polygon(t_polygon *poly)
{
	unsigned	i;
	t_polygon	*new_poly;
	t_vertex	*first_vertex;

	first_vertex = (t_vertex*)lst_data_at(poly->vertices, 0);
	i = 0;
	while (i < poly->vertices->size - 2)
	{
		new_poly = (t_polygon*)calloc(1, sizeof(t_polygon));
		new_poly->vertices = new_lst();
		lst_push_back(new_poly->vertices, first_vertex);
		lst_push_back(new_poly->vertices, lst_data_at(poly->vertices, i + 1));
		lst_push_back(new_poly->vertices, lst_data_at(poly->vertices, i + 2));
		lst_push_back(g_scop.polygons, new_poly);
		i++;
	}
}

void		triangulate_polygons(void)
{
	t_lstiter	it;
	t_polygon	*poly;

	init_iter(&it, g_scop.polygons, increasing);
	while (lst_iterator_next(&it))
	{
		poly = (t_polygon*)it.data;
		if (poly->vertices->size > 3)
		{
			triangulate_polygon(poly);
			lst_remove_iterator_node(&it);
		}
	}
}
