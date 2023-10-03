#pragma once

#include "collision_manifold.h"
#include "../primitives/circle.h"
#include "../primitives/collider2D.h"

namespace physics2D
{
	namespace collisions
	{
		collision_manifold find_collision_features(const circle& a, const circle& b);
		collision_manifold find_collision_features(const collider2D& c1, const collider2D& c2);
	}
}
