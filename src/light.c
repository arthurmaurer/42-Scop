/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/20 00:01:27 by amaurer           #+#    #+#             */
/*   Updated: 2015/09/20 00:01:29 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include <stdlib.h>

t_light	*create_light(t_vec3 const *position, t_vec3 const *color)
{
	t_light	*light;

	light = (t_light*)calloc(1, sizeof(t_light));
	if (position != NULL)
		vec3_copy(&light->position, position);
	if (color != NULL)
		vec3_copy(&light->color, color);
	return (light);
}
