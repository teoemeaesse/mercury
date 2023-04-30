#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>

#include "particle.h"

using namespace glm;


struct Bounds {
    vec3 min;
    vec3 max;
};

struct Node {
    Node **children;
    Particle *particle;
    Bounds bounds;

    vec3 total_position;
    float total_mass;

    std::string to_string(int depth = 0) const {
        std::string indent(depth * 2, ' ');
        std::stringstream ss;
        ss << indent << "Bounds: [" << bounds.min.x << ", " << bounds.min.y << ", " << bounds.min.z << "] - [";
        ss << bounds.max.x << ", " << bounds.max.y << ", " << bounds.max.z << "]\n";
        ss << indent << "Total position: [" << total_position.x << ", " << total_position.y << ", " << total_position.z << "]\n";
        ss << indent << "Total mass: " << total_mass << "\n";
        
        return ss.str();
    }
};

class OctTree {
    private:
        Node *root;
    
    public:
        OctTree(Bounds bounds);

        ~OctTree();

        // insert a particle into the octtree
        void insert(Particle *particle);

        // convert to shader storage buffer object format
        // TODO: void *to_ssbo();
        std::string to_string() const {
            if (root) {
                return root->to_string(2);
            } else {
                return "Empty OctTree";
            }
        }

};