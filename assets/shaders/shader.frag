#version 420

layout(location = 0) in vec3 colour;

layout(location = 0) out vec4 outColor;

void main() {
    outColor = vec4(colour, 1.0);
}
