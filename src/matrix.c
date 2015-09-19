/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/19 23:48:26 by amaurer           #+#    #+#             */
/*   Updated: 2015/09/20 00:14:41 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include "matrix.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>

float	*matrix_perspective(float fov, float aspect, float near_plane,
	float far_plane)
{
	GLfloat	*matrix;
	float	tan_half_fov;

	matrix = create_matrix();
	tan_half_fov = tanf(fov / 2.0f);
	matrix[0] = 1.0f / (aspect * tan_half_fov);
	matrix[5] = 1.0f / (tan_half_fov);
	matrix[10] = (far_plane + near_plane) / (far_plane - near_plane) * -1;
	matrix[11] = -1.0f;
	matrix[14] = (2.0f * far_plane * near_plane)
	/ (far_plane - near_plane) * -1;
	return (matrix);
}

GLfloat	*create_matrix(void)
{
	GLfloat	*matrix;

	matrix = (float*)calloc(16, sizeof(float));
	matrix_identity(matrix);
	return (matrix);
}

void	matrix_identity(float *matrix)
{
	memset(matrix, 0, sizeof(float) * 16);
	matrix[0] = 1.0f;
	matrix[5] = 1.0f;
	matrix[10] = 1.0f;
	matrix[15] = 1.0f;
}

float	*matrix_clone(float const *matrix)
{
	float	*new_matrix;

	new_matrix = create_matrix();
	memcpy(new_matrix, matrix, sizeof(float) * 16);
	return (new_matrix);
}
