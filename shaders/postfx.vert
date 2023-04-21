#version 430 core

layout(location = 0) in vec2 position;
layout(location = 1) in vec2 tex_coords;

layout(location = 2) out vec2 out_tex_coords;

void main() {
    gl_Position = vec4(position.xy, 1.0f, 1.0f); 
    out_tex_coords = tex_coords;
}  