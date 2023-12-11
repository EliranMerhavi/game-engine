#pragma once
#include "glm/glm.hpp"
#include "renderer2D/renderer2D.h"
#include <iostream>

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

        rigidBody(float mass, float omega, glm::f32vec2 vel, bool static_position, bool static_rotation, 
                  float restitution=1);

    };
    
}

