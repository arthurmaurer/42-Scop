/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec36.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/20 00:18:24 by amaurer           #+#    #+#             */
/*   Updated: 2015/09/20 00:18:48 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"

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
