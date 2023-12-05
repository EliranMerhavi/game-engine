#pragma once

#include "scene/components/rigidBody.h"
#include "scene/game_object_t.h"
#include "scene/components.h"

#include "core/input.h"

glm::f32vec2 mutualGravity(game_object_t obj1, game_object_t obj2, float strength);