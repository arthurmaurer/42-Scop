/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_die.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/07 19:38:24 by amaurer           #+#    #+#             */
/*   Updated: 2015/09/07 19:41:20 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "obj_internal.h"
#ifdef _WIN32
# include <Windows.h>
#endif

void	parser_die(const char *msg)
{
	#ifdef _WIN32
	char	lol[400];
	sprintf(lol, "Parse error at line %u !\n%s\n", g_current_line, msg);
	OutputDebugString(lol);
	#else
	printf("Parse error at line %u !\n%s\n", g_current_line, msg);
	#endif
	exit(EXIT_FAILURE);
}
