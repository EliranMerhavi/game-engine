#include "pch.h"
#include "rigidBody.h"

void component::rigidBody::intialize(float m, float om, glm::f32vec2 vel, std::string type)
{
	this->mass = m;
	this->omega = om;
	this->velocity = vel;
	this->type = type;

	this->acceleration = { 0,0 };
	this->moment = m;
}
