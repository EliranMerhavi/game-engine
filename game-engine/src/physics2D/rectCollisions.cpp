#include "pch.h"
#include "rectCollisions.h"
#include "scene/game_object_t.h"
#include <limits>
#include "scene/components.h"
namespace rectCollisions {
    bool isColliding(game_object_t& A, game_object_t& B)
    {
        auto& objA = A.get<component::transform>();
        auto& objB = B.get<component::transform>();
        //This is some downright retard level reformulation. Why we can't just agree to use radians is beyond me.
        float angleA = objA.rotation() * M_PI / 180;
        float angleB = objB.rotation() * M_PI / 180;
        glm::f32vec2 posA = objA.position();
        glm::f32vec2 posB = objB.position();
        glm::f32vec2 dimA = objA.scale();
        glm::f32vec2 dimB = objB.scale();
        float wA = dimA.x;
        float hA = dimA.y;
        float wB = dimB.x;
        float hB = dimB.y;


        glm::f32vec2 verticesA[4];
        glm::f32vec2 verticesB[4];
        /*
        It's worth explaining how I'm finding the vertices. Each vertex is offset from the centre (the position of the box) by a vector of the form [+-w/2, +-h/2].
        However, once we've rotated the shape at all, this is no longer the case! Instead, we have a rotation matrix, which we multiply by whatever our offset vector should be.
        Then, the vertex is just the position vector plus the appropriate offset vector!

        The Vertices are numbered counterclockwise, the first one being up and to the right of the center (without any rotation. Once we've rotated, all bets are off!)
        */
        float cA = cos(angleA);
        float cB = cos(angleB);
        float sA = sin(angleA);
        float sB = sin(angleB);
        verticesA[0] = { posA.x + wA / 2 * cA - hA / 2 * sA, posA.y + wA / 2 * sA + hA / 2 * cA };
        verticesA[1] = { posA.x - wA / 2 * cA - hA / 2 * sA, posA.y + wA / 2 * sA + hA / 2 * cA };
        verticesA[2] = { posA.x - wA / 2 * cA - hA / 2 * sA, posA.y - wA / 2 * sA + hA / 2 * cA };
        verticesA[3] = { posA.x + wA / 2 * cA - hA / 2 * sA, posA.y - wA / 2 * sA + hA / 2 * cA };
        verticesB[0] = { posB.x + wB / 2 * cB - hB / 2 * sB, posB.y + wB / 2 * sB + hB / 2 * cB };
        verticesB[1] = { posB.x - wB / 2 * cB - hB / 2 * sB, posB.y + wB / 2 * sB + hB / 2 * cB };
        verticesB[2] = { posB.x - wB / 2 * cB - hB / 2 * sB, posB.y - wB / 2 * sB + hB / 2 * cB };
        verticesB[3] = { posB.x + wB / 2 * cB - hB / 2 * sB, posB.y - wB / 2 * sB + hB / 2 * cB };

        //Well, now we actually have the information about what our rectangles are. Great. That took far too long.
        float depth = 0;
        float returnDepth = 100000000000;
        float maxA, minA, maxB, minB;
        glm::f32vec2 normal;

        for (int i = 0; i < 4; i++) {
            minA = 100000000000;
            minB = 100000000000;
            maxA = -100000000000;
            maxB = -100000000000;

            glm::f32vec2 edge = verticesA[i] - verticesA[(i + 1) % 4];
            for (int j = 0; j < 4; j++) {
                float projA = glm::dot(verticesA[j], edge);
                float projB = glm::dot(verticesB[j], edge);
                if (projA > maxA) { maxA = projA; }
                if (projA < minA) { minA = projA; }
                if (projB > maxB) { maxB = projB; }
                if (projB < minB) { minB = projB; }
            }
            depth = std::min(maxB - minA, maxA - minB);
            if (depth <= 0) { return false; }
            if (depth < returnDepth) {
                returnDepth = depth;
                normal = edge;
            }
        }

        for (int i = 0; i < 4; i++) {
            minA = 100000000000;
            minB = 100000000000;
            maxA = -100000000000;
            maxB = -100000000000;

            glm::f32vec2 edge = verticesB[i] - verticesB[(i + 1) % 4];
            for (int j = 0; j < 4; j++) {
                float projA = glm::dot(verticesA[j], edge);
                float projB = glm::dot(verticesB[j], edge);
                if (projA > maxA) { maxA = projA; }
                if (projA < minA) { minA = projA; }
                if (projB > maxB) { maxB = projB; }
                if (projB < minB) { minB = projB; }
            }
            depth = std::min(maxB - minA, maxA - minB);
            if (depth <= 0) { return false; }
            if (depth < returnDepth) {
                returnDepth = depth;
                normal = edge;
            }
        }

        return true;
    }

