#include <stdlib.h>
#include <stdio.h>
#include "scop.h"
#include <math.h>
#include "matrix.h"
#include "obj/obj.h"
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

static void	set_default_colors(void)
{
	t_lstiter	it_poly;
	t_lstiter	it_vertex;
	t_vec3		color;
	t_vertex	*vertex;

	init_iter(&it_poly, g_scop.polygons, increasing);
	while (lst_iterator_next(&it_poly))
	{
		color.x = (rand() % 1000) / 1000.0f;
		color.y = (rand() % 1000) / 1000.0f;
		color.z = (rand() % 1000) / 1000.0f;
		init_iter(&it_vertex, ((t_polygon*)it_poly.data)->vertices, increasing);
		while (lst_iterator_next(&it_vertex))
		{
			vertex = (t_vertex*)it_vertex.data;
			vec3_copy(&vertex->color, &color);
		}
	}
}

static void	set_default_uvs(void)
{
	t_lstiter	it_poly;
	t_lstiter	it_vertex;
	t_vertex	*vertex;
	t_vertex	*prev_vertex;

	init_iter(&it_poly, g_scop.polygons, increasing);
	while (lst_iterator_next(&it_poly))
	{
		prev_vertex = NULL;
		init_iter(&it_vertex, ((t_polygon*)it_poly.data)->vertices, increasing);
		while (lst_iterator_next(&it_vertex))
		{
			vertex = (t_vertex*)it_vertex.data;

			if (is_vec2_defined(&vertex->uv))
				continue ;

			if (prev_vertex == NULL || (prev_vertex->uv.x == 0.0f && prev_vertex->uv.y == 1.0f))
			{
				vertex->uv.x = 0.0f;
				vertex->uv.y = 0.0f;
			}
			else if (prev_vertex->uv.x == 0.0f && prev_vertex->uv.y == 0.0f)
			{
				vertex->uv.x = 1.0f;
				vertex->uv.y = 0.0f;
			}
			else if (prev_vertex->uv.x == 1.0f && prev_vertex->uv.y == 0.0f)
			{
				vertex->uv.x = 1.0f;
				vertex->uv.y = 1.0f;
			}
			else if (prev_vertex->uv.x == 1.0f && prev_vertex->uv.y == 1.0f)
			{
				vertex->uv.x = 0.0f;
				vertex->uv.y = 1.0f;
			}
			prev_vertex = vertex;
		}
	}
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

	set_default_colors();
	set_default_uvs();
	triangulate_polygons();

	g_scop.vertex_count = count_vertices();

	return (0);
}

int		main(void)
{
	g_scop.wireframe = 0;
	g_scop.auto_rotate = 1;
	g_scop.prev_mouse_pos.x = -1.0f;
	g_scop.prev_mouse_pos.y = -1.0f;
	g_scop.lighting = 1;

	g_scop.light = create_light(NULL, NULL);
	vec3_set(&g_scop.light->position, 0.0f, 0.0f, 100.0f);
	vec3_set(&g_scop.light->color, 1.0f, 1.0f, 1.0f);

	srand((unsigned)time(NULL));
	parse_input_file("scenes/cube.obj");
	launch();
	destroy();

	return (EXIT_SUCCESS);
}
