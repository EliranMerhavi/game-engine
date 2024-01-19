#include "pch.h"
#include "Collisions.h"
#include <algorithm>

bool collisions::intersectPolygons(rigidBody& A, rigidBody& B) {
	float maxB = -1000000;
	float minB = 1000000;
	float maxA = -1000000;
	float minA = 1000000;
	float depth = 0;
	float returnDepth = 100000000;
	glm::f32vec2 normal;
	//loop over the vertices of the first shape to get the edges of it
	for (int i = 0; i < 4; i++) {
		minA = 10000000;
		minB = 10000000;
		maxA = -10000000;
		maxB = -10000000;
		glm::f32vec2 edge = (-A.vertices[(i + 1) % 4] + A.vertices[i]) / glm::length(-A.vertices[(i + 1) % 4] + A.vertices[i]);
		for (int j = 0; j < 4; j++) {
			float projA = A.vertices[j].x * edge[0] + A.vertices[j].y * edge[1];
			float projB = B.vertices[j].x * edge[0] + B.vertices[j].y * edge[1];
			if (projA > maxA) { maxA = projA; }
			if (projA < minA) { minA = projA; }
			if (projB > maxB) { maxB = projB; }
			if (projB < minB) { minB = projB; }
		}
		/*
		We figure out the axis with least penetration. If said lest penetration is negative, we found a seperating axis, and there's no collision.
		Otherwise, we check to see if this is the least penetration so far. If so, this is the new direction in which we say the collision has taken place.
		*/
		depth = std::min(maxB - minA, maxA - minB);
		if (depth <= 0) { return 0; }
		if (depth < returnDepth) {
			returnDepth = depth;
			normal.x = edge.x;
			normal.y = edge.y;
		}
	}
	for (int i = 0; i < 4; i++) {
		minA = 10000000;
		minB = 10000000;
		maxA = -10000000;
		maxB = -10000000;
		glm::f32vec2 edge = (-B.vertices[(i + 1) % 4] + B.vertices[i]) / glm::length(-B.vertices[(i + 1) % 4] + B.vertices[i]);
		for (int j = 0; j < 4; j++) {
			float projA = A.vertices[j].x * edge.x + A.vertices[j].y * edge.y;
			float projB = B.vertices[j].x * edge.x + B.vertices[j].y * edge.y;
			if (projA > maxA) { maxA = projA; }
			if (projA < minA) { minA = projA; }
			if (projB > maxB) { maxB = projB; }
			if (projB < minB) { minB = projB; }
		}
		depth = std::min(maxB - minA, maxA - minB);
		if (depth <= 0) { return 0; }
		if (depth < returnDepth) {
			returnDepth = depth;
			normal.x = edge.x;
			normal.y = edge.y;
		}
	}
	//If we're at this point, it means we indeed have an intersection, with the normal vector we've found
	//we push out the bodies along this axis before doing anything else
	//we need to determine which body is the one that needs to be pushed.

	if (glm::dot(normal, A.position - B.position) > 0) {
		A.position.x += normal.x * returnDepth/2;
		A.position.y += normal.y * returnDepth/2;
		B.position.x -= normal.x * returnDepth/2;
		B.position.y -= normal.y * returnDepth/2;
	}
	else {
		A.position.x -= normal.x * returnDepth/2;
		A.position.y -= normal.y * returnDepth/2;
		B.position.x += normal.x * returnDepth/2;
		B.position.y += normal.y * returnDepth/2;
	}


	return 1;
}

