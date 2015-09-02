/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsierra- <nsierra-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/12 04:25:01 by nsierra-          #+#    #+#             */
/*   Updated: 2015/04/12 04:25:02 by nsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJ_H
# define OBJ_H

# include "ftlst.h"
# include "scop.h"
/*
** Struct returned by parse_obj. It contains a list of everything in the file,
** where :
**	- positions correspond to 'v' ;
**	- uvs correspond to 'vt' ;
**	- normals correspond to 'vn' ;
**	- polygons correspond to 'f' ;
*/
typedef struct	s_obj_data
{
	t_lst		*positions;
	t_lst		*uvs;
	t_lst		*normals;
	t_lst		*polygons;
}				t_obj_data;

/*
** Use this function to retrieve data from a obj file path.
** Return values : the t_obj_data structure filled with everything the file
** contains or NULL if an error occured.
*/
t_obj_data		*obj_parse(const char *file_path);
/*
** Use this function to print all data. Very ugly.
*/
void			obj_print_data(const t_obj_data *data);
/*
** Use this function to free all space allocated by obj_parse.
*/
void			obj_delete_data(t_obj_data **data);

#endif