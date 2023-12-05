#include "pch.h"
#include "circCollisions.h"
#include "ecs/components.h"

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
        
        float j = (1 + e) * glm::dot(physB.velocity - physA.velocity, normal) / (1 / physA.mass + 1 / physB.mass);
        physA.velocity = physA.velocity + j / physA.mass * normal;
        physB.velocity = physB.velocity - j / physB.mass * normal;


        if (A.has<component::collider_callback>()) {
            A.get<component::collider_callback>().on_collision(B);
        }
        if (B.has<component::collider_callback>()) {
            B.get<component::collider_callback>().on_collision(A);
        }

        return true;
    }
    bool rotationalCollision(game_engine::game_object& A, game_engine::game_object& B, float e)
    {
        auto& objA = A.get<component::transform>();
        auto& objB = B.get<component::transform>();
        auto& physA = A.get<component::rigidBody>();
        auto& physB = B.get<component::rigidBody>();


        if (physA.staticPos && physB.staticPos) {
            return false;
        }
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

        // Now for the collision itself
        

        if (glm::dot(normal, posA - posB) > 0) {
            if (physA.staticPos) {
                objB.set_position(posB - depth * normal);
            }
            else if (physB.staticPos) {
                objA.set_position(posA + depth * normal);
            }
            else {
                objA.set_position(posA + depth / 2 * normal);
                objB.set_position(posB - depth / 2 * normal);
            }
        }
        else {

            if (physA.staticPos) {
                objB.set_position(posB + depth * normal);
            }
            else if (physB.staticPos) {
                objA.set_position(posA - depth * normal);
            }
            else {
                objA.set_position(posA - depth / 2 * normal);
                objB.set_position(posB + depth / 2 * normal);
            }
        }
        
        float invMA, invMB;
        if (physA.staticPos) {
            invMA = 0;
        }
        else { invMA = 1 / physA.mass; }
        if (physB.staticPos) {
            invMB = 0;
        }
        else { invMB = 1 / physB.mass; }

        // Moments of Inertia
        float IA = physA.mass * 2 * rA /3;
        float IB = physB.mass * 2 * rB/3;
        float invIA, invIB;
        if (physA.staticRot) {
            invIA = 0;
        }
        else { invIA = 1 / IA; }
        if (physB.staticRot) {
            invIB = 0;
        }
        else { invIB = 1 / IB; }

        glm::f32vec2 nearestVertex = (posA * rB + posB * rA)/(rA + rB);


        glm::f32vec2 rAy = nearestVertex - posA;
        glm::f32vec2 rAp = { -rAy.y, rAy.x };
        glm::f32vec2 rBy = nearestVertex - posB;
        glm::f32vec2 rBp = { -rBy.y, rBy.x };


        float rapdn = glm::dot(rAp, normal);
        float rbpdn = glm::dot(rBp, normal);
        // Once we've seperated, we can go about the collision resolution


        glm::f32vec2 angularLinearVelocityA = rAp * physA.omega;
        glm::f32vec2 angularLinearVelocityB = rBp * physB.omega;

        if (glm::dot(physA.velocity + angularLinearVelocityA - physB.velocity - angularLinearVelocityB, normal) > 0) {
            return true;
        }

        float j = -(1 + e) * glm::dot(physA.velocity + angularLinearVelocityA - physB.velocity - angularLinearVelocityB, normal);
        j /= (invMA + invMB + rapdn * rapdn * invIA + rbpdn * rbpdn * invIB);

        glm::f32vec2 impulse = j * normal;

        physA.velocity = physA.velocity + impulse * invMA;
        physB.velocity = physB.velocity - impulse * invMB;

        physA.omega += (rAy.x * impulse.y - rAy.y * impulse.x) * invIA;
        physB.omega -= (rBy.x * impulse.y - rBy.y * impulse.y) * invIB;


        return true;
    }
}

