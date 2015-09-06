#version 400 core

in vec3				_color;
in vec2				_uv;
in vec3				_normal;
in vec3				_toLightVector;

out vec4			color;

uniform bool		lighting;
uniform float		textureLevel;
uniform vec3		lightPosition;
uniform vec3		lightColor;
uniform sampler2D	tex;

void	main()
{
	color = vec4(_color, 1.0f);

	if (textureLevel > 0.0f)
		color = mix(color, texture(tex, _uv), textureLevel);

	if (!lighting)
		return ;

	vec3	normNormal;
	vec3	normLight;
	float	dotResult;
	float	brightness;
	vec3	diffuse;

	normNormal = normalize(_normal);
	normLight = normalize(_toLightVector);

	dotResult = dot(normNormal, normLight);
	brightness = max(dotResult, 0.2);
	diffuse = brightness * lightColor;

	color *= vec4(diffuse, 1.0);
}
