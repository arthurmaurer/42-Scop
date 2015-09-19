/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec32.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/20 00:16:01 by amaurer           #+#    #+#             */
/*   Updated: 2015/09/20 00:17:26 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"
#include <string.h>

int				vec3_is_null(const t_vec3 *vector)
{
	return (vector->x == 0 && vector->y == 0 && vector->z == 0);
}

int				vec3_equals(const t_vec3 *vector1, const t_vec3 *vector2)
{
	return (vector1->x == vector2->x
			&& vector1->y == vector2->y
			&& vector1->z == vector2->z);
}

void			vec3_swap(t_vec3 **vector1, t_vec3 **vector2)
{
	t_vec3	*tmp;

	tmp = *vector1;
	*vector1 = *vector2;
	*vector2 = tmp;
}

void			vec3_set(t_vec3 *vector, float x, float y, float z)
{
	vector->x = x;
	vector->y = y;
	vector->z = z;
}

void			vec3_copy(t_vec3 *dest, const t_vec3 *src)
{
	memcpy(dest, src, sizeof(t_vec3));
}