void collisions::linearCollision(rigidBody& A, rigidBody& B, float restitution)
{
	float maxB = -1000000;
	float minB = 1000000;
	float maxA = -1000000;
	float minA = 1000000;
	float depth = 0;
	float returnDepth = 100000000;
	glm::f32vec2 normal;
	//loop over the vertices of the first shape to get the edges of it
	for (int i = 0; i < 4; i++) {
		minA = 10000000;
		minB = 10000000;
		maxA = -10000000;
		maxB = -10000000;
		glm::f32vec2 edge = (-A.vertices[(i + 1) % 4] + A.vertices[i]) / glm::length(-A.vertices[(i + 1) % 4] + A.vertices[i]);
		for (int j = 0; j < 4; j++) {
			float projA = A.vertices[j].x * edge[0] + A.vertices[j].y * edge[1];
			float projB = B.vertices[j].x * edge[0] + B.vertices[j].y * edge[1];
			if (projA > maxA) { maxA = projA; }
			if (projA < minA) { minA = projA; }
			if (projB > maxB) { maxB = projB; }
			if (projB < minB) { minB = projB; }

		}
		/*
		We figure out the axis with least penetration. If said lest penetration is negative, we found a seperating axis, and there's no collision.
		Otherwise, we check to see if this is the least penetration so far. If so, this is the new direction in which we say the collision has taken place.
		*/
		depth = std::min(maxB - minA, maxA - minB);
		if (depth <= 0) { return; }
		if (depth < returnDepth) {
			returnDepth = depth;
			normal.x = edge.x;
			normal.y = edge.y;
		}
	}
	//now the second shape
	for (int i = 0; i < 4; i++) {
		minA = 10000000;
		minB = 10000000;
		maxA = -10000000;
		maxB = -10000000;
		glm::f32vec2 edge = (-B.vertices[(i + 1) % 4] + B.vertices[i]) / glm::length(-B.vertices[(i + 1) % 4] + B.vertices[i]);
		for (int j = 0; j < 4; j++) {
			float projA = A.vertices[j].x * edge.x + A.vertices[j].y * edge.y;
			float projB = B.vertices[j].x * edge.x + B.vertices[j].y * edge.y;
			if (projA > maxA) { maxA = projA; }
			if (projA < minA) { minA = projA; }
			if (projB > maxB) { maxB = projB; }
			if (projB < minB) { minB = projB; }
		}
		depth = std::min(maxB - minA, maxA - minB);
		if (depth <= 0) { return; }
		if (depth < returnDepth) {
			returnDepth = depth;
			normal.x = edge.x;
			normal.y = edge.y;
		}
	}
	//If we're at this point, it means we indeed have an intersection, with the normal vector we've found
	//we push out the bodies along this axis before doing anything else
	//we need to determine which body is the one that needs to be pushed.

	if (glm::dot(normal, A.position - B.position) > 0) {
		A.position.x += normal.x * returnDepth / 2;
		A.position.y += normal.y * returnDepth / 2;
		B.position.x -= normal.x * returnDepth / 2;
		B.position.y -= normal.y * returnDepth / 2;
	}
	else {
		A.position.x -= normal.x * returnDepth / 2;
		A.position.y -= normal.y * returnDepth / 2;
		B.position.x += normal.x * returnDepth / 2;
		B.position.y += normal.y * returnDepth / 2;
	}

	//Calculate the actual collisions. This is shockingly easy!
	float j = (1 + restitution) * glm::dot((-A.velocity + B.velocity), normal)/(1/A.mass + 1/B.mass);
	A.velocity = A.velocity + j / A.mass * normal;
	B.velocity = B.velocity - j / B.mass * normal;
}

