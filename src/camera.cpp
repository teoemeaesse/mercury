#define GLM_FORCE_SWIZZLE

#include <stdlib.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>

#include "camera.h"
#include "utils.h"

using namespace glm;

Camera::Camera() {
    this->spherical = vec3(0.0f, PI / 2.0f, 1.0f);
    this->angular_velocity = 50.0f;
    this->radial_velocity = 500.0f;
}

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

// compute the camera's view matrix
mat4 Camera::view_matrix() {
    return lookAt(
        this->get_cartesian(),  // camera position
        vec3(0.0f, 0.0f, 0.0f), // look at origin
        vec3(0.0f, 0.0f, 1.0f)  // up vector
    );
}

// rotate camera around the center - theta horizontal, phi vertical
void Camera::rotate(float delta_theta, float delta_phi, double frame_time) {
    float dt = (float) (frame_time / 1000000000.0);

    this->spherical.x += this->angular_velocity * delta_theta * dt;
    this->spherical.y += this->angular_velocity * delta_phi * dt;

    // clamp phi to ]0, PI[
    this->spherical.y = clamp(this->spherical.y, 0.001f, PI - 0.001f);
}

// zoom in/out
void Camera::zoom(Direction direction, unsigned long frametime) {
    float dt = (float) (frametime / 1000000.0);

    if (direction == IN) {
        this->spherical.z -= this->radial_velocity * dt;
    } else {
        this->spherical.z += this->radial_velocity * dt;
    }

    // clamp radius to ]0, inf[
    this->spherical.z = max(0.001f, this->spherical.z);
}