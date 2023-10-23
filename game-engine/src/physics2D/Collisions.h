#pragma once
#include "rigidBody.h"
namespace collisions {
	//These are all only meant for Squares, maybe rectangles. Needs adaptation, not too much, if we need it to work for arbitrary polygons!
	bool intersectPolygons(rigidBody& A, rigidBody& B);
	void linearCollision(rigidBody& A, rigidBody& B, float restitution);
	void angularCollision(rigidBody& A, rigidBody& B, float restitution);
}