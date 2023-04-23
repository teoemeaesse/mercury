#pragma once

#include <glm/glm.hpp>

using glm::vec3;


class MassInitializer {
    public:
        // intialize mass at a given position
        virtual float get_mass(vec3 position) = 0;
};

class PositionInitializer {
    public:
        virtual vec3 get_position() = 0;
};

class VelocityInitializer {
    public:
        virtual vec3 get_velocity() = 0;
};

class Particle {
    private:
        vec3 position;
        vec3 velocity;
        float mass;
    
    public:
        Particle(ParticleInitializer &initializer);
        Particle(
            PositionInitializer &position_initializer,
            VelocityInitializer &velocity_initializer,
            MassInitializer &mass_initializer
        );
};



// ----- PARTICLE INITIALIZERS -----



// ----- POSITION INITIALIZERS -----

class SquarePositionInitializer : public PositionInitializer {
    private:
        float side_length;
    
    public:
        SquarePositionInitializer(float side_length);
        vec3 get_position();
};



// ----- VELOCITY INITIALIZERS -----

class ZeroVelocityInitializer : public VelocityInitializer {
    public:
        vec3 get_velocity();
};



// ----- MASS INITIALIZERS -----

class ConstantMassInitializer : public MassInitializer {
    private:
        float mass;
    
    public:
        ConstantMassInitializer(float mass);
        float get_mass(vec3 position);
};