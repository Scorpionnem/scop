#version 330 core

out vec4 FragColor;

in vec3 TexCoords;

uniform samplerCube skybox;
uniform float skyboxIntensity;
uniform float backgroundIntensity;

uniform vec3 background;

void main()
{
    vec3 textureColor = texture(skybox, TexCoords).rgb * skyboxIntensity;
    vec3 backgroundColor = background * backgroundIntensity;

    FragColor = vec4(textureColor + backgroundColor, 1.0);
}
