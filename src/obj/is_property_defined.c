/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_property_defined.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/19 23:12:51 by amaurer           #+#    #+#             */
/*   Updated: 2015/09/19 23:21:12 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <float.h>
#include "obj_internal.h"

int		is_vec2_defined(t_vec2 *v)
{
	if (v->x == FLT_MAX && v->y == FLT_MAX)
		return (0);
	return (1);
}

int		is_vec3_defined(t_vec3 *v)
{
	if (v->x == FLT_MAX && v->y == FLT_MAX && v->z == FLT_MAX)
		return (0);
	return (1);
}
