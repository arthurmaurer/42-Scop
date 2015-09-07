
#include "scop.h"
#include "matrix.h"
#include <stdio.h>

extern t_scop	g_scop;

void	handle_keys(GLFWwindow *window, int button, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		if (button == GLFW_KEY_ESCAPE)
			glfwSetWindowShouldClose(window, 1);
		else if (button == GLFW_KEY_R)
			g_scop.auto_rotate = !g_scop.auto_rotate;
		else if (button == GLFW_KEY_SPACE)
			toggle_wireframe_mode();
		else if (button == GLFW_KEY_T)
			toggle_texturing();
		else if (button == GLFW_KEY_L)
			toggle_lighting();
	}
	(void)scancode;
	(void)mods;
}

void	handle_scroll(GLFWwindow *window, double scroll_x, double scroll_y)
{
	matrix_scale_xyz(g_scop.model_matrix, 1.0f + (float)scroll_y / 10);
	(void)window;
	(void)scroll_x;
}

static void	user_rotate(float pos_x, float pos_y)
{
	if (g_scop.prev_mouse_pos.x < 0)
		return ;

	matrix_rotate_y(g_scop.model_matrix, (g_scop.prev_mouse_pos.x - pos_x) / 500.0f);
	matrix_rotate_x(g_scop.model_matrix, (g_scop.prev_mouse_pos.y - pos_y) / 500.0f);
}

void	handle_mouse_move(GLFWwindow *window, double pos_x, double pos_y)
{
	if (g_scop.user_control == USER_CONTROL_NONE)
		return ;

	if (g_scop.user_control == USER_CONTROL_ROTATE)
		user_rotate((float)pos_x, (float)pos_y);

	g_scop.prev_mouse_pos.x = (float)pos_x;
	g_scop.prev_mouse_pos.y = (float)pos_y;
	(void)window;
}

void			handle_mouse_button(GLFWwindow *window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_1)
	{
		g_scop.auto_rotate = 0;

		if (action == GLFW_PRESS)
			g_scop.user_control = USER_CONTROL_ROTATE;
		else
		{
			g_scop.user_control = USER_CONTROL_NONE;
			g_scop.prev_mouse_pos.x = -1.0f;
			g_scop.prev_mouse_pos.y = -1.0f;
		}
	}
	(void)window;
	(void)mods;
}
