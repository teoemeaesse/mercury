#version 430 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 velocity;
//in vec3 normal;


layout(location = 0) out vec4 o_position;


out vec3 v_position;


uniform vec2 window;
uniform mat4 perspective;
uniform mat4 view;
//uniform mat4 model;


void main() {
    //mat4 modelview = view;// * model;
    //v_normal = transpose(inverse(mat3(modelview))) * normal;
    o_position = perspective * view * vec4(position * 0.05, 1.0);
    v_position = position;
}