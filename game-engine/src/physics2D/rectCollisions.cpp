#include "pch.h"
#include "rectCollisions.h"
#include "scene/game_object.h"
#include <limits>
bool isColliding(game_engine::game_object& A, game_engine::game_object& B)
{
    auto& objA = A.get<component::transform>();
    auto& objB = B.get<component::transform>();
    //This is some downright retard level reformulation. Why we can't just agree to use radians is beyond me.
    float angleA = objA.rotation() * M_PI/180;
    float angleB = objB.rotation() * M_PI/180;
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
        depth = std::min(maxB - minA, maxA - minB);
        if (depth <= 0) { return false; }
        if (depth < returnDepth) {
            returnDepth = depth;
            normal = edge;
        }
    }

    // At this point we know there's been a collision, the axis to move on, and the depth of the penetration.
    if (glm::dot(normal, posA - posB) > 0) {
        objA.set_position(posA + returnDepth / 2 * normal);
        objB.set_position(posB - returnDepth / 2 * normal);
    }
    else {
        objA.set_position(posA - returnDepth / 2 * normal);
        objB.set_position(posB + returnDepth / 2 * normal);
    }

    return true;
}

