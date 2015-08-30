/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/07 19:06:58 by amaurer           #+#    #+#             */
/*   Updated: 2015/07/09 00:18:51 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>

t_vec3	*vec3_new(float x, float y, float z)
{
	t_vec3	*vector;

	vector = calloc(1, sizeof(t_vec3));
	vector->x = x;
	vector->y = y;
	vector->z = z;

	return (vector);
}

t_vec3			*vec3_zero(void)
{
	return (vec3_new(0, 0, 0));
}

t_vec3			*vec3_up(void)
{
	return (vec3_new(0, 1, 0));
}

t_vec3			*vec3_down(void)
{
	return (vec3_new(0, -1, 0));
}

t_vec3			*vec3_left(void)
{
	return (vec3_new(-1, 0, 0));
}

t_vec3			*vec3_right(void)
{
	return (vec3_new(1, 0, 0));
}

t_vec3			*vec3_forward(void)
{
	return (vec3_new(0, 0, 1));
}

t_vec3			*vec3_back(void)
{
	return (vec3_new(0, 0, -1));
}

t_vec3			*vec3_clone(const t_vec3 *vector)
{
	return (vec3_new(vector->x, vector->y, vector->z));
}

void			vec3_normalize(t_vec3 *vector)
{
	float	magn;

	magn = vec3_magnitude(vector);
	vector->x = vector->x / magn;
	vector->y = vector->y / magn;
	vector->z = vector->z / magn;
}

t_vec3			*vec3_normalize_d(const t_vec3 *vector)
{
	t_vec3	*normalized;

	normalized = vec3_clone(vector);
	vec3_normalize(normalized);
	return (normalized);
}

float			vec3_magnitude(const t_vec3 *vector)
{
	return (sqrtf(powf(vector->x, 2) + powf(vector->y, 2) + powf(vector->z, 2)));
}

float			vec3_dot(const t_vec3 *vector1, const t_vec3 *vector2)
{
	return (vector1->x * vector2->x + vector1->y * vector2->y + vector1->z * vector2->z);
}

void			vec3_add(t_vec3 *vector, const t_vec3 *modifier)
{
	vector->x += modifier->x;
	vector->y += modifier->y;
	vector->z += modifier->z;
}

void			vec3_sub(t_vec3 *vector, const t_vec3 *modifier)
{
	vector->x -= modifier->x;
	vector->y -= modifier->y;
	vector->z -= modifier->z;
}

void			vec3_mult(t_vec3 *vector, float factor)
{
	vector->x *= factor;
	vector->y *= factor;
	vector->z *= factor;
}

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