    bool linearCollision(game_object_t& A, game_object_t& B, float e)
    {
        auto& objA = A.get<component::transform>();
        auto& objB = B.get<component::transform>();
        //This is some downright retard level reformulation. Why we can't just agree to use radians is beyond me.
        float angleA = objA.rotation() * M_PI / 180;
        float angleB = objB.rotation() * M_PI / 180;
        glm::f32vec2 posA = objA.position();
        glm::f32vec2 posB = objB.position();
        glm::f32vec2 dimA = objA.scale();
        glm::f32vec2 dimB = objB.scale();
        float wA = dimA.x;
        float hA = dimA.y;
        float wB = dimB.x;
        float hB = dimB.y;


        glm::f32vec2 verticesA[4];
        glm::f32vec2 verticesB[4];
        /*
        It's worth explaining how I'm finding the vertices. Each vertex is offset from the centre (the position of the box) by a vector of the form [+-w/2, +-h/2].
        However, once we've rotated the shape at all, this is no longer the case! Instead, we have a rotation matrix, which we multiply by whatever our offset vector should be.
        Then, the vertex is just the position vector plus the appropriate offset vector!

        The Vertices are numbered counterclockwise, the first one being up and to the right of the center (without any rotation. Once we've rotated, all bets are off!)
        */
        float cA = cos(angleA);
        float cB = cos(angleB);
        float sA = sin(angleA);
        float sB = sin(angleB);
        verticesA[0] = { posA.x + wA / 2 * cA - hA/2 * sA , posA.y + wA/2 * sA + hA / 2 * cA };
        verticesA[1] = { posA.x - wA / 2 * cA - hA/2 * sA , posA.y - wA/2 * sA + hA / 2 * cA };
        verticesA[2] = { posA.x - wA / 2 * cA + hA/2 * sA , posA.y - wA/2 * sA - hA / 2 * cA };
        verticesA[3] = { posA.x + wA / 2 * cA + hA/2 * sA , posA.y + wA/2 * sA - hA / 2 * cA };
        verticesB[0] = { posB.x + wB / 2 * cB - hB / 2 * sB , posB.y + wB / 2 * sB + hB / 2 * cB };
        verticesB[1] = { posB.x - wB / 2 * cB - hB / 2 * sB , posB.y - wB / 2 * sB + hB / 2 * cB };
        verticesB[2] = { posB.x - wB / 2 * cB + hB / 2 * sB , posB.y - wB / 2 * sB - hB / 2 * cB };
        verticesB[3] = { posB.x + wB / 2 * cB + hB / 2 * sB , posB.y + wB / 2 * sB - hB / 2 * cB };

        //Well, now we actually have the information about what our rectangles are. Great. That took far too long.
        float depth = 0;
        float returnDepth = std::numeric_limits<float>::max();
        float maxA, minA, maxB, minB;
        glm::f32vec2 normal;

        for (int i = 0; i < 4; i++) {
            minA = std::numeric_limits<float>::max();
            minB = std::numeric_limits<float>::max();
            maxA = -std::numeric_limits<float>::max();
            maxB = -std::numeric_limits<float>::max();

            glm::f32vec2 edge = verticesA[i] - verticesA[(i + 1) % 4];
            for (int j = 0; j < 4; j++) {
                float projA = glm::dot(verticesA[j], edge);
                float projB = glm::dot(verticesB[j], edge);
                if (projA > maxA) { maxA = projA; }
                if (projA < minA) { minA = projA; }
                if (projB > maxB) { maxB = projB; }
                if (projB < minB) { minB = projB; }
            }
            depth = std::min(maxB - minA, maxA - minB);
            if (depth <= 0) { return false; }
            if (depth < returnDepth) {
                returnDepth = depth;
                normal = edge;
            }
        }

        for (int i = 0; i < 4; i++) {
            minA = std::numeric_limits<float>::max();
            minB = std::numeric_limits<float>::max();
            maxA = -std::numeric_limits<float>::max();
            maxB = -std::numeric_limits<float>::max();

            glm::f32vec2 edge = verticesB[i] - verticesB[(i + 1) % 4];
            for (int j = 0; j < 4; j++) {
                float projA = glm::dot(verticesA[j], edge);
                float projB = glm::dot(verticesB[j], edge);
                if (projA > maxA) { maxA = projA; }
                if (projA < minA) { minA = projA; }
                if (projB > maxB) { maxB = projB; }
                if (projB < minB) { minB = projB; }
            }
            depth = std::min(maxB - minA, maxA - minB)/glm::length(edge);
            if (depth <= 0) { return false; }
            if (depth < returnDepth) {
                returnDepth = depth;
                normal = edge;
            }
        }
        normal = normal / glm::length(normal);
        // At this point we know there's been a collision, the axis to move on, and the depth of the penetration.
        if (glm::dot(normal, posB - posA) < 0) {
            objA.set_position(posA + returnDepth / 2 * normal);
            objB.set_position(posB - returnDepth / 2 * normal);
        }
        else {
            objA.set_position(posA - returnDepth / 2 * normal);
            objB.set_position(posB + returnDepth / 2 * normal);
        }

        auto& physA = A.get<component::rigidBody>();
        auto& physB = B.get<component::rigidBody>();
        // Once we've seperated, we can go about the collision resolution
        float j = (1 + e) * glm::dot(physB.velocity - physA.velocity, normal) / (1 / physA.mass + 1 / physB.mass);
        physA.velocity = physA.velocity + j / physA.mass * normal;
        physB.velocity = physB.velocity - j / physB.mass * normal;

        return true;
    }

