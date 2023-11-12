#include "pch.h"
#include "rigidBody.h"

void component::rigidBody::intialize(float m, float r, float om, glm::f32vec2 vel, std::string type)
{
	this->mass = m;
	this->radius = r;
	this->omega = om;
	this->velocity = vel;
	this->type = type;

	this->acceleration = { 0,0 };
	this->moment = m * r * r;
}

void component::rigidBody::setVelocity(glm::f32vec2 vel)
{
	this->velocity = vel;
}

glm::f32vec2 component::rigidBody::getVelocity()
{
	return this->velocity;
}

float component::rigidBody::getMass()
{
	return this->mass;
}