void collisions::angularCollision(rigidBody& A, rigidBody& B, float restitution)
{
	float maxB = -1000000;
	float minB = 1000000;
	float maxA = -1000000;
	float minA = 1000000;
	float depth = 0;
	float depthA = 0;
	float depthB = 0;
	float returnDepth = 100000000;
	glm::f32vec2 normal;
	/*
	The idea for finding the intersection point is thus:
	1. Determine the minimal axis, and which polygon it's from.
	2. The point is then taken from the second polygon, it's the one closest to the first one's center!
	THIS DOES NOT WORK AS INTENDED! THINK OF A BETTER WAY! THIS IS THE LAST THING LEFT AS FAR AS I CAN TELL!!!!
	*/
	glm::f32vec2 intersectionPoint;
	//loop over the vertices of the first shape to get the edges of it
	for (int i = 0; i < 4; i++) {
		minA = 10000000;
		minB = 10000000;
		maxA = -10000000;
		maxB = -10000000;
		glm::f32vec2 edge = (-A.vertices[(i + 1) % 4] + A.vertices[i]) / glm::length(-A.vertices[(i + 1) % 4] + A.vertices[i]);
		for (int j = 0; j < 4; j++) {
			float projA = A.vertices[j].x * edge[0] + A.vertices[j].y * edge[1];
			float projB = B.vertices[j].x * edge[0] + B.vertices[j].y * edge[1];
			if (projA > maxA) { maxA = projA;}
			if (projA < minA) { minA = projA; }
			if (projB > maxB) { maxB = projB; }
			if (projB < minB) { minB = projB; }

		}
		/*
		We figure out the axis with least penetration. If said lest penetration is negative, we found a seperating axis, and there's no collision.
		Otherwise, we check to see if this is the least penetration so far. If so, this is the new direction in which we say the collision has taken place.
		*/
		depthA = std::min(maxB - minA, maxA - minB);
		if (depthA <= 0) { return; }
		if (depthA < returnDepth) {
			returnDepth = depthA;
			normal.x = edge.x;
			normal.y = edge.y;
		}
	}
	//now the second shape
	for (int i = 0; i < 4; i++) {
		minA = 10000000;
		minB = 10000000;
		maxA = -10000000;
		maxB = -10000000;
		glm::f32vec2 edge = (-B.vertices[(i + 1) % 4] + B.vertices[i]) / glm::length(-B.vertices[(i + 1) % 4] + B.vertices[i]);
		for (int j = 0; j < 4; j++) {
			float projA = A.vertices[j].x * edge.x + A.vertices[j].y * edge.y;
			float projB = B.vertices[j].x * edge.x + B.vertices[j].y * edge.y;
			if (projA > maxA) { maxA = projA; }
			if (projA < minA) { minA = projA; }
			if (projB > maxB) { maxB = projB; }
			if (projB < minB) { minB = projB; }
		}
		depthB = std::min(maxB - minA, maxA - minB);
		if (depthB <= 0) { return; }
		if (depthB < returnDepth) {
			returnDepth = depthB;
			normal.x = edge.x;
			normal.y = edge.y;
		}
	}

	//If we're at this point, it means we indeed have an intersection, with the normal vector we've found
	//we push out the bodies along this axis before doing anything else
	//we need to determine which body is the one that needs to be pushed.

	if (glm::dot(normal, A.position - B.position) > 0) {
		A.position.x += normal.x * returnDepth / 2;
		A.position.y += normal.y * returnDepth / 2;
		B.position.x -= normal.x * returnDepth / 2;
		B.position.y -= normal.y * returnDepth / 2;
	}
	else {
		A.position.x -= normal.x * returnDepth / 2;
		A.position.y -= normal.y * returnDepth / 2;
		B.position.x += normal.x * returnDepth / 2;
		B.position.y += normal.y * returnDepth / 2;
	}

	//Calculate the actual collisions. This is shockingly easy!
	// TODO: Finding the collision point needs to be done somewhat better.
	intersectionPoint = (A.position + B.position);
	intersectionPoint.x /= 2;
	intersectionPoint.y /= 2;
	glm::f32vec2 sn(-normal.y, normal.x);
	float rAP = glm::dot(intersectionPoint - A.position, sn);
	float rBP = glm::dot(intersectionPoint - B.position, -sn);
	float j = (1 + restitution) * glm::dot((-A.velocity + B.velocity), normal) / (1 / A.mass + 1 / B.mass + rAP * rAP/A.moment + rBP*rBP/B.moment);
	A.velocity = A.velocity + j / A.mass * normal;
	B.velocity = B.velocity - j / B.mass * normal;
	
	A.omega = A.omega + rAP * j / A.moment;
	B.omega = B.omega + rBP * j / B.moment;
	
}


