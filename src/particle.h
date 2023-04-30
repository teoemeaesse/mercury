#pragma once

#include <glm/glm.hpp>
#include <vector>

using glm::vec3;


class PositionInitializer {
    protected:
        std::vector<vec3> relative_positions;

    public:
        // initialize positions
        virtual std::vector<vec3> &generate(const vec3 &center, int num_particles) = 0;
};

class VelocityInitializer {
    protected:
        std::vector<vec3> velocities;

    public:
        // initialize velocity at a given position, relative to the center of the particle group
        virtual std::vector<vec3> &generate(const std::vector<vec3> &relative_positions, int num_particles) = 0;
};

class MassInitializer {
    protected:
        std::vector<float> masses;

    public:
        // initialize mass at a given position, relative to the center of the particle group
        virtual std::vector<float> &generate(const std::vector<vec3> &relative_positions, int num_particles) = 0;
};


class Particle {
    private:
        vec3 position;
        vec3 velocity;
        float mass;
    
    public:
        Particle(vec3 position, vec3 velocity, float mass);

        vec3 &get_position();

        float &get_mass();
};


class ParticleGroup {
    private:
        std::vector<Particle> particles;
        vec3 center;
    
    public:
        ParticleGroup(
            PositionInitializer &position_initializer,
            VelocityInitializer &velocity_initializer,
            MassInitializer &mass_initializer,
            vec3 center,
            int num_particles
        );

        // TODO: void *data();
};


class ParticleLayout {
    private:
        std::vector<ParticleGroup *> particle_groups;
    
    public:
        // add a new group of particles to the layout
        void push_back(ParticleGroup &particle_group);

        // TODO: void *data();
};



// ----- POSITION INITIALIZERS -----

class SquarePositionInitializer : public PositionInitializer {
    private:
        float side_length;
    
    public:
        SquarePositionInitializer(float side_length);
        
        // initialize positions
        std::vector<vec3> &generate(const vec3 &center, int num_particles);
};



// ----- VELOCITY INITIALIZERS -----

class ZeroVelocityInitializer : public VelocityInitializer {
    public:
        // initialize velocity at a given position, relative to the center of the particle group
        std::vector<vec3> &generate(const std::vector<vec3> &relative_positions, int num_particles);
};



// ----- MASS INITIALIZERS -----

class ConstantMassInitializer : public MassInitializer {
    private:
        float mass;
    
    public:
        ConstantMassInitializer(float mass);
        
        // initialize mass at a given position, relative to the center of the particle group
        std::vector<float> &generate(const std::vector<vec3> &relative_positions, int num_particles);
};