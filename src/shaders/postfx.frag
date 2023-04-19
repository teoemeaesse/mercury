#version 430 core

out vec4 frag_color;

layout(location = 2) in vec2 tex_coords;

uniform sampler2D base;
uniform sampler2D overlay;

void main() {
    const float gamma = 1.0;
    vec3 base_color = texture(base, tex_coords).rgb;
    vec3 overlay_color = texture(overlay, tex_coords).rgb;

    vec3 result = base_color + overlay_color * 5;
    result = pow(result, vec3(1.0 / gamma));
    frag_color = vec4(result, 1.0);
} 