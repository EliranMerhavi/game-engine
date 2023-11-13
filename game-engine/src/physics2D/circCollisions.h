#pragma once
#include "ecs/components/quad.h"
#include "pch.h"
#include "scene/game_object.h"
#include <limits>
namespace circCollisions {
	bool isColliding(game_engine::game_object& A, game_engine::game_object& B);
	bool linearCollision(game_engine::game_object& A, game_engine::game_object& B, float e);
}

