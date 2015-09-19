/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx_toggles.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/20 00:19:40 by amaurer           #+#    #+#             */
/*   Updated: 2015/09/20 00:36:01 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

extern t_scop	g_scop;

void		toggle_wireframe_mode(void)
{
	if (g_scop.wireframe)
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	g_scop.wireframe = !g_scop.wireframe;
}

void		toggle_texturing(void)
{
	g_scop.texturing = !g_scop.texturing;
}

void		toggle_lighting(void)
{
	g_scop.lighting = !g_scop.lighting;
	glUniform1i(g_scop.gfx.lighting_uni, g_scop.lighting);
}

void		switch_clear_color(void)
{
	if (g_scop.clear_color.x < 1.0f)
	{
		g_scop.clear_color.x += 0.35f;
		g_scop.clear_color.y += 0.35f;
		g_scop.clear_color.z += 0.35f;
	}
	else
		vec3_set(&g_scop.clear_color, 0, 0, 0);
	glClearColor(g_scop.clear_color.x, g_scop.clear_color.y,
		g_scop.clear_color.z, 1.0f);
}
