#pragma once

#include <glm/glm.hpp>

#include "io.h"

using glm::vec3;
using glm::mat4;

#define PI 3.1415927f

class Camera {
    private:
        vec3 spherical;                             // <theta, phi, radius>
        float fov,
              angular_velocity, 
              radial_velocity;                      // camera settings

        // convert spherical coordinates to cartesian coordinates
        vec3 get_cartesian();
        
        // rotate camera around the center - theta horizontal, phi vertical
        void rotate(float delta_theta, float delta_phi, unsigned long frametime);

        // zoom in/out
        void zoom(float scroll, unsigned long frametime);

    public:        
        Camera();

        // compute the camera's view matrix
        mat4 view_matrix();

        // compute the camera's perspective matrix
        mat4 perspective_matrix(int target_width, int target_height);

        // update camera state based on keyboard and mouse input
        void update(Keyboard &keyboard, Mouse &mouse, unsigned long frametime);
};