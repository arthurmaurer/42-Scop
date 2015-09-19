/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/20 00:12:43 by amaurer           #+#    #+#             */
/*   Updated: 2015/09/20 00:15:01 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"
#include <stdio.h>
#include <string.h>

void	matrix_copy(float *dest, float const *src)
{
	memcpy(dest, src, sizeof(float) * 16);
}

float	*matrix_mult(float *dest, float const *left, float const *right)
{
	float		final_matrix[16];
	unsigned	i;
	unsigned	j;

	i = 0;
	while (i < 16)
	{
		final_matrix[i] = 0;
		j = 0;
		while (j < 4)
		{
			final_matrix[i] += left[((i / 4) * 4 + j)] * right[(j * 4 + i % 4)];
			j++;
		}
		i++;
	}
	if (dest == NULL)
		return (matrix_clone(final_matrix));
	matrix_copy(dest, final_matrix);
	return (dest);
}

float	*matrix_mult_m(float *dest, unsigned n, ...)
{
	va_list		list;
	unsigned	i;
	float		*matrix;

	va_start(list, n);
	i = 0;
	while (i < n)
	{
		matrix = va_arg(list, float*);
		matrix_mult(dest, dest, matrix);
		i++;
	}
	va_end(list);
	return (dest);
}

void	matrix_debug(float const *matrix)
{
	printf("%f\t%f\t%f\t%f\n%f\t%f\t%f\t%f\n%f\t%f\t"
		"%f\t%f\n%f\t%f\t%f\t%f\n",
		matrix[0], matrix[1], matrix[2], matrix[3],
		matrix[4], matrix[5], matrix[6], matrix[7],
		matrix[8], matrix[9], matrix[10], matrix[11],
		matrix[12], matrix[13], matrix[14], matrix[15]);
}

float	*matrix_translate(float *dest, t_vec3 const *amount)
{
	float	translation[16];

	matrix_identity(translation);
	translation[3] = amount->x;
	translation[7] = amount->y;
	translation[11] = amount->z;
	if (dest == NULL)
		return (matrix_clone(translation));
	return (matrix_mult(dest, dest, translation));
}
