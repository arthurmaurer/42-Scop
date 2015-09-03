#version 400 core

in vec3			position;
in vec3			color;
in vec2			uv;
in vec3			normal;

out	vec3		_color;
out vec2		_uv;
out vec3		_normal;
out vec3		_toLightVector;

uniform mat4	modelMatrix;
uniform vec3	lightPosition;
uniform mat4	mvp;

void	main()
{
	gl_Position = mvp * vec4(position, 1);

	_color = color;
	_uv = uv;

	vec4	worldPosition;

	worldPosition = modelMatrix * vec4(position, 1.0);

	_normal = (modelMatrix * vec4(normal, 0.0)).xyz;
	_toLightVector = lightPosition - worldPosition.xyz;
}
