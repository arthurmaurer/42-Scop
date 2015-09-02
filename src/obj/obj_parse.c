#include <stdlib.h>
#include <stdio.h>
#include "ftlst.h"
#include "obj_internal.h"

static int		init_parser(t_obj_data *data)
{
	g_current_line = 0;
	g_current_data = data;
	data->positions = new_lst();
	data->uvs = new_lst();
	data->normals = new_lst();
	data->polygons = new_lst();
	return (1);
}

t_obj_data		*obj_parse(const char *file_path)
{
	FILE		*fp;
	char		line[BUFF_SIZE];
	t_obj_data	*data;

	if (!(fp = fopen(file_path, "r"))
		|| !(data = malloc(sizeof(t_obj_data)))
		|| !init_parser(data))
		return (NULL);
	while (fgets(line, BUFF_SIZE, fp) != NULL && ++g_current_line)
	{
		if (line[0] == '\n')
			continue ;
		if (!parse_line(line))
			return (NULL);
	}
	fclose(fp);
	return (data);
}
