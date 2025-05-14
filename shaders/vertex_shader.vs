#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec3 aColor;

out vec3 FragColor;
out vec3 FragPos;
out vec3 FragNormal;

out	vec2 texCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model * vec4(aPos, 1.0);
	FragColor = aColor;
	FragPos = aPos;
	FragNormal = aNormal;
	texCoord = vec2(FragPos.z, FragPos.y);
}
