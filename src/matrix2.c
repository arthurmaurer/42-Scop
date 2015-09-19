/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/20 00:10:21 by amaurer           #+#    #+#             */
/*   Updated: 2015/09/20 00:12:24 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"
#include <string.h>
#include <math.h>

float	*matrix_scale(float *dest, t_vec3 const *amount)
{
	float	scaling[16];

	matrix_identity(scaling);
	scaling[0] = amount->x;
	scaling[5] = amount->y;
	scaling[10] = amount->z;
	if (dest == NULL)
		return (matrix_clone(scaling));
	return (matrix_mult(dest, dest, scaling));
}

float	*matrix_scale_xyz(float *dest, float amount)
{
	t_vec3	vec;

	vec.x = amount;
	vec.y = amount;
	vec.z = amount;
	return (matrix_scale(dest, &vec));
}

float	*matrix_rotate_x(float *dest, float amount)
{
	float	rotation[16];

	matrix_identity(rotation);
	rotation[5] = cosf(amount);
	rotation[6] = sinf(amount) * -1;
	rotation[9] = sinf(amount);
	rotation[10] = cosf(amount);
	if (dest == NULL)
		return (matrix_clone(rotation));
	return (matrix_mult(dest, dest, rotation));
}

float	*matrix_rotate_y(float *dest, float amount)
{
	float	rotation[16];

	matrix_identity((float*)&rotation);
	rotation[0] = cosf(amount);
	rotation[2] = sinf(amount);
	rotation[8] = sinf(amount) * -1;
	rotation[10] = cosf(amount);
	if (dest == NULL)
		return (matrix_clone(rotation));
	return (matrix_mult(dest, dest, rotation));
}

float	*matrix_rotate_z(float *dest, float amount)
{
	float	rotation[16];

	matrix_identity((float*)&rotation);
	rotation[0] = cosf(amount);
	rotation[1] = sinf(amount) * -1;
	rotation[4] = sinf(amount);
	rotation[5] = cosf(amount);
	if (dest == NULL)
		return (matrix_clone(rotation));
	return (matrix_mult(dest, dest, rotation));
}
