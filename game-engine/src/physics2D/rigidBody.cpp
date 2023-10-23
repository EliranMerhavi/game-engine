#include "pch.h"
#include "rigidBody.h"
#include <math.h>

rigidBody::rigidBody(float mass, float angle, float radius, float omega, float restitution, glm::f32vec2 position, glm::f32vec2 velocity, std::string type)
{
    this->mass = mass;
    this->position = position;
    this->velocity = velocity;
    this->omega = omega;
    this->type = type;
    this->angle = angle + 0.7853981634;
    this->radius = radius;
    this->restitution = restitution;
    if (type == "circle") {
        this->moment = 0.25 * 3.14159 * radius * radius * radius * radius;
    }
    else if (type == "square") {
        //radius is distance from center of the square to the vertices, not the side! 
        //TODO: FIX THE MOMENT CALCULTION ACCORDINGLY!
        this->moment = 0.33333 * radius * radius * mass;
        this->vertices[0] = { position.x + radius * cos(angle), position.y + radius * sin(angle) };
        this->vertices[1] = { position.x - radius * sin(angle), position.y + radius * cos(angle) };
        this->vertices[2] = { position.x - radius * cos(angle), position.y - radius * sin(angle) };
        this->vertices[3] = { position.x + radius * sin(angle), position.y - radius * cos(angle) };
    }
    else if (type == "triangle") {
        this->moment = sqrt(3) * 0.09375 * radius * radius * radius * radius;
    }
    else {
        this->moment = 0;
    }
}

void rigidBody::updateRect(float dt)
{
    this->position.x += this->velocity.x * dt;
    this->position.y += this->velocity.y * dt;
    this->angle += this->omega * dt;
    this->vertices[0] = { this->position.x + this->radius * cos(this->angle), this->position.y + this->radius * sin(this->angle) };
    this->vertices[1] = { this->position.x - this->radius * sin(this->angle), this->position.y + this->radius * cos(this->angle) };
    this->vertices[2] = { this->position.x - this->radius * cos(this->angle), this->position.y - this->radius * sin(this->angle) };
    this->vertices[3] = { this->position.x + this->radius * sin(this->angle), this->position.y - this->radius * cos(this->angle) };
}

void rigidBody::printVertices()
{
    std::cout << "Vertex 0:" << this->vertices[0].x << "," << this->vertices[0].y << " \n";
    std::cout << "Vertex 1:" << this->vertices[1].x << "," << this->vertices[1].y << " \n";
    std::cout << "Vertex 2:" << this->vertices[2].x << "," << this->vertices[2].y << " \n";
    std::cout << "Vertex 3:" << this->vertices[3].x << "," << this->vertices[3].y << " \n";
}

void rigidBody::applyForce()
{

}
