#include "pch.h"
#include "rigidBody.h"

void component::rigidBody::intialize(float m, float om, glm::f32vec2 vel)
{
	this->mass = m;
	this->omega = om;
	this->velocity = vel;
	this->restitution = 1;
	this->acceleration = { 0,0 };
	this->moment = m;

	this->staticPos = 0;
	this->staticRot = 0;
	
}


