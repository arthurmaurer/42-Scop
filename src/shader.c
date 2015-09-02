
#include <fcntl.h>
#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "scop.h"

#define _CRT_SECURE_NO_DEPRECATE

static char		*read_file(char const *path)
{
	char	*content;
	size_t	length;
	FILE	*file;

	file = fopen(path, "r");
	if (file == NULL)
		return (NULL);
	fseek(file, 0, SEEK_END);
	length = ftell(file);
	rewind(file);

	content = (char*) calloc(length + 1, sizeof(char));
	fread(content, length, sizeof(char), file);
	fclose(file);

	return (content);
}

static void		compile_shader(GLuint shader_id, char const *code)
{
	GLint	length;
	GLint	result;
	GLint	log_length;
	char	log[200] = { 0 };

	length = strlen(code);
	glShaderSource(shader_id, 1, &code, &length);
	glCompileShader(shader_id);
	
	result = GL_FALSE;
	glGetShaderiv(shader_id, GL_COMPILE_STATUS, &result);
	glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &log_length);

	if (result == GL_FALSE)
	{
		glGetShaderInfoLog(shader_id, 200, NULL, log);
		die(log);
	}
}

static GLuint	create_program(GLuint vertex_shader, GLuint fragment_shader)
{
	GLuint	program;
	GLint	result;
	GLint	log_length;
	char	log[200] = { 0 };

	program = glCreateProgram();
	glAttachShader(program, vertex_shader);
	glAttachShader(program, fragment_shader);
	glLinkProgram(program);

	result = GL_FALSE;
	glGetProgramiv(program, GL_LINK_STATUS, &result);
	glGetProgramiv(program, GL_INFO_LOG_LENGTH, &log_length);
	
	if (result == GL_FALSE)
	{
		glGetProgramInfoLog(program, 200, NULL, log);
		die(log);
	}

	return (program);
}

GLuint			load_shaders(char const *vertex_shader_path, char const *fragment_shader_path)
{
	GLuint	vertex_shader;
	GLuint	fragment_shader;
	char	*vertex_shader_code;
	char	*fragment_shader_code;

	vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	
	vertex_shader_code = read_file(vertex_shader_path);
	if (vertex_shader_code == NULL)
		die("Could not read the vertex shader file.");
	fragment_shader_code = read_file(fragment_shader_path);
	if (fragment_shader_code == NULL)
		die("Could not read the fragment shader file.");

	compile_shader(vertex_shader, vertex_shader_code);
	compile_shader(fragment_shader, fragment_shader_code);

	return (create_program(vertex_shader, fragment_shader));
}
