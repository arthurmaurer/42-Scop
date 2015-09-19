/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx_attribs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/20 00:21:13 by amaurer           #+#    #+#             */
/*   Updated: 2015/09/20 00:36:19 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

extern t_scop	g_scop;

void	set_position_attrib(void)
{
	g_scop.gfx.pos_attrib = glGetAttribLocation(g_scop.gfx.program, "position");
	glEnableVertexAttribArray(g_scop.gfx.pos_attrib);
	glVertexAttribPointer(g_scop.gfx.pos_attrib, 3, GL_FLOAT, GL_FALSE,
		sizeof(float) * 11, 0);
}

void	set_color_attrib(void)
{
	g_scop.gfx.col_attrib = glGetAttribLocation(g_scop.gfx.program, "color");
	glEnableVertexAttribArray(g_scop.gfx.col_attrib);
	glVertexAttribPointer(g_scop.gfx.col_attrib, 3, GL_FLOAT, GL_FALSE,
		sizeof(float) * 11, (void*)(sizeof(float) * 3));
}

void	set_uv_attrib(void)
{
	GLuint	id;

	id = glGetAttribLocation(g_scop.gfx.program, "uv");
	glEnableVertexAttribArray(id);
	glVertexAttribPointer(id, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 11,
		(void*)(sizeof(GLfloat) * 6));
}

void	set_normal_attrib(void)
{
	GLuint	id;

	id = glGetAttribLocation(g_scop.gfx.program, "normal");
	glEnableVertexAttribArray(id);
	glVertexAttribPointer(id, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 11,
		(void*)(sizeof(GLfloat) * 8));
}
