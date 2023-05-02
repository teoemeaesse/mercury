#version 430 core

layout(location = 0) out vec4 color;

// layout(location = 1) in vec3 velocity;


in vec3 v_position;


void main() {
    color = vec4(v_position, 255.0);
}