#version 330 core
out vec4 FragColor;

uniform sampler2D tex0;

in vec2 fragPos;
in vec4 clip;

uniform float time;
uniform float SCREEN_WIDTH;
uniform float SCREEN_HEIGHT;
uniform bool rainbow;

void main() {
    vec4 texColor = texture(tex0, fragPos);
    if (texColor.a < 0.1)
        discard ;
    if (rainbow)
    {
        vec3 ndc = vec3(clip) / clip.w;

        float screenX = (ndc.x / 2.0f + 0.5f) * SCREEN_WIDTH;

        float speed = time * 40.0;
        float offset = (screenX) / 20;

        float red   = sin(offset + speed + 0.0);
        float green = sin(offset + speed + 2.0);
        float blue  = sin(offset + speed + 4.0);

        red = clamp(red, 0.0, 1.0);
        green = clamp(green, 0.0, 1.0);
        blue = clamp(blue, 0.0, 1.0);

        FragColor = vec4(red, green, blue, 1.0);
    }
    else
        FragColor = texColor;
}
