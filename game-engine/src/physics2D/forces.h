#pragma once
#include "ecs/components/rigidBody.h"
#include "glm/glm.hpp"

glm::f32vec2 mutualGravity(component::rigidBody A, component::rigidBody B, float strength);