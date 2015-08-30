
#include "scop.h"
#include "matrix.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#ifdef _WIN32
	#include <Windows.h>
#endif

float	*matrix_perspective(float fov, float aspect, float near_plane, float far_plane)
{
	GLfloat	*matrix;
	float	tan_half_fov;
	
	matrix = create_matrix();
	tan_half_fov = tanf(fov / 2.0f);
	matrix[0] = 1.0f / (aspect * tan_half_fov);
	matrix[5] = 1.0f / (tan_half_fov);
	matrix[10] = (far_plane + near_plane) / (far_plane - near_plane) * -1;
	matrix[11] = -1.0f;
	matrix[14] = (2.0f * far_plane * near_plane) / (far_plane - near_plane) * -1;
	return (matrix);
}

GLfloat	*create_matrix(void)
{
	GLfloat	*matrix;

	matrix = (float*) calloc(16, sizeof(float));
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
		return matrix_clone(final_matrix);
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
	char	buffer[300] = { 0 };

	sprintf(buffer, "%f\t%f\t%f\t%f\n%f\t%f\t%f\t%f\n%f\t%f\t%f\t%f\n%f\t%f\t%f\t%f\n",
		matrix[0], matrix[1], matrix[2], matrix[3], 
		matrix[4], matrix[5], matrix[6], matrix[7], 
		matrix[8], matrix[9], matrix[10], matrix[11], 
		matrix[12], matrix[13], matrix[14], matrix[15]);
	OutputDebugString(buffer);
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
