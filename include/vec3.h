/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/07 19:59:48 by amaurer           #+#    #+#             */
/*   Updated: 2015/07/09 00:14:10 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC3_H
# define VEC3_H

typedef struct	s_vec2
{
	float		x;
	float		y;
}				t_vec2;

typedef struct	s_vec3
{
	float		x;
	float		y;
	float		z;
}				t_vec3;

t_vec3			*vec3_new(float x, float y, float z);
t_vec3			*vec3_zero(void);
t_vec3			*vec3_up(void);
t_vec3			*vec3_down(void);
t_vec3			*vec3_left(void);
t_vec3			*vec3_right(void);
t_vec3			*vec3_forward(void);
t_vec3			*vec3_back(void);
t_vec3			*vec3_clone(const t_vec3 *vector);

void			vec3_normalize(t_vec3 *vector);
t_vec3			*vec3_normalize_d(const t_vec3 *vector);
float			vec3_magnitude(const t_vec3 *vector);
float			vec3_dot(const t_vec3 *vector1, const t_vec3 *vector2);
void			vec3_cross(t_vec3 *vector1, const t_vec3 *vector2);
t_vec3			*vec3_cross_d(const t_vec3 *vector1, const t_vec3 *vector2);

void			vec3_add(t_vec3 *vector, const t_vec3 *modifier);
void			vec3_sub(t_vec3 *vector, const t_vec3 *modifier);
void			vec3_mult(t_vec3 *vector, float factor);

t_vec3			*vec3_add_d(const t_vec3 *vector, const t_vec3 *modifier);
t_vec3			*vec3_sub_d(const t_vec3 *vector, const t_vec3 *modifier);
t_vec3			*vec3_mult_d(const t_vec3 *vector, float factor);

int				vec3_is_null(const t_vec3 *vector);
int				vec3_equals(const t_vec3 *vector1, const t_vec3 *vector2);

void			vec3_swap(t_vec3 **vector1, t_vec3 **vector2);
void			vec3_set(t_vec3 *vector, float x, float y, float z);
void			vec3_copy(t_vec3 *dest, const t_vec3 *src);

#endif
