#version 330 core

in vec3 exPosition;
in vec2 exTexcoord;
in vec3 exNormal;

out vec4 FragmentColor;

uniform vec4 BaseColor;

vec3 normalColor(void) {
    return (exNormal + vec3(1.0)) * 0.5;
}

void main(void)
{
    FragmentColor = BaseColor + 0.2 * vec4(normalColor(), 1.0);
}
