/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/20 00:04:49 by amaurer           #+#    #+#             */
/*   Updated: 2015/09/20 00:36:47 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include "matrix.h"
#include <stdio.h>

extern t_scop	g_scop;

static void	auto_rotate_object(void)
{
	matrix_rotate_y(g_scop.model_matrix, 0.001f);
}

static void	update_texture_transition(void)
{
	if (g_scop.texturing)
	{
		if (g_scop.texture_level < 1.0f)
			g_scop.texture_level += 0.01f;
		else if (g_scop.texture_level > 1.0f)
			g_scop.texture_level = 1.0f;
	}
	else if (!g_scop.texturing)
	{
		if (g_scop.texture_level > 0.0f)
			g_scop.texture_level -= 0.01f;
		else if (g_scop.texture_level < 0.0f)
			g_scop.texture_level = 0.0f;
	}
}

void		render(void)
{
	static float	mvp[16] = { 0 };

	if (g_scop.auto_rotate)
		auto_rotate_object();
	update_texture_transition();
	matrix_identity(mvp);
	matrix_mult_m(mvp, 3, g_scop.model_matrix, g_scop.view_matrix,
		g_scop.proj_matrix);
	glUniformMatrix4fv(g_scop.gfx.model_matrix_uni, 1, GL_FALSE,
		g_scop.model_matrix);
	glUniformMatrix4fv(g_scop.gfx.mvp_uni, 1, GL_FALSE, mvp);
	glUniform1f(g_scop.gfx.texture_level_uni, g_scop.texture_level);
	glDrawArrays(GL_TRIANGLES, 0, g_scop.vertex_count);
}
