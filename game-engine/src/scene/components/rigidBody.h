#pragma once
#include "glm/glm.hpp"
#include "renderer2D/renderer2D.h"
#include "physics2D/collisions.h"

namespace component {
    class rigidBody {
    public:
        float mass;
        float omega;
        glm::f32vec2 velocity;
        glm::f32vec2 acceleration;

        float restitution;
        
        bool static_position;
        bool static_rotation;

        collisions::type collision_type;

        rigidBody(collisions::type collision_type, float mass, float omega, glm::f32vec2 vel, bool static_position, bool static_rotation,
                  float restitution=1);

    };
    
}

