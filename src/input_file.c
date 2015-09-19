/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/19 22:58:21 by amaurer           #+#    #+#             */
/*   Updated: 2015/09/19 23:35:31 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include <stdlib.h>
#include <obj.h>

#define SET_UV(VERTEX, X, Y)	VERTEX->uv.x = X, VERTEX->uv.y = Y

extern t_scop	g_scop;

static unsigned	count_vertices(void)
{
	unsigned	count;
	unsigned	poly_length;
	t_lstiter	iter;

	count = 0;
	init_iter(&iter, g_scop.polygons, increasing);
	while (lst_iterator_next(&iter))
	{
		poly_length = ((t_polygon*)iter.data)->vertices->size;
		if (poly_length != 3)
			die("Scop can only handle triangle shapes.");
		count += poly_length;
	}
	return (count);
}

static void		set_default_colors(void)
{
	t_lstiter	it_poly;
	t_lstiter	it_vertex;
	t_vec3		color;
	t_vertex	*vertex;

	init_iter(&it_poly, g_scop.polygons, increasing);
	while (lst_iterator_next(&it_poly))
	{
		color.x = (rand() % 1000) / 1000.0f;
		color.y = (rand() % 1000) / 1000.0f;
		color.z = (rand() % 1000) / 1000.0f;
		init_iter(&it_vertex, ((t_polygon*)it_poly.data)->vertices, increasing);
		while (lst_iterator_next(&it_vertex))
		{
			vertex = (t_vertex*)it_vertex.data;
			vec3_copy(&vertex->color, &color);
		}
	}
}

static void		set_default_uvs2(t_polygon *polygon)
{
	t_vertex	*prev_vertex;
	t_vertex	*vertex;
	t_lstiter	it_vertex;

	prev_vertex = NULL;
	init_iter(&it_vertex, polygon->vertices, increasing);
	while (lst_iterator_next(&it_vertex))
	{
		vertex = (t_vertex*)it_vertex.data;
		if (is_vec2_defined(&vertex->uv))
			continue ;
		if (prev_vertex == NULL
			|| (prev_vertex->uv.x == 0.0f && prev_vertex->uv.y == 1.0f))
			SET_UV(vertex, 0.0f, 0.0f);
		else if (prev_vertex->uv.x == 0.0f && prev_vertex->uv.y == 0.0f)
			SET_UV(vertex, 1.0f, 0.0f);
		else if (prev_vertex->uv.x == 1.0f && prev_vertex->uv.y == 0.0f)
			SET_UV(vertex, 1.0f, 1.0f);
		else if (prev_vertex->uv.x == 1.0f && prev_vertex->uv.y == 1.0f)
			SET_UV(vertex, 0.0f, 1.0f);
		prev_vertex = vertex;
	}
}

static void		set_default_uvs(void)
{
	t_lstiter	it_poly;

	init_iter(&it_poly, g_scop.polygons, increasing);
	while (lst_iterator_next(&it_poly))
		set_default_uvs2(it_poly.data);
}

int				parse_input_file(char const *pathname)
{
	t_obj_data	*obj_data;

	obj_data = obj_parse(pathname);
	if (obj_data == NULL)
		die("Could not open the OBJ file.");
	g_scop.polygons = obj_data->polygons;
	lst_destroy(&obj_data->positions, free);
	lst_destroy(&obj_data->uvs, free);
	lst_destroy(&obj_data->normals, free);
	free(obj_data);
	set_default_colors();
	set_default_uvs();
	triangulate_polygons();
	g_scop.vertex_count = count_vertices();
	return (0);
}
