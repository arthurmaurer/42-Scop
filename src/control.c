
#include "scop.h"

void	handle_keys(GLFWwindow *window, int button, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		if (button == GLFW_KEY_ESCAPE)
			glfwSetWindowShouldClose(window, 1);
		if (button == GLFW_KEY_SPACE)
		{

		}
	}
}
