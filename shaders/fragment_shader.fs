#version 330 core

in vec3 FragColor;
in vec3 FragPos;
in vec3 FragNormal;

out vec4 outColor;

in vec2 texCoord;

uniform sampler2D tex0;

uniform float texIntensity;
uniform float colorIntensity;

uniform vec3 lightColor;
uniform vec3 lightPos;

void main()
{
	vec4 finalTexture = texture(tex0, texCoord) * texIntensity;
	vec4 finalColor = vec4(FragColor, 1.0) * colorIntensity;
	// outColor = (finalTexture + finalColor) + vec4(FragNormal, 1.0);

	float ambientStrength = 0.2;
	vec3 ambient = ambientStrength * lightColor;

	//diffuse lighting
	vec3 norm = normalize(FragNormal);
	vec3 lightDir = normalize(lightPos - FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;
	vec3 result = (ambient + diffuse);

	outColor = vec4(result, 1.0) * (finalTexture + finalColor);
}
