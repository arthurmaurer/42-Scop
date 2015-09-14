
#include "scop.h"
#include <stdio.h>

extern t_scop	g_scop;

GLFWwindow	*create_window(void)
{
	GLFWwindow	*window;

	if (!glfwInit())
		die("Could not init glfw.");

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(1024, 768, "Scop", NULL, NULL);

	if (!window)
		die("Could not create the window.");

	glfwMakeContextCurrent(window);

	glfwSetKeyCallback(window, handle_keys);
	glfwSetScrollCallback(window, handle_scroll);
	glfwSetCursorPosCallback(window, handle_mouse_move);
	glfwSetMouseButtonCallback(window, handle_mouse_button);

	glewExperimental = 1;

	if (glewInit() != GLEW_OK)
		die("Could not init glew.");

	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	glEnable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	if (g_scop.wireframe)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	return (window);
}
