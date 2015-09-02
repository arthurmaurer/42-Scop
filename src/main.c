#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <Windows.h>
#include <stdio.h>
#include "scop.h"
#include <math.h>
#include "matrix.h"
#include "obj\obj.h"
#include <Windows.h>

t_scop	g_scop;

int		parse_input_file(char const *pathname)
{
	t_obj_data	*obj_data;

	obj_data = obj_parse(pathname);
	g_scop.points = (t_lst_vec3*)obj_data->positions;
	g_scop.uvs = (t_lst_vec2*)obj_data->uvs;
	g_scop.normals = (t_lst_vec3*)obj_data->normals;
	g_scop.polygons = (t_lst_poly*)obj_data->polygons;
	free(obj_data);

	return (0);
}

int		main(void)
{
	parse_input_file("scenes/cube.obj");
	launch();
	destroy();

	return (EXIT_SUCCESS);
}
