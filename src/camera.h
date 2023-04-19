#pragma once

#include <glm/glm.hpp>

using glm::vec3;
using glm::mat4;

#define PI 3.1415927f

enum Direction {
    IN,
    OUT
};

class Camera {
    private:
        vec3 spherical;                             // <theta, phi, radius>
        float angular_velocity, radial_velocity;    // camera settings

        // convert spherical coordinates to cartesian coordinates
        vec3 get_cartesian();
    public:
        Camera();

        // compute the camera's view matrix
        mat4 view_matrix();

        // rotate camera around the center - theta horizontal, phi vertical
        void rotate(float delta_theta, float delta_phi, double frame_time);

        // zoom in/out
        void zoom(Direction direction , double frame_time);
};