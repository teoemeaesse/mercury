#version 430 core

layout(location = 0) out vec4 color;
layout(location = 1) out vec4 brightness;

in vec2 velocity;

void main() {
    float abs_velocity = sqrt(velocity.x * velocity.x + velocity.y * velocity.y);
    float min_v = 0.0, max_v = 10.0;
    float norm_velocity = (abs_velocity - min_v) / (max_v - min_v);
    color = vec4(norm_velocity * 0.7, 0.3 - norm_velocity, 0.3, 1.0);

    vec3 brightness_bias = vec3(1.5, 1.5, 1.5);
    brightness = vec4(color.rgb * brightness_bias, 1.0);
}