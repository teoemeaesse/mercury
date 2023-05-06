#define GLM_FORCE_SWIZZLE

#include <stdlib.h>
#include <glm/gtc/matrix_transform.hpp>
#include <string>

#include "camera.h"
#include "utils.h"

using namespace glm;

Camera::Camera() : 
    spherical(vec3(0.0f, PI / 2.0f, 1.0f)),
    angular_velocity(1.0f),
    radial_velocity(100.0f) 
{}

// convert spherical coordinates to cartesian coordinates
vec3 Camera::get_cartesian() {
    float theta = this->spherical.x;
    float phi = this->spherical.y;
    float radius = this->spherical.z;

    float x = radius * sin(phi) * sin(theta);
    float y = radius * sin(phi) * cos(theta);
    float z = radius * cos(phi);

    return vec3(x, y, z);
}

// rotate camera around the center - theta horizontal, phi vertical
void Camera::rotate(float delta_theta, float delta_phi, unsigned long frametime) {
    float dt = (float) (frametime / 1000000.0);

    this->spherical.x += this->angular_velocity * delta_theta * dt;
    this->spherical.y += this->angular_velocity * delta_phi * dt;

    // clamp phi to ]0, PI[
    this->spherical.y = clamp(this->spherical.y, 0.001f, PI - 0.001f);
}

// zoom in/out
void Camera::zoom(float scroll, unsigned long frametime) {
    float dt = (float) (frametime / 1000000.0);

    this->spherical.z -= scroll * this->radial_velocity * dt;

    // clamp radius to ]0, inf[
    this->spherical.z = max(0.001f, this->spherical.z);
}

// compute the camera's view matrix
mat4 Camera::view_matrix() {
    return lookAt(
        this->get_cartesian(),  // camera position
        vec3(0.0f, 0.0f, 0.0f), // look at origin
        vec3(0.0f, 0.0f, 1.0f)  // up vector
    );
}

// compute the camera's perspective matrix
mat4 Camera::perspective_matrix(int target_width, int target_height) {
    return glm::perspective(
        glm::radians(45.0f),                  // fov
        (float) target_width / target_height, // aspect ratio
        0.1f,                                 // near plane
        100.0f                                // far plane
    );
}

// update camera state based on keyboard and mouse input
void Camera::update(Keyboard &keyboard, Mouse &mouse, unsigned long frametime) {
    // mouse rotate camera
    this->rotate(mouse.consume_x_acc(), mouse.consume_y_acc(), frametime);

    // keyboard rotate camera
    this->rotate(keyboard.d_down - keyboard.a_down, keyboard.s_down - keyboard.w_down, frametime);

    // zoom in/out
    this->zoom(mouse.consume_scroll_acc(), frametime);
}