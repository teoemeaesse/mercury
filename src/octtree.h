#pragma once

#include <vector>


class Node {
    
};

class Leaf : public Node {

};

class Branch : public Node {

};

class OctTree {
    private:
        std::vector<Node> nodes;
    
    public:
        OctTree();

        // insert a particle into the octtree
        void insert();

        // convert to shader storage buffer object format
        // TODO: void *to_ssbo();
};