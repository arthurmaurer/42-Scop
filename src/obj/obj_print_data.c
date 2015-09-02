#include <stdio.h>
#include "obj_internal.h"

static void		print_vec3(void *data)
{
	t_vec3		*pos;

	pos = (t_vec3 *)data;
	printf("\tx = %f\n", pos->x);
	printf("\ty = %f\n", pos->y);
	printf("\tz = %f\n\n", pos->z);
}

static void		print_vec2(void *data)
{
	t_vec3		*pos;

	pos = (t_vec3 *)data;
	printf("\tx = %f\n", pos->x);
	printf("\ty = %f\n\n", pos->y);
}

static void		print_poly_component(void *data)
{
	t_vertex	*component;

	component = (t_vertex *)data;
	puts("***");
	print_vec3(&component->position);
	print_vec2(&component->uv);
	print_vec3(&component->normal);
	puts("***");
}

static void		print_polygons(void *data)
{
	t_lst		*components;

	puts("---");
	components = (t_lst *)((t_polygon *)data)->vertices;
	lst_print(components, print_poly_component, 0);
	puts("---");
}

void			obj_print_data(const t_obj_data *data)
{
	puts("--- POSITIONS ---");
	lst_print(data->positions, print_vec3, 0);
	puts("--- END POSITIONS ---");
	puts("--- UVS ---");
	lst_print(data->uvs, print_vec2, 0);
	puts("--- END UVS ---");
	puts("--- NORMALS ---");
	lst_print(data->normals, print_vec3, 0);
	puts("--- END NORMALS ---");
	puts("--- POLYGONS ---");
	lst_print(data->polygons, print_polygons, 0);
	puts("--- END POLYGONS ---");
}