    bool rotationalCollision(game_object_t& A, game_object_t& B, float e)
    {
        auto& objA = A.get<component::transform>();
        auto& objB = B.get<component::transform>();
        //This is some downright retard level reformulation. Why we can't just agree to use radians is beyond me.
        float angleA = objA.rotation() * M_PI / 180;
        float angleB = objB.rotation() * M_PI / 180;
        glm::f32vec2 posA = objA.position();
        glm::f32vec2 posB = objB.position();
        glm::f32vec2 dimA = objA.scale();
        glm::f32vec2 dimB = objB.scale();
        float wA = dimA.x;
        float hA = dimA.y;
        float wB = dimB.x;
        float hB = dimB.y;


        glm::f32vec2 verticesA[4];
        glm::f32vec2 verticesB[4];
        /*
        It's worth explaining how I'm finding the vertices. Each vertex is offset from the centre (the position of the box) by a vector of the form [+-w/2, +-h/2].
        However, once we've rotated the shape at all, this is no longer the case! Instead, we have a rotation matrix, which we multiply by whatever our offset vector should be.
        Then, the vertex is just the position vector plus the appropriate offset vector!

        The Vertices are numbered counterclockwise, the first one being up and to the right of the center (without any rotation. Once we've rotated, all bets are off!)
        */
        float cA = cos(angleA);
        float cB = cos(angleB);
        float sA = sin(angleA);
        float sB = sin(angleB);
        verticesA[0] = { posA.x + wA / 2 * cA - hA / 2 * sA , posA.y + wA / 2 * sA + hA / 2 * cA };
        verticesA[1] = { posA.x - wA / 2 * cA - hA / 2 * sA , posA.y - wA / 2 * sA + hA / 2 * cA };
        verticesA[2] = { posA.x - wA / 2 * cA + hA / 2 * sA , posA.y - wA / 2 * sA - hA / 2 * cA };
        verticesA[3] = { posA.x + wA / 2 * cA + hA / 2 * sA , posA.y + wA / 2 * sA - hA / 2 * cA };
        verticesB[0] = { posB.x + wB / 2 * cB - hB / 2 * sB , posB.y + wB / 2 * sB + hB / 2 * cB };
        verticesB[1] = { posB.x - wB / 2 * cB - hB / 2 * sB , posB.y - wB / 2 * sB + hB / 2 * cB };
        verticesB[2] = { posB.x - wB / 2 * cB + hB / 2 * sB , posB.y - wB / 2 * sB - hB / 2 * cB };
        verticesB[3] = { posB.x + wB / 2 * cB + hB / 2 * sB , posB.y + wB / 2 * sB - hB / 2 * cB };

        //Well, now we actually have the information about what our rectangles are. Great. That took far too long.
        float depth = 0;
        float returnDepth = std::numeric_limits<float>::max();
        float maxA, minA, maxB, minB;
        glm::f32vec2 normal;

        for (int i = 0; i < 4; i++) {
            minA = std::numeric_limits<float>::max();
            minB = std::numeric_limits<float>::max();
            maxA = -std::numeric_limits<float>::max();
            maxB = -std::numeric_limits<float>::max();

            glm::f32vec2 edge = verticesA[i] - verticesA[(i + 1) % 4];
            for (int j = 0; j < 4; j++) {
                float projA = glm::dot(verticesA[j], edge);
                float projB = glm::dot(verticesB[j], edge);
                if (projA > maxA) { maxA = projA; }
                if (projA < minA) { minA = projA; }
                if (projB > maxB) { maxB = projB; }
                if (projB < minB) { minB = projB; }




            }
            depth = std::min(maxB - minA, maxA - minB);
            if (depth <= 0) { return false; }
            if (depth < returnDepth) {
                returnDepth = depth;
                normal = edge;
            }
        }

        for (int i = 0; i < 4; i++) {
            minA = std::numeric_limits<float>::max();
            minB = std::numeric_limits<float>::max();
            maxA = -std::numeric_limits<float>::max();
            maxB = -std::numeric_limits<float>::max();

            glm::f32vec2 edge = verticesB[i] - verticesB[(i + 1) % 4];
            for (int j = 0; j < 4; j++) {
                float projA = glm::dot(verticesA[j], edge);
                float projB = glm::dot(verticesB[j], edge);
                if (projA > maxA) { maxA = projA; }
                if (projA < minA) { minA = projA; }
                if (projB > maxB) { maxB = projB; }
                if (projB < minB) { minB = projB; }
            }
            depth = std::min(maxB - minA, maxA - minB) / glm::length(edge);
            if (depth <= 0) { return false; }
            if (depth < returnDepth) {
                returnDepth = depth;
                normal = edge;
            }
        }
        normal = normal / glm::length(normal);
        // At this point we know there's been a collision, the axis to move on, and the depth of the penetration.
        


        auto& physA = A.get<component::rigidBody>();
        auto& physB = B.get<component::rigidBody>();



        if (glm::dot(normal, posB - posA) < 0) {
            if (physA.staticPos) {
                objB.set_position(posB - 1 * returnDepth * normal);
            }
            else if (physB.staticPos) {
                objA.set_position(posA + 1 * returnDepth  * normal);
            }
            else {
                objA.set_position(posA + returnDepth / 2 * normal);
                objB.set_position(posB - returnDepth / 2 * normal);
            }
        }
        else {
            if (physA.staticPos) {
                objB.set_position(posB + 1 * returnDepth * normal);
            }
            else if (physB.staticPos) {
                objA.set_position(posA - 1 * returnDepth * normal);
            }
            else {
                objA.set_position(posA - returnDepth / 2 * normal);
                objB.set_position(posB + returnDepth / 2 * normal);
            }
        }
         

        float invMA, invMB;
        if (physA.staticPos) {
            if (physB.staticPos) {
                return true;
            }
            invMA = 0;
        }
        else { invMA = 1 / physA.mass; }
        if (physB.staticPos) {
            invMB = 0;
        }
        else { invMB = 1 / physB.mass; }

        // Moments of Inertia
        float IA = physA.mass * (wA * wA + hA * hA) / 12;
        float IB = physB.mass * (wB * wB + hB * hB) / 12;
        float invIA, invIB;
        if (physA.staticRot) {
            invIA = 0;
        }
        else { invIA = 1 / IA; }
        if (physB.staticRot) {
            invIB = 0;
        }
        else { invIB = 1 / IB; }
        // Finding the collision vertex
        glm::f32vec2 nearestVertex = { 0,0 };
   
        float minDist = 10000000;
        float distToPoint = 0;
        for (int i = 0; i < 4; i++) {
            glm::f32vec2 ab = verticesA[i] - verticesA[(i + 1) % 4];
            float ablenSquared = glm::dot(ab, ab);
            for (int j = 0; j < 4; j++) {
                glm::f32vec2 ap = -verticesA[(i+1)%4] + verticesB[j];
                float d = glm::dot(ab, ap)/ablenSquared;
                if (d < 0) {
                    distToPoint = glm::length(verticesA[(i + 1) % 4] - verticesB[j]);
                }
                if (d > 1) {
                    distToPoint = glm::length(verticesA[i] - verticesB[j]);
                }
                else {
                    distToPoint = glm::length(verticesA[(i + 1) % 4] + d * ab - verticesB[j]);
                }
                if (distToPoint < minDist) { nearestVertex = verticesB[j]; minDist = distToPoint; }
            }

            ab = verticesB[i] - verticesB[(i + 1) % 4];
            ablenSquared = glm::dot(ab, ab);
            for (int j = 0; j < 4; j++) {
                glm::f32vec2 ap = -verticesB[(i + 1) % 4] + verticesA[j];
                float d = glm::dot(ab, ap) / ablenSquared;
                if (d < 0) {
                    distToPoint = glm::length(verticesB[(i + 1) % 4] - verticesA[j]);
                }
                if (d > 1) {
                    distToPoint = glm::length(verticesB[i] - verticesA[j]);
                }
                else {
                    distToPoint = glm::length(verticesB[(i + 1) % 4] + d * ab - verticesA[j]);
                }
                if (distToPoint < minDist) { nearestVertex = verticesA[j]; minDist = distToPoint; }
            }

        }



        //std::cout << "nearest Vertex " << nearestVertex.x << "," << nearestVertex.y << "\n";

        // The perpendicular radii
        glm::f32vec2 rA = nearestVertex - posA;
        //std::cout << "rA " << rA.x << "," << rA.y << "\n";
        glm::f32vec2 rAp = { -rA.y, rA.x };
        glm::f32vec2 rB = nearestVertex - posB;
        glm::f32vec2 rBp = { -rB.y, rB.x };
   

        float rapdn = glm::dot(rAp, normal);
        float rbpdn = glm::dot(rBp, normal);
        // Once we've seperated, we can go about the collision resolution
        

        glm::f32vec2 angularLinearVelocityA = rAp * physA.omega;
        glm::f32vec2 angularLinearVelocityB = rBp * physB.omega;
        //std::cout << "normal " << normal.x << ", " << normal.y << "\n";

        float j = -(1 + e) * glm::dot(physA.velocity + angularLinearVelocityA - physB.velocity - angularLinearVelocityB, normal);
        j /= (invMA + invMB + rapdn * rapdn * invIA + rbpdn * rbpdn * invIB);
        //std::cout << j << "\n";
        glm::f32vec2 impulse = j * normal;
        
        physA.velocity = physA.velocity + impulse * invMA;
        physB.velocity = physB.velocity - impulse * invMB;

        physA.omega += (rA.x * impulse.y - rA.y * impulse.x) * invIA;
        physB.omega -= (rB.x * impulse.y - rB.y * impulse.y) * invIB;

        

        return true;
    }
}