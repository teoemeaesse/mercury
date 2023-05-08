#pragma once

#include <glm/glm.hpp>

using glm::vec3;


struct SerialParticle {
    vec3 position;
    vec3 velocity;
    float mass;
};

struct SerialNode {
    unsigned int children[8];  // index of children, 0 if no child
    unsigned int particles_index; // index of first particle in this node
    unsigned int particles_count; // number of particles in this node

    vec3 total_position;
    float total_mass, side_length;
};


