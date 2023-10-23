#pragma once
#include "rigidBody.h"
#include "glm/glm.hpp"

glm::f32vec2 mutualGravity(rigidBody A, rigidBody B, float strength);