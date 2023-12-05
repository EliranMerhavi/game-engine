#pragma once
#include "scene/components/quad.h"
#include "pch.h"
#include "scene/game_object_t.h"
#include <limits>

namespace rectCollisions {
	bool isColliding(game_object_t& A, game_object_t& B);
	bool linearCollision(game_object_t& A, game_object_t& B, float e);
}
