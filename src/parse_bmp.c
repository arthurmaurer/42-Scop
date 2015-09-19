/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_bmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/19 22:55:03 by amaurer           #+#    #+#             */
/*   Updated: 2015/09/19 22:57:44 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bmp.h"
#include <stdio.h>
#include <stdlib.h>

unsigned char	*parse_bmp(char const *pathname, int *width, int *height)
{
	FILE				*file;
	t_bmp_header		header;
	t_bmp_dib_header	dib_header;
	unsigned char		*data;
	unsigned			size_read;

	file = fopen(pathname, "r+b");
	if (file == NULL)
		return (NULL);
	if (fread(&header, 1, sizeof(t_bmp_header), file) != sizeof(t_bmp_header))
		return (NULL);
	if (header.data_offset > header.data_offset)
		return (NULL);
	if (fread(&dib_header, 1, sizeof(dib_header), file) != sizeof(dib_header))
		return (NULL);
	*width = dib_header.image_width;
	*height = dib_header.image_height;
	fseek(file, header.data_offset, SEEK_SET);
	data = (unsigned char*)calloc(dib_header.image_size, sizeof(unsigned char));
	size_read = fread(data, 1, dib_header.image_size, file);
	if (size_read != dib_header.image_size)
		return (NULL);
	return (data);
}
