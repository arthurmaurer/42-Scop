
#ifndef _SCOP_H
# define _SCOP_H

# include <GL/glew.h>
# include <GLFW/glfw3.h>
# include <ftlst.h>
# include "vec3.h"

# define WINDOW_WIDTH	800
# define WINDOW_HEIGHT	600

typedef t_lst	*t_lst_vec2;
typedef t_lst	*t_lst_vec3;
typedef t_lst	*t_lst_poly;

typedef struct	s_vertex
{
	t_vec3		position;
	t_vec3		color;
	t_vec2		uv;
	t_vec3		normal;
}				t_vertex;

typedef struct	s_polygon
{
	t_lst		*vertices;
}				t_polygon;

typedef struct	s_gfx
{
	GLuint		program;
	GLuint		vbo;
	GLuint		ebo;
	GLuint		vertex_array;
	GLuint		modelUni;
	GLuint		viewUni;
	GLuint		projUni;
	GLuint		mvpUni;
	GLuint		posAttrib;
	GLuint		colAttrib;
	GLFWwindow	*window;
}				t_gfx;

typedef struct	s_scop
{
	t_lst_vec3	*points;
	t_lst_vec2	*uvs;
	t_lst_vec3	*colors;
	t_lst_vec3	*normals;
	t_lst_poly	*polygons;
	float		*model_matrix;
	float		*view_matrix;
	float		*proj_matrix;
	int			wireframe;
	t_gfx		gfx;
}				t_scop;

GLFWwindow		*create_window(void);
GLuint			load_shaders(char const *vertex_shader_path, char const *fragment_shader_path);

int				parse_obj(const char *file_path, t_lst *v, t_lst *t, t_lst *f);

void			launch(void);
void			destroy(void);
void			handle_keys(GLFWwindow *window, int button, int scancode, int action, int mods);
void			render(void);

int				die(char const *message);
float			deg_to_rad(float deg);
float			*look_at(float *matrix, t_vec3 const *eye, t_vec3 const *center, t_vec3 const *up);
char			**ft_split(const char *str, const char *to_avoid);
void			ft_free_tab(char **tab);

#endif
