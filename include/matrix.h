/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/14 21:35:57 by amaurer           #+#    #+#             */
/*   Updated: 2015/09/20 00:31:50 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _MATRIX_H
# define _MATRIX_H

# include "vec3.h"
# include <stdarg.h>

float	*matrix_perspective(float fov, float aspect, float near_plane,
	float far_plane);
float	*create_matrix(void);
float	*matrix_clone(float const *matrix);
void	matrix_copy(float *dest, float const *src);
float	*matrix_mult(float *dest, float const *left, float const *right);
float	*matrix_mult_m(float *dest, unsigned n, ...);
void	matrix_identity(float *matrix);
void	matrix_debug(float const *matrix);
float	*matrix_translate(float *matrix, t_vec3 const *amount);
float	*matrix_scale(float *matrix, t_vec3 const *amount);
float	*matrix_scale_xyz(float *matrix, float amount);
float	*matrix_rotate_x(float *dest, float amount);
float	*matrix_rotate_y(float *dest, float amount);
float	*matrix_rotate_z(float *dest, float amount);

#endif
