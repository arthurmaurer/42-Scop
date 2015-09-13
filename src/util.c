
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "vec3.h"
#include "matrix.h"

#ifndef M_PI
	#define M_PI 3.14159265358979323846
#endif

int		die(char const *message)
{
	#ifdef _WIN32
	OutputDebugString(message);
	OutputDebugString("\n");
	#else
		printf("%s\n", message);
	#endif
	exit(EXIT_FAILURE);
	return (0);
}

float	deg_to_rad(float deg)
{
	return (deg * ((float)M_PI / 180.0f));
}

float	*look_at(float *matrix, t_vec3 const *eye, t_vec3 const *center, t_vec3 const *up)
{
	t_vec3	f;
	t_vec3	s;
	t_vec3	u;

	if (matrix == NULL)
		matrix = create_matrix();
	else
		matrix_identity(matrix);

	if (vec3_equals(eye, center))
	{
		matrix_identity(matrix);
		return (matrix);
	}

	vec3_copy(&f, center);
	vec3_sub(&f, eye);
	vec3_normalize(&f);

	vec3_copy(&s, &f);
	vec3_cross(&s, up);
	vec3_normalize(&s);

	vec3_copy(&u, &s);
	vec3_cross(&u, &f);


	matrix[0] = s.x;
	matrix[4] = s.y;
	matrix[8] = s.z;
	matrix[1] = u.x;
	matrix[5] = u.y;
	matrix[9] = u.z;
	matrix[2] = -f.x;
	matrix[6] = -f.y;
	matrix[10] = -f.z;
	matrix[12] = -vec3_dot(&s, eye);
	matrix[13] = -vec3_dot(&u, eye);
	matrix[14] = vec3_dot(&f, eye);

	return (matrix);
}

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

void		ft_free_tab(char **tab)
{
	int		i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}
