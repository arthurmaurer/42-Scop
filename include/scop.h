/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/20 00:28:39 by amaurer           #+#    #+#             */
/*   Updated: 2015/09/20 00:34:17 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	GLuint		mvp_uni;
	GLuint		model_matrix_uni;
	GLuint		lighting_uni;
	GLuint		light_position_uni;
	GLuint		light_color_uni;
	GLuint		texture_level_uni;
	GLuint		pos_attrib;
	GLuint		col_attrib;
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
	float		texture_level;
	int			lighting;
	int			auto_rotate;
	int			user_control;
	t_light		*light;
	t_vec2		prev_mouse_pos;
	t_vec3		clear_color;
	char		*texture_diffuse;
	char		*obj_file;
	t_gfx		gfx;
}				t_scop;

GLFWwindow		*create_window(void);
GLuint			load_shaders(char const *vertex_shader_path,
	char const *fragment_shader_path);
int				parse_input_file(char const *pathname);
void			launch(void);
void			destroy(void);
void			render(void);
void			toggle_wireframe_mode(void);
void			toggle_texturing(void);
void			toggle_lighting(void);
void			switch_clear_color(void);
void			set_position_attrib(void);
void			set_color_attrib(void);
void			set_uv_attrib(void);
void			set_normal_attrib(void);
void			build_vertex_buffer(void);
void			handle_keys(GLFWwindow *window, int button, int scancode,
	int action, int mods);
void			handle_scroll(GLFWwindow *window, double scroll_x,
	double scroll_y);
void			handle_mouse_move(GLFWwindow *window, double pos_x,
	double pos_y);
void			handle_mouse_button(GLFWwindow *window, int button,
	int action, int mods);
int				die(char const *message);
float			deg_to_rad(float deg);
float			*look_at(float *m, t_vec3 const *eye, t_vec3 const *center,
	t_vec3 const *up);
char			**ft_split(const char *str, const char *to_avoid);
void			ft_free_tab(char **tab);
t_light			*create_light(t_vec3 const *position, t_vec3 const *color);
void			triangulate_polygons(void);

#endif
