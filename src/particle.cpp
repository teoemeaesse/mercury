#include "particle.h"
#include "utils.h"


// ----- PARTICLE -----

Particle::Particle(vec3 position, vec3 velocity, float mass) :
    position(position),
    velocity(velocity),
    mass(mass)
{}

vec3 &Particle::get_position() {
    return position;
}

float &Particle::get_mass() {
    return mass;
}



// ----- PARTICLE GROUP -----

ParticleGroup::ParticleGroup(
    PositionInitializer &position_initializer,
    VelocityInitializer &velocity_initializer,
    MassInitializer &mass_initializer,
    vec3 center,
    int num_particles
) {
    std::vector<vec3> &relative_positions = position_initializer.generate(center, num_particles);
    std::vector<vec3> &velocities = velocity_initializer.generate(relative_positions, num_particles);
    std::vector<float> &masses = mass_initializer.generate(relative_positions, num_particles);

    particles.reserve(num_particles);
    for (int i = 0; i < num_particles; i++) {
        particles.emplace_back(
            relative_positions[i] + center,
            velocities[i],
            masses[i]
        );
    }
}



// ----- PARTICLE LAYOUT -----

void ParticleLayout::push_back(ParticleGroup &particle_group) {
    this->particle_groups.push_back(&particle_group);
}



// ----- POSITION INITIALIZERS -----

SquarePositionInitializer::SquarePositionInitializer(float side_length) :
    side_length(side_length)
{}

std::vector<vec3> &SquarePositionInitializer::generate(const vec3 &center, int num_particles) {
    if (relative_positions.size() > 0) {
        log("SquarePositionInitializer::generate() called twice, reusing value", DEBUG_LOG);
        return relative_positions;
    }

    unsigned int particles_per_side = std::round(cbrt(num_particles));
    float step = side_length / particles_per_side;

    relative_positions.reserve(num_particles);
    for (int x = 0; x < particles_per_side; x++) {
        for (int y = 0; y < particles_per_side; y++) {
            for (int z = 0; z < particles_per_side; z++) {
                relative_positions.emplace_back(
                    center.x + x * step - side_length / 2,
                    center.y + y * step - side_length / 2,
                    center.z + z * step - side_length / 2
                );
            }
        }
    }

    return relative_positions;
}



// ----- VELOCITY INITIALIZERS -----

std::vector<vec3> &ZeroVelocityInitializer::generate(const std::vector<vec3> &relative_positions, int num_particles) {
    if (velocities.size() > 0) {
        log("ZeroVelocityInitializer::generate() called twice, reusing value", DEBUG_LOG);
        return velocities;
    }

    velocities.reserve(num_particles);
    for (int i = 0; i < num_particles; i++) {
        velocities.emplace_back(0, 0, 0);
    }

    return velocities;
}



// ----- MASS INITIALIZERS -----

ConstantMassInitializer::ConstantMassInitializer(float mass) :
    mass(mass)
{}

std::vector<float> &ConstantMassInitializer::generate(const std::vector<vec3> &relative_positions, int num_particles) {
    if (masses.size() > 0) {
        log("ConstantMassInitializer::generate() called twice, reusing value", DEBUG_LOG);
        return masses;
    }

    masses.reserve(num_particles);
    for (int i = 0; i < num_particles; i++) {
        masses.push_back(mass);
    }

    return masses;
}