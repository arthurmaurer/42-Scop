/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/07 19:06:58 by amaurer           #+#    #+#             */
/*   Updated: 2015/09/20 00:18:16 by amaurer          ###   ########.fr       */
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
