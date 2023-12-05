#pragma once

#include "ecs/components/rigidBody.h"
#include "scene/game_object.h"
#include "ecs/components.h"
#include "renderer2D/renderer2D_utils.h"
#include "core/input.h"
glm::f32vec2 mutualGravity(game_engine::game_object obj1, game_engine::game_object obj2, float strength);