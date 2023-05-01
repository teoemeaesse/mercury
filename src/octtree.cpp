#include "octtree.h"


// ----- NODE ------

// creates a new node
Node *create_node(Bounds bounds) {
    Node *node = new Node();

    node->children = nullptr;
    node->particles = nullptr;
    node->bounds = bounds;
    node->total_position = vec3(0.0, 0.0, 0.0);
    node->total_mass = 0.0;

    return node;
}

// deletes a node and all of its children
void delete_node(Node *node) {
    if (node == nullptr)
        return;

    if (node->children) {
        for (int i = 0; i < 8; i++)
            delete_node(node->children[i]);
        delete[] node->children;
    }

    if (node->particles)
        delete node->particles;
    // TODO: delete particles?

    delete node;
}

// gets the octant of a position within a given bounds
unsigned int get_octant(Bounds &parent_bounds, vec3 &position) {
    float mid_x = (parent_bounds.min.x + parent_bounds.max.x) / 2.0;
    float mid_y = (parent_bounds.min.y + parent_bounds.max.y) / 2.0;
    float mid_z = (parent_bounds.min.z + parent_bounds.max.z) / 2.0;

    unsigned int octant = 0;
    if (position.x >= mid_x)
        octant += 1;
    if (position.y >= mid_y)
        octant += 2;
    if (position.z >= mid_z)
        octant += 4;
    return octant;
}

// creates a child of a node at an octant (0-7)
Node *create_child(Bounds &parent_bounds, unsigned int octant) {
    if (octant < 0 || octant > 7)
        return nullptr;

    vec3 min = parent_bounds.min;
    vec3 max = parent_bounds.max;

    float mid_x = (min.x + max.x) / 2.0;
    float mid_y = (min.y + max.y) / 2.0;
    float mid_z = (min.z + max.z) / 2.0;

    switch (octant) {
        case 0:
            return create_node({vec3(min.x, min.y, min.z), vec3(mid_x, mid_y, mid_z)});
        case 1:
            return create_node({vec3(mid_x, min.y, min.z), vec3(max.x, mid_y, mid_z)});
        case 2:
            return create_node({vec3(min.x, mid_y, min.z), vec3(mid_x, max.y, mid_z)});
        case 3:
            return create_node({vec3(mid_x, mid_y, min.z), vec3(max.x, max.y, mid_z)});
        case 4:
            return create_node({vec3(min.x, min.y, mid_z), vec3(mid_x, mid_y, max.z)});
        case 5:
            return create_node({vec3(mid_x, min.y, mid_z), vec3(max.x, mid_y, max.z)});
        case 6:
            return create_node({vec3(min.x, mid_y, mid_z), vec3(mid_x, max.y, max.z)});
        case 7:
            return create_node({vec3(mid_x, mid_y, mid_z), vec3(max.x, max.y, max.z)});
    }

    return nullptr;
}

// recursively insert a particle into a node
void insert_node(Node *node, Particle *particle, unsigned int depth, unsigned int max_depth) {
    if (node == nullptr)
        return;

    // update the total position and mass of the node
    node->total_position += particle->get_position() * particle->get_mass();
    node->total_mass += particle->get_mass();

    // node is a branch, recursively insert
    if (node->children) {
        unsigned int octant = get_octant(node->bounds, particle->get_position());
        insert_node(node->children[octant], particle, depth + 1, max_depth);
        return;
    }

    // node is an empty leaf, insert particle
    if (node->particles == nullptr) {
        node->particles = new std::vector<Particle *>();
        node->particles->push_back(particle);
        return;
    }

    // node is a leaf with a particle

    // node is at max depth, insert particle
    if (depth >= max_depth) {
        node->particles->push_back(particle);
        return;
    }

    // create children and insert both particles
    node->children = new Node *[8];
    for (int i = 0; i < 8; i++)
        node->children[i] = create_child(node->bounds, i);

    unsigned int old_octant = get_octant(node->bounds, (*node->particles)[0]->get_position());
    unsigned int new_octant = get_octant(node->bounds, particle->get_position());

    // TODO: can merge particles here, just check if they overlap

    insert_node(node->children[old_octant], (*node->particles)[0], depth + 1, max_depth);
    insert_node(node->children[new_octant], particle, depth + 1, max_depth);

    delete node->particles;
    node->particles = nullptr;
}



// ----- OCT TREE ----- //



OctTree::OctTree(Bounds bounds, unsigned int max_depth) {
    this->root = create_node(bounds);
    this->max_depth = max_depth;
}

OctTree::~OctTree() {
    delete_node(root);
}

// insert a particle into the octtree
void OctTree::insert(Particle *particle) {
    insert_node(root, particle, 0, max_depth);
}