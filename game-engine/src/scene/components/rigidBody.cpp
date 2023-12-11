#include "pch.h"
#include "rigidBody.h"


component::rigidBody::rigidBody(float mass, float omega, glm::f32vec2 vel, bool static_position, bool static_rotation, float restitution)
	: mass(mass), omega(omega), velocity(vel), restitution(restitution), acceleration({ 0, 0 }), static_position(static_position), static_rotation(static_rotation)
{
}
