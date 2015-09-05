#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <Windows.h>
#include <stdio.h>
#include "scop.h"
#include <math.h>
#include "matrix.h"
#include "obj\obj.h"
#include <time.h>
#include "bmp.h"

t_scop	g_scop;

static unsigned	count_vertices(void)
{
	unsigned	count;
	unsigned	poly_length;
	t_lstiter	iter;

	count = 0;
	init_iter(&iter, g_scop.polygons, increasing);
	while (lst_iterator_next(&iter))
	{
		poly_length = ((t_polygon*)iter.data)->vertices->size;
		if (poly_length != 3)
			die("Scop can only handle triangle shapes.");
		count += poly_length;
	}
	return (count);
}

static int	parse_input_file(char const *pathname)
{
	t_obj_data	*obj_data;

	obj_data = obj_parse(pathname);

	if (obj_data == NULL)
		die("Could not open the OBJ file.");
	g_scop.polygons = obj_data->polygons;
	lst_destroy(&obj_data->positions, free);
	lst_destroy(&obj_data->uvs, free);
	lst_destroy(&obj_data->normals, free);
	free(obj_data);

	triangulate_polygons();

	g_scop.vertex_count = count_vertices();

	return (0);
}

int		main(void)
{
	int	width;
	int	height;
	unsigned char	*data;

	g_scop.wireframe = 0;
	g_scop.auto_rotate = 1;
	g_scop.prev_mouse_pos.x = -1.0f;
	g_scop.prev_mouse_pos.y = -1.0f;
	g_scop.lighting = 1;

	g_scop.light = create_light(NULL, NULL);
	vec3_set(&g_scop.light->position, 0.0f, 0.0f, 100.0f);
	vec3_set(&g_scop.light->color, 1.0f, 1.0f, 1.0f);

	srand(time(NULL));
	parse_input_file("scenes/cube.obj");
	launch();
	destroy();

	return (EXIT_SUCCESS);
}
