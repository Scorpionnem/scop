#version 330 core

in vec3 FragColor;
in vec3 FragPos;
in vec3 FragNormal;

out vec4 outColor;

void main()
{
	outColor = vec4(FragColor * FragNormal, 1.0);
}
