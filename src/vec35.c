/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec35.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/20 00:17:58 by amaurer           #+#    #+#             */
/*   Updated: 2015/09/20 00:18:49 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"

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
