#pragma once

#include "particle.h"
#include "config.h"


class Simulator {
    private:

    public:
        Simulator(ParticleLayout & initial_state, Configuration & config);
        ~Simulator();

        // calculate the next frame
        void step();
};