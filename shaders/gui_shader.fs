#version 330 core
out vec4 FragColor;

uniform sampler2D tex0;

in vec2 fragPos;

void main() {
    FragColor = texture(tex0, fragPos);
}
