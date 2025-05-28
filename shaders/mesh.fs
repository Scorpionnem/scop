#version 330 core

in vec3 FragColor;
in vec3 FragPos;
in vec3 FragNormal;
in vec3 FragAbsNormal;

out vec4 outColor;

in vec2 texCoord;

uniform sampler2D tex0;

uniform float texIntensity;
uniform float colorIntensity;

uniform vec3 lightColor;
uniform vec3 lightPos;
uniform float ambientStrength;

uniform int shaderEffect;
uniform float time;

uniform vec3 viewPos;

void main()
{
	vec4 textureColor = texture(tex0, texCoord);
	vec4 finalTexture = textureColor * texIntensity;
	
	vec3 tempColor = FragColor + FragAbsNormal;
	vec4 finalColor = vec4(tempColor, 1.0) * colorIntensity;

	if (textureColor.r == 1 && textureColor.g == 0 && textureColor.b == 1 && texIntensity != 0)
        discard ;

	vec3 ambient = ambientStrength * lightColor;
	float specularStrength = 0.5;

	vec3 norm = normalize(FragNormal);
	vec3 lightDir = normalize(lightPos - FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;

	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);

	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 64);
	vec3 specular = specularStrength * spec * lightColor;

	vec3 result = (ambient + diffuse + specular);
	result = clamp(result, 0.0, 1.0);

	if (shaderEffect == 0) // No effect
	{
		outColor = vec4(result, 1.0) * (finalTexture + finalColor);
	}
	else if (shaderEffect == 1) //Black and white effect
	{
		outColor = vec4(result, 1.0) * (finalTexture + finalColor);
		float maxColor = min(min(outColor.x, outColor.y), outColor.z);
		outColor = vec4(maxColor, maxColor, maxColor, 1.0);
	}
	else if (shaderEffect == 2) // Inverted color effect
	{
		outColor = vec4(result, 1.0) * (finalTexture + finalColor);
		outColor = vec4(1 - outColor.x, 1 - outColor.y, 1 - outColor.z, 1.0);
	}
	else if (shaderEffect == 3) //Rotating textures effect
	{
		vec4 finalTexture = texture(tex0, vec2(texCoord.x + sin(time), texCoord.y + cos(time))) * texIntensity;
		outColor = vec4(result, 1.0) * (finalTexture + finalColor);
	}
}
