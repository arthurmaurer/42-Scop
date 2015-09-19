/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_die.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/14 21:35:57 by amaurer           #+#    #+#             */
/*   Updated: 2015/09/20 00:04:22 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "obj_internal.h"

void	parser_die(const char *msg)
{
	printf("Parse error at line %u !\n%s\n", g_current_line, msg);
	exit(EXIT_FAILURE);
}
