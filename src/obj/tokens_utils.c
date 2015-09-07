#include <stdlib.h>
#include "obj_internal.h"

int			tokens_are_enough(const char **tokens, int qty)
{
	int		i;

	i = 0;
	while (i < qty)
	{
		if (!tokens[i++])
			return (0);
	}
	return (1);
}

int			token_to_int(const char **tokens, int index)
{
	int		j;
	int		ret;

	j = 0;
	while (j <= index)
	{
		if (!tokens[j++])
			return DEFAULT_CODE;
	}
	ret = atoi(tokens[index]) - 1;
	if (ret < 0)
		parser_die("A face index can't be negative.");
	return (ret);
}
