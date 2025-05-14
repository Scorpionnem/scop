#version 330 core

in vec3 FragColor;
in vec3 FragPos;
in vec3 FragNormal;

out vec4 outColor;

in vec2 texCoord;

uniform sampler2D tex0;

uniform float texIntensity;
uniform float colorIntensity;

void main()
{
	outColor = (texture(tex0, texCoord) * texIntensity) + (vec4(FragColor, 1.0) * colorIntensity);
}
