#version 330 core

in vec3 vPos;
in vec3 vNormal;
in vec2 vUV;

out vec4 FragColor;

struct Material
{
	vec3	ambient;

	vec3	diffuse;
	int		hasDiffuseTex;

	vec3	specular;

	float	shininess;
	float	opacity;
};

struct Light {
	vec3	pos;

	vec3	color;

	float	constant;
	float	linear;
	float	quadratic;
};

#define NR_POINT_LIGHTS_MAX 32
uniform int	NR_POINT_LIGHTS;
uniform Light	uLight[NR_POINT_LIGHTS_MAX];

uniform Material uMaterial;

uniform vec3 uViewPos;

uniform float uTime;

uniform int uTriangleCount;
// Use gl_PrimitiveID for triangle view mode

uniform sampler2D tex;

vec3 CalcPointLight(Light light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
	vec3 N = normalize(vNormal);
	vec3 L = normalize(light.pos - vPos);
	vec3 H = normalize(L + viewDir);

	vec3 ambient = uMaterial.diffuse * 0.05 * light.color;

	float diff = max(dot(N, L), 0.0);
	vec3 diffuse = uMaterial.diffuse * diff * light.color;

	float spec = pow(max(dot(N, H), 0.0), uMaterial.shininess);
	vec3 specular = uMaterial.specular * spec * light.color;

	float	distance = length(light.pos - vPos);
	float	attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;
	return (ambient + diffuse + specular);
}

void main()
{
	vec3 viewDir = normalize(uViewPos - vPos);

	vec4 materialColor = vec4(vec3(1), uMaterial.opacity);
	if (uMaterial.hasDiffuseTex == 1)
		materialColor = texture(tex, vUV);

	vec3 result = vec3(0);
	for (int i = 0; i < NR_POINT_LIGHTS; i++)
		result += CalcPointLight(uLight[i], vNormal, vPos, viewDir);

	materialColor.rgb = materialColor.rgb * result;

	FragColor = materialColor;
}
