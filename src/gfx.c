
#include "scop.h"
#include "matrix.h"
#include <stdlib.h>
#include <string.h>

extern t_scop	g_scop;

void		toggleWireframeMode(void)
{
	if (g_scop.wireframe)
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	g_scop.wireframe = !g_scop.wireframe;
}

void		build_vertex_buffer(void)
{
	GLfloat	buffer_data[] = {
		-0.5f, -0.5f, -0.5f,	1.0f, 0.0f, 0.0f,	// A	0
		-0.5f, 0.5f, -0.5f,		0.0f, 1.0f, 0.0f,	// B	1
		0.5f, 0.5f, -0.5f,		0.0f, 0.0f, 1.0f,	// C	2
		
		0.5f, 0.5f, -0.5f,		0.0f, 0.0f, 1.0f,	// C	2
		0.5f, -0.5f, -0.5f,		1.0f, 1.0f, 1.0f,	// D	3
		-0.5f, -0.5f, -0.5f,	1.0f, 0.0f, 0.0f,	// A	0
		
		-0.5f, -0.5f, 0.5f,		1.0f, 0.0f, 0.0f,	// E	4
		-0.5f, 0.5f, 0.5f,		0.0f, 1.0f, 0.0f,	// F	5
		0.5f, 0.5f, 0.5f,		0.0f, 0.0f, 1.0f,	// G	6
		
		0.5f, 0.5f, 0.5f,		0.0f, 0.0f, 1.0f,	// G	6
		0.5f, -0.5f, 0.5f,		1.0f, 1.0f, 1.0f,	// H	7
		-0.5f, -0.5f, 0.5f,		1.0f, 0.0f, 0.0f,	// E	4
		
		-0.5f, -0.5f, 0.5f,		1.0f, 0.0f, 0.0f,	// E	4
		-0.5f, 0.5f, 0.5f,		0.0f, 1.0f, 0.0f,	// F	5
		-0.5f, 0.5f, -0.5f,		0.0f, 1.0f, 0.0f,	// B	1
		
		-0.5f, 0.5f, -0.5f,		0.0f, 1.0f, 0.0f,	// B	1
		-0.5f, -0.5f, -0.5f,	1.0f, 0.0f, 0.0f,	// A	0
		-0.5f, -0.5f, 0.5f,		1.0f, 0.0f, 0.0f,	// E	4
		
		0.5f, 0.5f, 0.5f,		0.0f, 0.0f, 1.0f,	// G	6
		0.5f, 0.5f, -0.5f,		0.0f, 0.0f, 1.0f,	// C	2
		0.5f, -0.5f, -0.5f,		1.0f, 1.0f, 1.0f,	// D	3
		
		0.5f, -0.5f, -0.5f,		1.0f, 1.0f, 1.0f,	// D	3
		0.5f, -0.5f, 0.5f,		1.0f, 1.0f, 1.0f,	// H	7
		0.5f, 0.5f, 0.5f,		0.0f, 0.0f, 1.0f,	// G	6

		-0.5f, -0.5f, -0.5f,	1.0f, 0.0f, 0.0f,	// A	0
		0.5f, -0.5f, -0.5f,		1.0f, 1.0f, 1.0f,	// D	3
		0.5f, -0.5f, 0.5f,		1.0f, 1.0f, 1.0f,	// H	7
		
		0.5f, -0.5f, 0.5f,		1.0f, 1.0f, 1.0f,	// H	7
		-0.5f, -0.5f, 0.5f,		1.0f, 0.0f, 0.0f,	// E	4
		-0.5f, -0.5f, -0.5f,	1.0f, 0.0f, 0.0f,	// A	0
		
		-0.5f, 0.5f, 0.5f,		0.0f, 1.0f, 0.0f,	// F	5
		-0.5f, 0.5f, -0.5f,		0.0f, 1.0f, 0.0f,	// B	1
		0.5f, 0.5f, -0.5f,		0.0f, 0.0f, 1.0f,	// C	2
		
		0.5f, 0.5f, -0.5f,		0.0f, 0.0f, 1.0f,	// C	2
		0.5f, 0.5f, 0.5f,		0.0f, 0.0f, 1.0f,	// G	6
		-0.5f, 0.5f, 0.5f,		0.0f, 1.0f, 0.0f,	// F	5
	};

	glGenBuffers(1, &g_scop.gfx.vbo);
	glBindBuffer(GL_ARRAY_BUFFER, g_scop.gfx.vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(buffer_data), buffer_data, GL_STATIC_DRAW);
}

static void	setPositionAttrib(void)
{
	g_scop.gfx.posAttrib = glGetAttribLocation(g_scop.gfx.program, "position");
	glEnableVertexAttribArray(g_scop.gfx.posAttrib);
	glVertexAttribPointer(g_scop.gfx.posAttrib, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, 0);
}

static void	setColorAttrib(void)
{
	g_scop.gfx.colAttrib = glGetAttribLocation(g_scop.gfx.program, "color");
	glEnableVertexAttribArray(g_scop.gfx.colAttrib);
	glVertexAttribPointer(g_scop.gfx.colAttrib, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)(sizeof(float) * 3));
}

static void	setUVAttrib(void)
{
	GLuint	id;

	id = glGetAttribLocation(g_scop.gfx.program, "uv");
	glEnableVertexAttribArray(id);
	glVertexAttribPointer(id, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 8, (void*)(sizeof(GLfloat) * 6));
}

void		set_view_matrix(void)
{
	t_vec3	eye;
	t_vec3	center;
	t_vec3	up;

	g_scop.view_matrix = create_matrix();

	eye.x = 1.2f;
	eye.y = 0.7f;
	eye.z = 0.7f;

	center.x = 0.0f;
	center.y = 0.0f;
	center.z = 0.0f;

	up.x = 0.0f;
	up.y = 0.0f;
	up.z = 1.0f;

	look_at(g_scop.view_matrix, &eye, &center, &up);
}

void		launch(void)
{
	g_scop.gfx.window = create_window();

	if (g_scop.gfx.window == NULL)
		die("Could not create the window.");

	glGenVertexArrays(1, &g_scop.gfx.vertex_array);
	glBindVertexArray(g_scop.gfx.vertex_array);

	build_vertex_buffer();

	g_scop.gfx.program = load_shaders("shader/scop.vertexshader", "shader/scop.fragmentshader");
	glUseProgram(g_scop.gfx.program);

	setPositionAttrib();
	setColorAttrib();

	set_view_matrix();
	g_scop.model_matrix = create_matrix();
	g_scop.proj_matrix = matrix_perspective(deg_to_rad(60.0f), 800.0f / 600.0f, 0.1f, 1000.0f);
	g_scop.gfx.mvpUni = glGetUniformLocation(g_scop.gfx.program, "mvp");

	do
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		render();
		glfwSwapBuffers(g_scop.gfx.window);
		glfwPollEvents();
	}
	while (glfwWindowShouldClose(g_scop.gfx.window) == 0);
}

void		destroy(void)
{
	glDeleteBuffers(1, &g_scop.gfx.vbo);
	glDeleteVertexArrays(1, &g_scop.gfx.vertex_array);
	glDeleteProgram(g_scop.gfx.program);
	glfwTerminate();
}
