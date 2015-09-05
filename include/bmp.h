
#ifndef _BMP_H
# define _BMP_H

#pragma pack(1)
typedef struct	s_bmp_header
{
	char		type[2];
	unsigned	size;
	short		reserved1;
	short		reserved2;
	unsigned	data_offset;
}				t_bmp_header;

typedef struct	s_bmp_dib_header
{
	unsigned	header_size;
	int			image_width;
	int			image_height;
	short		color_planes;
	short		bits_per_pixel;
	unsigned	compression_method;
	unsigned	image_size;
	int			horizontal_resolution;
	int			vertical_resolution;
	int			colors;
	int			important_colors;
	char	lol;
}				t_bmp_dib_header;
#pragma pack()

unsigned char	*parse_bmp(char const *pathname, int *width, int *height);

#endif