#version 330 core

in vec3 vPos;
in vec3 vNormal;
in vec2 vUV;

out vec4 FragColor;

void main()
{
	vec3 n = normalize(vNormal);
	FragColor = vec4(vNormal, 1.0);
}
