
#ifndef _SCOP_H
# define _SCOP_H

# include <GL/glew.h>
# include <GLFW/glfw3.h>
# include <ftlst.h>
# include "vec3.h"

# define WINDOW_WIDTH			800
# define WINDOW_HEIGHT			600

# define USER_CONTROL_NONE		0
# define USER_CONTROL_ROTATE	1
# define USER_CONTROL_TRANSLATE	3

typedef struct	s_light
{
	t_vec3		position;
	t_vec3		color;
}				t_light;

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
	GLuint		vertex_array;
	GLuint		mvpUni;
	GLuint		model_matrix_uni;
	GLuint		texturingUni;
	GLuint		lightingUni;
	GLuint		lightPositionUni;
	GLuint		lightColorUni;
	GLuint		posAttrib;
	GLuint		colAttrib;
	GLuint		texture;
	GLFWwindow	*window;
}				t_gfx;

typedef struct	s_scop
{
	t_lst		*polygons;
	unsigned	vertex_count;
	float		*model_matrix;
	float		*view_matrix;
	float		*proj_matrix;
	int			wireframe;
	int			texturing;
	int			lighting;
	int			auto_rotate;
	int			user_control;
	t_light		*light;
	t_vec2		prev_mouse_pos;
	t_gfx		gfx;
}				t_scop;

GLFWwindow		*create_window(void);
GLuint			load_shaders(char const *vertex_shader_path, char const *fragment_shader_path);

int				parse_obj(const char *file_path, t_lst *v, t_lst *t, t_lst *f);

void			launch(void);
void			destroy(void);
void			render(void);

void			toggle_wireframe_mode(void);
void			toggle_texturing(void);
void			toggle_lighting(void);

void			handle_keys(GLFWwindow *window, int button, int scancode, int action, int mods);
void			handle_scroll(GLFWwindow *window, double scroll_x, double scroll_y);
void			handle_mouse_move(GLFWwindow *window, double pos_x, double pos_y);
void			handle_mouse_button(GLFWwindow *window, int button, int action, int mods);

int				die(char const *message);
float			deg_to_rad(float deg);
float			*look_at(float *matrix, t_vec3 const *eye, t_vec3 const *center, t_vec3 const *up);
char			**ft_split(const char *str, const char *to_avoid);
void			ft_free_tab(char **tab);

t_light			*create_light(t_vec3 const *position, t_vec3 const *color);

#endif
