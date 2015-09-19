/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/14 21:35:57 by amaurer           #+#    #+#             */
/*   Updated: 2015/09/19 23:39:11 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdio.h>
#include "obj_internal.h"

static int	(*get_parse_func(const char *input))(const char **)
{
	int		i;

	i = 0;
	while (g_type_matches[i].token && g_type_matches[i].f)
	{
		if (!strcmp(g_type_matches[i].token, input))
			return (g_type_matches[i].f);
		++i;
	}
	return (NULL);
}

int			parse_line(char *line)
{
	char	**tokens;
	int		(*parse_function)(const char **);

	if (!(tokens = ft_split(line, " \t\n")))
		return (0);
	parse_function = get_parse_func(tokens[0]);
	if (!parse_function)
	{
		puts(tokens[0]);
		ft_free_tab(tokens);
		return (1);
		parser_die("Unknown data type.");
	}
	(*parse_function)((const char **)(tokens + 1));
	ft_free_tab(tokens);
	return (1);
}
