#pragma once
#include "glm/glm.hpp"
#include "renderer2D/renderer2D.h"
#include <iostream>

namespace component {
    class rigidBody {
    public:
        float mass;
        float radius;
        float omega;
        glm::f32vec2 velocity;
        glm::f32vec2 acceleration;
        std::string type;
        float moment;

        void intialize(float m, float r, float om,glm::f32vec2 vel, std::string type);
        void setVelocity(glm::f32vec2 vel);
        glm::f32vec2 getVelocity();
        float getMass();
    };
}

