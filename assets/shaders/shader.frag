#version 460 core

layout(location = 0) in vec2 tex_coord;

layout(location = 0) out vec4 out_colour;

uniform sampler2D tex0;

void main() {
    out_colour = texture(tex0, tex_coord);
}
