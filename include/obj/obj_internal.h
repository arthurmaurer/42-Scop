/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_internal.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/14 21:35:57 by amaurer           #+#    #+#             */
/*   Updated: 2015/09/20 00:33:03 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJ_INTERNAL_H
# define OBJ_INTERNAL_H

# include "obj.h"
# include "obj_tokens.h"
# define BUFF_SIZE 512
# define TYPE_COUNT 5
# define DEFAULT_CODE -9

typedef struct				s_type_match
{
	const char				*token;
	int						(*f)(const char **);
}							t_type_match;

int							parse_vec3(const char **tokens, t_vec3 *vector);
int							parse_vec2(const char **tokens, t_vec3 *vector);

int							parse_comment(const char **tokens);
int							parse_position(const char **tokens);
int							parse_color(const char **tokens);
int							parse_normal(const char **tokens);
int							parse_polygon(const char **tokens);

int							parse_line(char *line);

void						parser_die(const char *msg);

int							add_vertex(
								const char **tokens,
								int no_texture,
								t_lst *vertices);

static const t_type_match	g_type_matches[] = {
	{
		COMMENT_TOKEN,
		parse_comment,
	},
	{
		POSITION_TOKEN,
		parse_position,
	},
	{
		COLOR_TOKEN,
		parse_color,
	},
	{
		NORMAL_TOKEN,
		parse_normal,
	},
	{
		POLYGON_TOKEN,
		parse_polygon
	},
	{
		NULL,
		NULL
	}
};

unsigned int				g_current_line;
t_obj_data					*g_current_data;

#endif
