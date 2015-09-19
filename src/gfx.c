/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/20 00:27:01 by amaurer           #+#    #+#             */
/*   Updated: 2015/09/20 00:35:43 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include "matrix.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "bmp.h"

extern t_scop	g_scop;

static void	load_texture(void)
{
	int				width;
	int				height;
	unsigned char	*image;

	glGenTextures(1, &g_scop.gfx.texture);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, g_scop.gfx.texture);
	image = parse_bmp(g_scop.texture_diffuse, &width, &height);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR,
		GL_UNSIGNED_BYTE, image);
	free(image);
	glUniform1i(glGetUniformLocation(g_scop.gfx.program, "texture"), 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

static void	set_light_uniforms(void)
{
	g_scop.gfx.light_position_uni = glGetUniformLocation(g_scop.gfx.program,
		"lightPosition");
	glUniform3f(g_scop.gfx.light_position_uni, g_scop.light->position.x,
		g_scop.light->position.y, g_scop.light->position.z);
	g_scop.gfx.light_color_uni = glGetUniformLocation(g_scop.gfx.program,
		"lightColor");
	glUniform3f(g_scop.gfx.light_color_uni, g_scop.light->color.x,
		g_scop.light->color.y, g_scop.light->color.z);
}

static void	prepare_launch(void)
{
	glGenVertexArrays(1, &g_scop.gfx.vertex_array);
	glBindVertexArray(g_scop.gfx.vertex_array);
	build_vertex_buffer();
	g_scop.gfx.program = load_shaders("shader/scop.vertexshader",
		"shader/scop.fragmentshader");
	glUseProgram(g_scop.gfx.program);
	set_position_attrib();
	set_color_attrib();
	set_uv_attrib();
	set_normal_attrib();
	load_texture();
	g_scop.view_matrix = create_matrix();
	g_scop.model_matrix = matrix_scale_xyz(NULL, 0.2f);
	g_scop.proj_matrix = matrix_perspective(deg_to_rad(60.0f), 800.0f / 600.0f,
		0.0f, 1000.0f);
	g_scop.gfx.mvp_uni = glGetUniformLocation(g_scop.gfx.program, "mvp");
	g_scop.gfx.model_matrix_uni = glGetUniformLocation(g_scop.gfx.program,
		"modelMatrix");
	g_scop.gfx.lighting_uni = glGetUniformLocation(g_scop.gfx.program,
		"lighting");
	glUniform1i(g_scop.gfx.lighting_uni, g_scop.lighting);
	g_scop.gfx.texture_level_uni = glGetUniformLocation(g_scop.gfx.program,
		"textureLevel");
	glUniform1f(g_scop.gfx.texture_level_uni, g_scop.texture_level);
	set_light_uniforms();
}

void		launch(void)
{
	g_scop.gfx.window = create_window();
	if (g_scop.gfx.window == NULL)
		die("Could not create the window.");
	prepare_launch();
	while (glfwWindowShouldClose(g_scop.gfx.window) == 0)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		render();
		glfwSwapBuffers(g_scop.gfx.window);
		glfwPollEvents();
	}
}

void		destroy(void)
{
	glDeleteBuffers(1, &g_scop.gfx.vbo);
	glDeleteVertexArrays(1, &g_scop.gfx.vertex_array);
	glDeleteProgram(g_scop.gfx.program);
	glfwTerminate();
}
