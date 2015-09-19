/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/19 23:56:53 by amaurer           #+#    #+#             */
/*   Updated: 2015/09/20 00:03:46 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>

int				ft_cisvalid(int c, const char *to_avoid)
{
	while (*to_avoid != '\0')
	{
		if (*to_avoid == c)
			return (0);
		++to_avoid;
	}
	return (1);
}

static size_t	clean_string_get_word_count(char *str, const char *to_avoid)
{
	int			i;
	int			j;
	size_t		word_count;

	i = 0;
	j = 0;
	word_count = 0;
	while (str[i] != '\0')
	{
		if (!ft_cisvalid(str[i], to_avoid))
			str[i] = '\0';
		++i;
	}
	while (j < i)
	{
		if (j < i && str[j] != '\0' && ++word_count)
		{
			while (j < i && str[j] != '\0')
				++j;
		}
		else
			++j;
	}
	return (word_count);
}

char			**ft_split(const char *str, const char *to_avoid)
{
	size_t		i;
	size_t		j;
	size_t		word_count;
	char		*tmp;
	char		**ret;

	i = 0;
	j = 0;
	tmp = strdup(str);
	word_count = clean_string_get_word_count(tmp, to_avoid);
	if (!(ret = NULL)
			&& !(ret = (char**)malloc(sizeof(char *) * (word_count + 1))))
		return (NULL);
	ret[word_count] = NULL;
	while (i < word_count)
	{
		while (tmp[j] == '\0')
			++j;
		ret[i] = strdup(tmp + j);
		++i;
		j += strlen(tmp + j);
	}
	free(tmp);
	return (ret);
}

void			ft_free_tab(char **tab)
{
	int		i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}
