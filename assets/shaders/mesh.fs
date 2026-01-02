#version 330 core

in vec3 vPos;
in vec3 vNormal;
in vec2 vUV;

out vec4 FragColor;

struct Material
{
	vec3	ambient;
	vec3	diffuse;
	vec3	specular;

	float	shininess;
	float	opacity;
};

uniform Material uMaterial;

uniform vec3 uLightPos;
uniform vec3 uLightColor;
uniform vec3 uViewPos;

void main()
{
	vec3 N = normalize(vNormal);
	vec3 L = normalize(uLightPos - vPos);
	vec3 V = normalize(uViewPos - vPos);
	vec3 H = normalize(L + V);

	vec3 ambient = uMaterial.diffuse * 0.05 * uLightColor;

	float diff = max(dot(N, L), 0.0);
	vec3 diffuse = uMaterial.diffuse * diff * uLightColor;

	float spec = pow(max(dot(N, H), 0.0), uMaterial.shininess);
	vec3 specular = uMaterial.specular * spec * uLightColor;

	vec3 color = ambient + diffuse + specular;

	FragColor = vec4(color, uMaterial.opacity);
}
