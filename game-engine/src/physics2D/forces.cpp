#include "pch.h"
#include "forces.h"

glm::f32vec2 mutualGravity(rigidBody A, rigidBody B, float strength)
{
	float r = glm::length(A.position - B.position);
	float Force_strength = -strength * A.mass * B.mass / (r * r);
	return Force_strength * (B.position - A.position);
}
