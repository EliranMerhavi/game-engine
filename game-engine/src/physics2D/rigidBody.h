#pragma once
#include "glm/glm.hpp"
#include "renderer2D/renderer2D_utils.h"
#include <iostream>


class rigidBody {
public:
    float mass;
    float angle;
    float radius;
    float restitution;
    float omega;
    glm::f32vec2 position;
    glm::f32vec2 velocity;
    std::string type;
    float moment;
    glm::f32vec2 vertices[4];
    float acceleration;

    rigidBody(float mass, float angle, float radius, float omega, float restitution, glm::f32vec2 position, glm::f32vec2 velocity, std::string type);
    void updateRect(float dt);
    void printVertices();
    void applyForce();
    
};
