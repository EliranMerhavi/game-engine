#include "pch.h"
#include "rigidBody.h"

component::rigidBody::rigidBody(float m, float om, glm::f32vec2 vel)
	: mass(m), omega(om), velocity(vel), restitution(1), acceleration({0, 0}), moment(m), staticPos(0), staticRot(0)
{
}
