
#include "scop.h"
#include "matrix.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "bmp.h"

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
	glUniform1i(g_scop.gfx.lightingUni, g_scop.lighting);
}

static void	buffer_load_poly(float *buffer, t_polygon const *poly)
{
	t_lstiter	iter;
	unsigned	i;
	t_vertex	*vertex;

	i = 0;
	init_iter(&iter, poly->vertices, increasing);
	while (lst_iterator_next(&iter))
	{
		vertex = (t_vertex*)iter.data;
		memcpy(buffer + i * 11, &vertex->position, sizeof(t_vec3));
		memcpy(buffer + i * 11 + 3, &vertex->color, sizeof(t_vec3));
		memcpy(buffer + i * 11 + 6, &vertex->uv, sizeof(t_vec2));
		memcpy(buffer + i * 11 + 8, &vertex->normal, sizeof(t_vec3));
		i++;
	}
}

void		build_vertex_buffer(void)
{
	unsigned	i;
	t_lstiter	iter;
	float		*buffer_data;
	unsigned	buffer_length;

	buffer_length = (3 + 3 + 2 + 3) * g_scop.vertex_count;
	buffer_data = (float*)calloc(buffer_length, sizeof(float));

	i = 0;
	init_iter(&iter, g_scop.polygons, increasing);
	while (lst_iterator_next(&iter))
	{
		buffer_load_poly(buffer_data + i * 11, (t_polygon*)iter.data);
		i += 3;
	}

	glGenBuffers(1, &g_scop.gfx.vbo);
	glBindBuffer(GL_ARRAY_BUFFER, g_scop.gfx.vbo);
	glBufferData(GL_ARRAY_BUFFER, buffer_length * sizeof(float), buffer_data, GL_STATIC_DRAW);
}

static void	setPositionAttrib(void)
{
	g_scop.gfx.posAttrib = glGetAttribLocation(g_scop.gfx.program, "position");
	glEnableVertexAttribArray(g_scop.gfx.posAttrib);
	glVertexAttribPointer(g_scop.gfx.posAttrib, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 11, 0);
}

static void	setColorAttrib(void)
{
	g_scop.gfx.colAttrib = glGetAttribLocation(g_scop.gfx.program, "color");
	glEnableVertexAttribArray(g_scop.gfx.colAttrib);
	glVertexAttribPointer(g_scop.gfx.colAttrib, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 11, (void*)(sizeof(float) * 3));
}

static void	setUVAttrib(void)
{
	GLuint	id;

	id = glGetAttribLocation(g_scop.gfx.program, "uv");
	glEnableVertexAttribArray(id);
	glVertexAttribPointer(id, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 11, (void*)(sizeof(GLfloat) * 6));
}

static void	setNormalAttrib(void)
{
	GLuint	id;

	id = glGetAttribLocation(g_scop.gfx.program, "normal");
	glEnableVertexAttribArray(id);
	glVertexAttribPointer(id, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 11, (void*)(sizeof(GLfloat) * 8));
}

static void	load_texture(void)
{
	int				width;
	int				height;
	unsigned char	*image;

	glGenTextures(1, &g_scop.gfx.texture);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, g_scop.gfx.texture);
	image = parse_bmp("scenes/texture.bmp", &width, &height);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, image);
	free(image);
	glUniform1i(glGetUniformLocation(g_scop.gfx.program, "texture"), 0);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

static void	set_light_uniforms(void)
{
	g_scop.gfx.lightPositionUni = glGetUniformLocation(g_scop.gfx.program, "lightPosition");
	glUniform3f(g_scop.gfx.lightPositionUni, g_scop.light->position.x, g_scop.light->position.y, g_scop.light->position.z);
	g_scop.gfx.lightColorUni = glGetUniformLocation(g_scop.gfx.program, "lightColor");
	glUniform3f(g_scop.gfx.lightColorUni, g_scop.light->color.x, g_scop.light->color.y, g_scop.light->color.z);
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
	setUVAttrib();
	setNormalAttrib();

	load_texture();

	g_scop.view_matrix = create_matrix();
	g_scop.model_matrix = matrix_scale_xyz(NULL, 0.2f);
	g_scop.proj_matrix = matrix_perspective(deg_to_rad(60.0f), 800.0f / 600.0f, 0.0f, 1000.0f);
	g_scop.gfx.mvpUni = glGetUniformLocation(g_scop.gfx.program, "mvp");
	g_scop.gfx.model_matrix_uni = glGetUniformLocation(g_scop.gfx.program, "modelMatrix");

	g_scop.gfx.lightingUni = glGetUniformLocation(g_scop.gfx.program, "lighting");
	glUniform1i(g_scop.gfx.lightingUni, g_scop.lighting);
	g_scop.gfx.textureLevelUni = glGetUniformLocation(g_scop.gfx.program, "textureLevel");
	glUniform1f(g_scop.gfx.textureLevelUni, g_scop.texture_level);

	set_light_uniforms();

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
