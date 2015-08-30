
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "vec3.h"
#include "matrix.h"

#ifdef _WIN32
	#define M_PI 3.14159265358979323846
	#include <Windows.h>
#endif

int		die(char const *message)
{
	//printf("%s\n", message);
	OutputDebugString(message);
	OutputDebugString("\n");
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
	matrix[2] =-f.x;
	matrix[6] =-f.y;
	matrix[10] =-f.z;
	matrix[12] =-vec3_dot(&s, eye);
	matrix[13] =-vec3_dot(&u, eye);
	matrix[14] = vec3_dot(&f, eye);

	return (matrix);
}
/*
detail::tvec3<T, P> f(normalize(center - eye));
detail::tvec3<T, P> s(normalize(cross(f, up)));
detail::tvec3<T, P> u(cross(s, f));

detail::tmat4x4<T, P> Result(1);
Result[0][0] = s.x;
Result[1][0] = s.y;
Result[2][0] = s.z;
Result[0][1] = u.x;
Result[1][1] = u.y;
Result[2][1] = u.z;
Result[0][2] =-f.x;
Result[1][2] =-f.y;
Result[2][2] =-f.z;
Result[3][0] =-dot(s, eye);
Result[3][1] =-dot(u, eye);
Result[3][2] = dot(f, eye);
return Result;
*/