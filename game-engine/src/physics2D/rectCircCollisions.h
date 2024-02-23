#pragma once
#include "scene/components/quad.h"
#include "pch.h"
#include "scene/game_object_t.h"
#include <limits>
namespace rectCircCollisions {
	// We'll just assume the first element is a rectangle and the second is a circle. We can add a more general function that just chooses the right case between all the different ones (circ - circ, rect - rect, rect - circ) later. Should be easy.
	bool isColliding(game_object_t& A, game_object_t& B);
	bool linearCollision(game_object_t& A, game_object_t& B, float e);
	bool rotationalCollision(game_object_t& A, game_object_t& B, float e);
}