#pragma once
#include "scene/components/quad.h"
#include "pch.h"
#include "scene/game_object_t.h"
#include <limits>

namespace circCollisions {
	bool isColliding(game_engine::game_object& A, game_engine::game_object& B);
	bool linearCollision(game_engine::game_object& A, game_engine::game_object& B, float e);
	bool rotationalCollision(game_engine::game_object& A, game_engine::game_object& B, float e);
}

