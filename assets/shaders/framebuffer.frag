#version 460 core

layout(location = 0) in vec2 tex_coord;

layout(location = 0) out vec4 out_colour;

uniform sampler2D screen_texture;

const vec2 texel_size = vec2(1.0) / vec2(1600.0, 900.0);
const float contrast = 0.3;

vec4 fxaa() {
    vec4 colour = texture(screen_texture, tex_coord);

    vec4 colour_left = texture(screen_texture, tex_coord - vec2(texel_size.x, 0.0));
    vec4 colour_right = texture(screen_texture, tex_coord + vec2(texel_size.x, 0.0));
    vec4 colour_up = texture(screen_texture, tex_coord + vec2(0.0, texel_size.y));
    vec4 colour_down = texture(screen_texture, tex_coord - vec2(0.0, texel_size.y));

    vec3 colour_diff = abs(colour.rgb - colour_left.rgb);
    vec3 edge_factor = max(colour_diff, abs(colour.rgb - colour_right.rgb));
    edge_factor = max(colour_diff, abs(colour.rgb - colour_down.rgb));
    edge_factor = max(colour_diff, abs(colour.rgb - colour_up.rgb));

    float max_edge = max(max(edge_factor.x, edge_factor.y), edge_factor.z);
    float alpha = smoothstep(0.1, 0.5, max_edge);

    vec4 smoothed_colour = mix(colour, (colour_left + colour_right + colour_up + colour_down) / 4.0, alpha);

    return smoothed_colour;
}

void main() {
    // out_color = texture(screen_texture, tex_coord);

    out_colour = fxaa();
    out_colour.rgb = (out_colour.rgb - 0.5) * (1.0 + contrast) + 0.5;
}
