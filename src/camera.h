#pragma once

#include <glm/glm.hpp>

using glm::vec3;
using glm::mat4;

#define PI 3.1415927f


class Camera {
    private:
        vec3 spherical;                             // <theta, phi, radius>
        float angular_velocity, radial_velocity;    // camera settings

        // convert spherical coordinates to cartesian coordinates
        vec3 get_cartesian();
    public:
        enum Direction {
            IN,
            OUT
        };
        
        Camera();

        // compute the camera's view matrix
        mat4 view_matrix();

        // rotate camera around the center - theta horizontal, phi vertical
        void rotate(float delta_theta, float delta_phi, double frametime);

        // zoom in/out
        void zoom(Direction direction, unsigned long frametime);
};