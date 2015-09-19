/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/19 23:41:07 by amaurer           #+#    #+#             */
/*   Updated: 2015/09/20 00:02:50 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

extern t_scop	g_scop;

static void	window_bind_controls(GLFWwindow *window)
{
	glfwSetKeyCallback(window, handle_keys);
	glfwSetScrollCallback(window, handle_scroll);
	glfwSetCursorPosCallback(window, handle_mouse_move);
	glfwSetMouseButtonCallback(window, handle_mouse_button);
}

static void	window_set_hints(void)
{
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

GLFWwindow	*create_window(void)
{
	GLFWwindow	*window;

	if (!glfwInit())
		die("Could not init glfw.");
	window_set_hints();
	window = glfwCreateWindow(1024, 768, "Scop", NULL, NULL);
	if (!window)
		die("Could not create the window.");
	glfwMakeContextCurrent(window);
	window_bind_controls(window);
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
