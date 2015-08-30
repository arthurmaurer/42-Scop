
#ifndef _SCOP_H
# define _SCOP_H

# include <GL/glew.h>
# include <GLFW/glfw3.h>
# include "vec3.h"

# define WINDOW_WIDTH	800
# define WINDOW_HEIGHT	600

typedef struct	s_vertex
{
	t_vec3		position;
	t_vec3		color;
	t_vec2		uv;
}				t_vertex;

typedef struct	s_scop
{
	int	ok;
}				t_scop;

GLFWwindow		*create_window(void);
GLuint			load_shaders(char const *vertex_shader_path, char const *fragment_shader_path);

int				die(char const *message);
float			deg_to_rad(float deg);
float			*look_at(float *matrix, t_vec3 const *eye, t_vec3 const *center, t_vec3 const *up);

#endif
