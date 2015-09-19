/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/20 00:06:03 by amaurer           #+#    #+#             */
/*   Updated: 2015/09/20 00:09:43 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

t_scop	g_scop;

static int		usage(void)
{
	printf("usage: scop obj_path diffuse_path\n");
	return (EXIT_SUCCESS);
}

static void		init(int ac, char **av)
{
	srand((unsigned)time(NULL));
	g_scop.wireframe = 0;
	g_scop.auto_rotate = 1;
	g_scop.prev_mouse_pos.x = -1.0f;
	g_scop.prev_mouse_pos.y = -1.0f;
	g_scop.lighting = 1;
	if (ac == 2)
	{
		asprintf(&g_scop.obj_file, "scenes/%s/%s.obj", av[1], av[1]);
		asprintf(&g_scop.texture_diffuse, "scenes/%s/texture_diffuse.bmp",
			av[1]);
	}
	else if (ac == 3)
	{
		g_scop.obj_file = av[1];
		g_scop.texture_diffuse = av[2];
	}
}

int				main(int ac, char **av)
{
	if (ac != 2 && ac != 3)
		return (usage());
	init(ac, av);
	g_scop.light = create_light(NULL, NULL);
	vec3_set(&g_scop.light->position, 0.0f, 0.0f, 100.0f);
	vec3_set(&g_scop.light->color, 1.0f, 1.0f, 1.0f);
	parse_input_file(g_scop.obj_file);
	launch();
	destroy();
	return (EXIT_SUCCESS);
}
