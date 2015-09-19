/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_vec2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/14 21:35:57 by amaurer           #+#    #+#             */
/*   Updated: 2015/09/19 23:39:20 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "obj_internal.h"

int		parse_vec2(const char **tokens, t_vec3 *vector)
{
	if (!tokens_are_enough(tokens, 2))
		return (0);
	vector->x = atof(tokens[0]);
	vector->y = atof(tokens[1]);
	return (1);
}
