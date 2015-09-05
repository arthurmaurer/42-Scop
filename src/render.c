
#include "scop.h"
#include "matrix.h"
#include <stdio.h>
#include <Windows.h>

extern t_scop	g_scop;

static void	auto_rotate_object()
{
	matrix_rotate_y(g_scop.model_matrix, 0.001f);
}

void		render(void)
{
	float	mvp[16] = { 0 };

	if (g_scop.auto_rotate)
		auto_rotate_object();

	matrix_identity(mvp);
	matrix_mult_m(mvp, 3, g_scop.model_matrix, g_scop.view_matrix, g_scop.proj_matrix);
	glUniformMatrix4fv(g_scop.gfx.model_matrix_uni, 1, GL_FALSE, g_scop.model_matrix);
	glUniformMatrix4fv(g_scop.gfx.mvpUni, 1, GL_FALSE, mvp);
	glDrawArrays(GL_TRIANGLES, 0, g_scop.vertex_count);
}

