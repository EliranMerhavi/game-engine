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

        float moment;
        float restitution;
        
        bool staticPos;
        bool staticRot;

        rigidBody(float m, float om, glm::f32vec2 vel);
    };
    
}

