#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <Windows.h>
#include <stdio.h>
#include "scop.h"
#include <math.h>

#include "matrix.h"

static GLFWwindow	*init_window(void)
{
	GLFWwindow	*window;

	if (!glfwInit())
		die("Could not init glfw.");

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	window = glfwCreateWindow(1024, 768, "Scop", NULL, NULL);

	if (!window)
		die("Could not create the window.");

	glfwMakeContextCurrent(window);

	glewExperimental = 1;

	if (glewInit() != GLEW_OK)
		die("Could not init glew.");

	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	glEnable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	return (window);
}

int		main(void)
{
	GLFWwindow	*window;
	GLuint	program;
	GLuint	vertex_array;

	/*

	           H ____________  E
	            /|          /|
	           / |         / |
	        D /__|________/  |
	          |  |      A |  |
			  |  |________|__| F
	          |  / G      |  /
	          | /         | /
	          |/__________|/
            C           B
	*/
	
	GLfloat	buffer_data[] = {
		-0.5f, -0.5f, -0.5f,	1.0f, 0.0f, 0.0f,	// A
		-0.5f, 0.5f, -0.5f,		0.0f, 1.0f, 0.0f,	// B
		0.5f, 0.5f, -0.5f,		0.0f, 0.0f, 1.0f,	// C
		0.5f, -0.5f, -0.5f,		1.0f, 1.0f, 1.0f,	// D
		-0.5f, -0.5f, 0.5f,		1.0f, 0.0f, 0.0f,	// E
		-0.5f, 0.5f, 0.5f,		0.0f, 1.0f, 0.0f,	// F
		0.5f, 0.5f, 0.5f,		0.0f, 0.0f, 1.0f,	// G
		0.5f, -0.5f, 0.5f,		1.0f, 1.0f, 1.0f,	// H
	};

	GLuint	elements[] = {
		0, 1, 2,
		2, 3, 0,
		4, 5, 6,
		6, 7, 4,
		4, 5, 1,
		1, 0, 4,
		6, 2, 3,
		3, 7, 6,
		0, 3, 7,
		7, 4, 0,
		5, 1, 2,
		2, 6, 5
	};

	GLuint	vao;
	GLuint	ebo;
	GLuint	posAttrib;
	GLuint	colAttrib;

	GLfloat	model[16] = {
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f,
	};

	float angle = 0.0f;
	
	GLint	uniModel;
	GLint	uniView;
	GLuint	projUni;
	float	*modelMatrix;
	float	*viewMatrix;
	float	*projMatrix;
	t_vec3	eye;
	t_vec3	center;
	t_vec3	up;

	window = init_window();

	if (window == NULL)
		return (EXIT_FAILURE);

	program = load_shaders("shader/scop.vertexshader", "shader/scop.fragmentshader");
	glUseProgram(program);

	glGenVertexArrays(1, &vertex_array);
	glBindVertexArray(vertex_array);

	glGenBuffers(1, &vao);
	glBindBuffer(GL_ARRAY_BUFFER, vao);
	glBufferData(GL_ARRAY_BUFFER, sizeof(buffer_data), buffer_data, GL_STATIC_DRAW);

	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

	posAttrib = glGetAttribLocation(program, "position");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, 0);

	colAttrib = glGetAttribLocation(program, "color");
	glEnableVertexAttribArray(colAttrib);
	glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)(sizeof(float) * 3));

	modelMatrix = create_matrix();
	uniModel = glGetUniformLocation(program, "model");
	glUniformMatrix4fv(uniModel, 1, GL_FALSE, modelMatrix);

	viewMatrix = create_matrix();

	eye.x = 1.2f;
	eye.y = 0.7f;
	eye.z = 0.7f;

	center.x = 0.0f;
	center.y = 0.0f;
	center.z = 0.0f;

	up.x = 0.0f;
	up.y = 0.0f;
	up.z = 1.0f;

	look_at(viewMatrix, &eye, &center, &up);

    uniView = glGetUniformLocation(program, "view");
	glUniformMatrix4fv(uniView, 1, GL_FALSE, viewMatrix);

	projMatrix = matrix_perspective(deg_to_rad(60.0f), 800.0f / 600.0f, 0.1f, 1000.0f);
	projUni = glGetUniformLocation(program, "proj");
	glUniformMatrix4fv(projUni, 1, GL_FALSE, projMatrix);

	do
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		matrix_rotate_x(modelMatrix, 0.001f);
		matrix_rotate_z(modelMatrix, 0.001f);
		glUniformMatrix4fv(uniModel, 1, GL_FALSE, modelMatrix);

		glDrawElements(GL_TRIANGLES, sizeof(elements) / sizeof(float), GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);

	glDeleteBuffers(1, &vao);
	glDeleteVertexArrays(1, &vertex_array);
	glDeleteProgram(program);

	glfwTerminate();

	return (EXIT_SUCCESS);
}
