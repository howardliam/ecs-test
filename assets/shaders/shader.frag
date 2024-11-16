#version 460 core

// layout(location = 0) in vec3 colour;
layout(location = 0) in vec2 tex_coord;

layout(location = 0) out vec4 out_color;

uniform sampler2D tex0;

void main() {
    // out_color = vec4(colour, 1.0);
    out_color = texture(tex0, tex_coord);
}
