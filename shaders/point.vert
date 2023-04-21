#version 430 core

uniform vec2 window;
uniform vec2 camera;
uniform float zoom;

layout(location = 0) in vec4 position;

out vec2 velocity;

void main() {
    gl_Position = vec4(((position.x - camera.x) / window.x) * zoom , ((position.y - camera.y) / window.y) * zoom, 1.0f, 1.0f);
    velocity = position.zw;
}