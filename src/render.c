
#include "scop.h"
#include "matrix.h"

extern t_scop	g_scop;

static void	rotate_object()
{
	matrix_rotate_x(g_scop.model_matrix, 0.001f);
	matrix_rotate_z(g_scop.model_matrix, 0.001f);
}

void		render(void)
{
	float	mvp[16] = { 0 };

	rotate_object();
	matrix_copy(mvp, g_scop.model_matrix);
	matrix_mult(mvp, mvp, g_scop.view_matrix);
	matrix_mult(mvp, mvp, g_scop.proj_matrix);
	glUniformMatrix4fv(g_scop.gfx.mvpUni, 1, GL_FALSE, mvp);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}
