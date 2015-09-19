/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx_buffer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/20 00:23:24 by amaurer           #+#    #+#             */
/*   Updated: 2015/09/20 00:24:30 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include <stdlib.h>
#include <string.h>

extern t_scop	g_scop;

static void	buffer_load_poly(float *buffer, t_polygon const *poly)
{
	t_lstiter	iter;
	unsigned	i;
	t_vertex	*vertex;

	i = 0;
	init_iter(&iter, poly->vertices, increasing);
	while (lst_iterator_next(&iter))
	{
		vertex = (t_vertex*)iter.data;
		memcpy(buffer + i * 11, &vertex->position, sizeof(t_vec3));
		memcpy(buffer + i * 11 + 3, &vertex->color, sizeof(t_vec3));
		memcpy(buffer + i * 11 + 6, &vertex->uv, sizeof(t_vec2));
		memcpy(buffer + i * 11 + 8, &vertex->normal, sizeof(t_vec3));
		i++;
	}
}

void		build_vertex_buffer(void)
{
	unsigned	i;
	t_lstiter	iter;
	float		*buffer_data;
	unsigned	buffer_length;

	buffer_length = (3 + 3 + 2 + 3) * g_scop.vertex_count;
	buffer_data = (float*)calloc(buffer_length, sizeof(float));
	i = 0;
	init_iter(&iter, g_scop.polygons, increasing);
	while (lst_iterator_next(&iter))
	{
		buffer_load_poly(buffer_data + i * 11, (t_polygon*)iter.data);
		i += 3;
	}
	glGenBuffers(1, &g_scop.gfx.vbo);
	glBindBuffer(GL_ARRAY_BUFFER, g_scop.gfx.vbo);
	glBufferData(GL_ARRAY_BUFFER, buffer_length * sizeof(float), buffer_data,
		GL_STATIC_DRAW);
}
