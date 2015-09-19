/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_delete_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/14 21:35:57 by amaurer           #+#    #+#             */
/*   Updated: 2015/09/20 00:01:56 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "obj_internal.h"

static void		delete_polygons(void *polygon_ptr)
{
	t_polygon	*polygon;

	polygon = (t_polygon *)polygon_ptr;
	lst_destroy(&polygon->vertices, free);
}

void			obj_delete_data(t_obj_data **d)
{
	t_obj_data	*data;

	data = *d;
	lst_destroy(&data->positions, free);
	lst_destroy(&data->uvs, free);
	lst_destroy(&data->normals, free);
	lst_destroy(&data->polygons, delete_polygons);
	free(data);
	*d = NULL;
}
