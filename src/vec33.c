/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec33.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/20 00:16:34 by amaurer           #+#    #+#             */
/*   Updated: 2015/09/20 00:18:57 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"

void			vec3_cross(t_vec3 *vector1, const t_vec3 *vector2)
{
	float	x;
	float	y;
	float	z;

	x = vector1->y * vector2->z - vector1->z * vector2->y;
	y = vector1->z * vector2->x - vector1->x * vector2->z;
	z = vector1->x * vector2->y - vector1->y * vector2->x;
	vector1->x = x;
	vector1->y = y;
	vector1->z = z;
}

t_vec3			*vec3_cross_d(const t_vec3 *vector1, const t_vec3 *vector2)
{
	t_vec3	*result;

	result = vec3_clone(vector1);
	vec3_cross(result, vector2);
	return (result);
}

t_vec3			*vec3_add_d(const t_vec3 *vector, const t_vec3 *modifier)
{
	t_vec3	*out;

	out = vec3_clone(vector);
	vec3_add(out, modifier);
	return (out);
}

t_vec3			*vec3_sub_d(const t_vec3 *vector, const t_vec3 *modifier)
{
	t_vec3	*out;

	out = vec3_clone(vector);
	vec3_sub(out, modifier);
	return (out);
}

t_vec3			*vec3_mult_d(const t_vec3 *vector, float factor)
{
	t_vec3	*out;

	out = vec3_clone(vector);
	vec3_mult(out, factor);
	return (out);
}
