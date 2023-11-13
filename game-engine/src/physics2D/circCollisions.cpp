#include "pch.h"
#include "circCollisions.h"
namespace circCollisions {
    bool isColliding(game_engine::game_object& A, game_engine::game_object& B)
    {
        auto& objA = A.get<component::transform>();
        auto& objB = B.get<component::transform>();

        float rA = objA.scale().x / 2;
        float rB = objB.scale().x / 2;
        glm::f32vec2 posA = objA.position();
        glm::f32vec2 posB = objB.position();

        glm::f32vec2 normal = posA - posB;
        float lenNormal = glm::length(normal);

        float depth = rA + rB - lenNormal;
        if (depth <= 0) {
            return false;
        }

        normal = normal / lenNormal;
        // At this point we know there's been a collision, the axis to move on, and the depth of the penetration.
        if (glm::dot(normal, posA - posB) > 0) {
            objA.set_position(posA + depth / 2 * normal);
            objB.set_position(posB - depth / 2 * normal);
        }
        else {
            objA.set_position(posA - depth / 2 * normal);
            objB.set_position(posB + depth / 2 * normal);
        }
        return true;
    }

    bool linearCollision(game_engine::game_object& A, game_engine::game_object& B, float e)
    {
        auto& objA = A.get<component::transform>();
        auto& objB = B.get<component::transform>();

        float rA = objA.scale().x / 2;
        float rB = objB.scale().x / 2;
        glm::f32vec2 posA = objA.position();
        glm::f32vec2 posB = objB.position();

        glm::f32vec2 normal = posA - posB;
        float lenNormal = glm::length(normal);

        float depth = rA + rB - lenNormal;
        if (depth <= 0) {
            return false;
        }

        normal = normal / lenNormal;
        // At this point we know there's been a collision, the axis to move on, and the depth of the penetration.
        if (glm::dot(normal, posA - posB) > 0) {
            objA.set_position(posA + depth / 2 * normal);
            objB.set_position(posB - depth / 2 * normal);
        }
        else {
            objA.set_position(posA - depth / 2 * normal);
            objB.set_position(posB + depth / 2 * normal);
        }
        // Now for the collision itself
        auto& physA = A.get<component::rigidBody>();
        auto& physB = B.get<component::rigidBody>();

        float j = (1 + e) * glm::dot(physB.velocity - physA.velocity, normal) / (1 / physA.mass, 1 / physB.mass);
        physA.velocity = physA.velocity + j / physA.mass * normal;
        physB.velocity = physB.velocity - j / physB.mass * normal;
        return true;
    }
}

