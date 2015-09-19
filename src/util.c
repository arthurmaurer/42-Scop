/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/19 23:41:29 by amaurer           #+#    #+#             */
/*   Updated: 2015/09/19 23:58:00 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "vec3.h"
#include "matrix.h"

#define A	m[0]=s.x;m[4]=s.y;m[8]=s.z;m[1]=u.x;m[5]=u.y;m[9]=u.z;m[2]=-f.x
#define B	m[6]=-f.y;m[10]=-f.z;m[12]=-vec3_dot(&s, eye)
#define C	m[13]=-vec3_dot(&u, eye);m[14]=vec3_dot(&f, eye)

int		die(char const *message)
{
	printf("%s\n", message);
	exit(EXIT_FAILURE);
	return (0);
}

float	deg_to_rad(float deg)
{
	return (deg * ((float)M_PI / 180.0f));
}

float	*look_at(float *m, t_vec3 const *eye, t_vec3 const *center,
	t_vec3 const *up)
{
	t_vec3	f;
	t_vec3	s;
	t_vec3	u;

	if (m == NULL)
		m = create_matrix();
	else
		matrix_identity(m);
	if (vec3_equals(eye, center))
	{
		matrix_identity(m);
		return (m);
	}
	vec3_copy(&f, center);
	vec3_sub(&f, eye);
	vec3_normalize(&f);
	vec3_copy(&s, &f);
	vec3_cross(&s, up);
	vec3_normalize(&s);
	vec3_copy(&u, &s);
	vec3_cross(&u, &f);
	A;
	B;
	C;
	return (m);
}
