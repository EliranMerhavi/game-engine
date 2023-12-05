#include "pch.h"
#include "rectCircCollisions.h"
#include "ecs/components.h"
namespace rectCircCollisions {
	bool isColliding(game_engine::game_object& A, game_engine::game_object& B)
	{
		auto& rect = A.get<component::transform>();
		auto& circ = B.get<component::transform>();

		float r = circ.scale().x/2;
		glm::f32vec2 posCirc = circ.position();

		glm::f32vec2 rectDims = rect.scale();
		glm::f32vec2 posRect = rect.position();
		float w = rectDims.x/2;
		float h = rectDims.y/2;
		float ang = rect.rotation() * M_PI / 180;

		float cA = cos(ang);
		float sA = sin(ang);

		glm::f32vec2 vertices[4];
		vertices[0] = { posRect.x + w / 2 * cA - h / 2 * sA, posRect.y + w / 2 * sA + h / 2 * cA };
		vertices[1] = { posRect.x - w / 2 * cA - h / 2 * sA, posRect.y + w / 2 * sA + h / 2 * cA };
		vertices[2] = { posRect.x - w / 2 * cA - h / 2 * sA, posRect.y - w / 2 * sA + h / 2 * cA };
		vertices[3] = { posRect.x + w / 2 * cA - h / 2 * sA, posRect.y - w / 2 * sA + h / 2 * cA };

		// We use the seperating axis theorem, this time with one additional axis: the one between the center of the circle and the closest vertex.
		// How to we determine what points on the circle need to be projected? We take the center, and add the direction of the seperating axis. Sadly, this means we have to normalise right from the get go.
		float depth = 0;
		float returnDepth = std::numeric_limits<float>::max();
		float maxRect, minRect, maxCirc, minCirc;
		glm::f32vec2 normal;
		
		for (int i = 0; i < 4; i++) {
			minRect = std::numeric_limits<float>::max();
			minCirc = std::numeric_limits<float>::max();
			maxRect = -std::numeric_limits<float>::max();
			maxCirc = -std::numeric_limits<float>::max();

			glm::f32vec2 edge = vertices[i] - vertices[(i + 1) % 4];
			
			edge = edge / glm::length(edge);

			for (int j = 0; j < 4; j++) {
				float projRect = glm::dot(vertices[j], edge);
				if (projRect > maxRect) { maxRect = projRect; }
				if (projRect < minRect) { minRect = projRect; }
			}
			// Possible optimization: we may not need to normalize the edge beforehand! We can just decompose the dot product additavely. May be better? Depends on the speed of the dot product operation.
			float projCirc1 = glm::dot(posCirc + r * edge, edge);
			float projCirc2 = glm::dot(posCirc - r * edge, edge);
			if (projCirc1 > projCirc2) {
				maxCirc = projCirc1;
				minCirc = projCirc2;
			}
			else {
				maxCirc = projCirc2;
				minCirc = projCirc1;
			}

			depth = std::min(maxRect - minCirc, maxCirc - minRect);
			if (depth <= 0) { return 0; }
			if (depth < returnDepth) {
				returnDepth = depth;
				normal = edge;
			}
		}
		// Now the check for the final axis: that between the center of the circle and nearest vertex.
		glm::f32vec2 nearestVertex;
		float dist = std::numeric_limits<float>::max();
		for (int i = 0; i < 4; i++) {
			float d = glm::length(posCirc - vertices[i]);
			if (d < dist) { nearestVertex = vertices[i];  dist = d; }
		}

		glm::f32vec2 edge = nearestVertex - posCirc / dist;
		for (int j = 0; j < 4; j++) {
			float projRect = glm::dot(vertices[j], edge);
			if (projRect > maxRect) { maxRect = projRect; }
			if (projRect < minRect) { minRect = projRect; }
		}

		float projCirc1 = glm::dot(posCirc + r * edge, edge);
		float projCirc2 = glm::dot(posCirc - r * edge, edge);
		if (projCirc1 > projCirc2) {
			maxCirc = projCirc1;
			minCirc = projCirc2;
		}
		else {
			maxCirc = projCirc2;
			minCirc = projCirc1;
		}

		depth = std::min(maxRect - minCirc, maxCirc - minRect);
		if (depth <= 0) { return 0; }
		if (depth < returnDepth) {
			returnDepth = depth;
			normal = edge;
		}
		return true;
	}

	bool linearCollision(game_engine::game_object& A, game_engine::game_object& B, float e)
	{
		auto& rect = A.get<component::transform>();
		auto& circ = B.get<component::transform>();
		auto& physA = A.get<component::rigidBody>();
		auto& physB = B.get<component::rigidBody>();
		float r = circ.scale().x/2;
		glm::f32vec2 posCirc = circ.position();

		glm::f32vec2 rectDims = rect.scale();
		glm::f32vec2 posRect = rect.position();
		float w = rectDims.x;
		float h = rectDims.y;
		float ang = rect.rotation() * M_PI / 180;

		float cA = cos(ang);
		float sA = sin(ang);

		glm::f32vec2 vertices[4];
		vertices[0] = { posRect.x + w / 2 * cA - h / 2 * sA, posRect.y + w / 2 * sA + h / 2 * cA };
		vertices[1] = { posRect.x - w / 2 * cA - h / 2 * sA, posRect.y - w / 2 * sA + h / 2 * cA };
		vertices[2] = { posRect.x - w / 2 * cA + h / 2 * sA, posRect.y - w / 2 * sA - h / 2 * cA };
		vertices[3] = { posRect.x + w / 2 * cA + h / 2 * sA, posRect.y + w / 2 * sA - h / 2 * cA };

		// We use the seperating axis theorem, this time with one additional axis: the one between the center of the circle and the closest vertex.
		// How to we determine what points on the circle need to be projected? We take the center, and add the direction of the seperating axis. Sadly, this means we have to normalise right from the get go.
		float depth = 0;
		float returnDepth = std::numeric_limits<float>::max();
		float maxRect, minRect, maxCirc, minCirc;
		glm::f32vec2 normal;
		
		for (int i = 0; i < 4; i++) {
			minRect = std::numeric_limits<float>::max();
			minCirc = std::numeric_limits<float>::max();
			maxRect = -std::numeric_limits<float>::max();
			maxCirc = -std::numeric_limits<float>::max();

			glm::f32vec2 edge = vertices[i] - vertices[(i + 1) % 4];

			edge = edge / glm::length(edge);

			for (int j = 0; j < 4; j++) {
				float projRect = glm::dot(vertices[j], edge);
				if (projRect > maxRect) { maxRect = projRect; }
				if (projRect < minRect) { minRect = projRect; }
			}
			// Possible optimization: we may not need to normalize the edge beforehand! We can just decompose the dot product additavely. May be better? Depends on the speed of the dot product operation.
			float projCirc1 = glm::dot(posCirc + r * edge, edge);
			float projCirc2 = glm::dot(posCirc - r * edge, edge);
			if (projCirc1 > projCirc2) {
				maxCirc = projCirc1;
				minCirc = projCirc2;
			}
			else {
				maxCirc = projCirc2;
				minCirc = projCirc1;
			}

			depth = std::min(maxRect - minCirc, maxCirc - minRect);
			if (depth <= 0) { return 0; }
			if (depth < returnDepth) {
				returnDepth = depth;
				normal = edge;
			}
		}
		// Now the check for the final axis: that between the center of the circle and nearest vertex.
		minRect = std::numeric_limits<float>::max();
		minCirc = std::numeric_limits<float>::max();
		maxRect = -std::numeric_limits<float>::max();
		maxCirc = -std::numeric_limits<float>::max();
		glm::f32vec2 nearestVertex;
		float dist = std::numeric_limits<float>::max();
		for (int i = 0; i < 4; i++) {
			float d = glm::length(posCirc - vertices[i]);
			if (d < dist) { nearestVertex = vertices[i];  dist = d; }
		}

		glm::f32vec2 edge = (-nearestVertex + posCirc) / dist;
		
		for (int j = 0; j < 4; j++) {
			float projRect = glm::dot(vertices[j], edge);
			if (projRect > maxRect) { maxRect = projRect; }
			if (projRect < minRect) { minRect = projRect; }
		}

		float projCirc1 = glm::dot(posCirc + r * edge, edge);
		float projCirc2 = glm::dot(posCirc - r * edge, edge);
		if (projCirc1 > projCirc2) {
			maxCirc = projCirc1;
			minCirc = projCirc2;
		}
		else {
			maxCirc = projCirc2;
			minCirc = projCirc1;
		}

		depth = std::min(maxRect - minCirc, maxCirc - minRect);
		if (depth <= 0) { return 0; }
		if (depth < returnDepth) {
			returnDepth = depth;
			normal = edge;
		}
		normal = normal / glm::length(normal);
		
		// At this point we know there's been a collision, the axis to move on, and the depth of the penetration.
		if (glm::dot(normal, posRect - posCirc) > 0) {
			if (physA.staticPos) {
				circ.set_position(posCirc - returnDepth * normal);
			}
			else if (physB.staticPos) {
				rect.set_position(posRect + returnDepth * normal);
			}
			else {
				rect.set_position(posRect + returnDepth / 2 * normal);
				circ.set_position(posCirc - returnDepth / 2 * normal);
			}
			
		}
		else {
			if (physA.staticPos) {
				circ.set_position(posCirc + returnDepth * normal);
			}
			else if (physB.staticPos) {
				rect.set_position(posRect - returnDepth * normal);
			}
			else {
				rect.set_position(posRect - returnDepth / 2 * normal);
				circ.set_position(posCirc + returnDepth / 2 * normal);
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

		// Resolve as usual
	
		float j = (1 + e) * glm::dot(physB.velocity - physA.velocity, normal) / (1 / physA.mass + 1 / physB.mass);
		physA.velocity = physA.velocity + j * invMA * normal;
		physB.velocity = physB.velocity - j * invMB * normal;


		return true;
	}

	bool rotationalCollision(game_engine::game_object& A, game_engine::game_object& B, float e)
	{
		auto& rect = A.get<component::transform>();
		auto& circ = B.get<component::transform>();
		auto& physA = A.get<component::rigidBody>();
		auto& physB = B.get<component::rigidBody>();
		float r = circ.scale().x / 2;
		glm::f32vec2 posCirc = circ.position();

		glm::f32vec2 rectDims = rect.scale();
		glm::f32vec2 posRect = rect.position();
		float w = rectDims.x;
		float h = rectDims.y;
		float ang = rect.rotation() * M_PI / 180;

		float cA = cos(ang);
		float sA = sin(ang);

		glm::f32vec2 vertices[4];
		vertices[0] = { posRect.x + w / 2 * cA - h / 2 * sA, posRect.y + w / 2 * sA + h / 2 * cA };
		vertices[1] = { posRect.x - w / 2 * cA - h / 2 * sA, posRect.y - w / 2 * sA + h / 2 * cA };
		vertices[2] = { posRect.x - w / 2 * cA + h / 2 * sA, posRect.y - w / 2 * sA - h / 2 * cA };
		vertices[3] = { posRect.x + w / 2 * cA + h / 2 * sA, posRect.y + w / 2 * sA - h / 2 * cA };

		// We use the seperating axis theorem, this time with one additional axis: the one between the center of the circle and the closest vertex.
		// How to we determine what points on the circle need to be projected? We take the center, and add the direction of the seperating axis. Sadly, this means we have to normalise right from the get go.
		float depth = 0;
		float returnDepth = std::numeric_limits<float>::max();
		float maxRect, minRect, maxCirc, minCirc;
		glm::f32vec2 normal;

		for (int i = 0; i < 4; i++) {
			minRect = std::numeric_limits<float>::max();
			minCirc = std::numeric_limits<float>::max();
			maxRect = -std::numeric_limits<float>::max();
			maxCirc = -std::numeric_limits<float>::max();

			glm::f32vec2 edge = vertices[i] - vertices[(i + 1) % 4];

			edge = edge / glm::length(edge);

			for (int j = 0; j < 4; j++) {
				float projRect = glm::dot(vertices[j], edge);
				if (projRect > maxRect) { maxRect = projRect; }
				if (projRect < minRect) { minRect = projRect; }
			}
			// Possible optimization: we may not need to normalize the edge beforehand! We can just decompose the dot product additavely. May be better? Depends on the speed of the dot product operation.
			float projCirc1 = glm::dot(posCirc + r * edge, edge);
			float projCirc2 = glm::dot(posCirc - r * edge, edge);
			if (projCirc1 > projCirc2) {
				maxCirc = projCirc1;
				minCirc = projCirc2;
			}
			else {
				maxCirc = projCirc2;
				minCirc = projCirc1;
			}

			depth = std::min(maxRect - minCirc, maxCirc - minRect);
			if (depth <= 0) { return 0; }
			if (depth < returnDepth) {
				returnDepth = depth;
				normal = edge;
			}
		}
		// Now the check for the final axis: that between the center of the circle and nearest vertex.
		minRect = std::numeric_limits<float>::max();
		minCirc = std::numeric_limits<float>::max();
		maxRect = -std::numeric_limits<float>::max();
		maxCirc = -std::numeric_limits<float>::max();
		glm::f32vec2 nearestVertex;
		float dist = std::numeric_limits<float>::max();
		for (int i = 0; i < 4; i++) {
			float d = glm::length(posCirc - vertices[i]);
			if (d < dist) { nearestVertex = vertices[i];  dist = d; }
		}

		glm::f32vec2 edge = (-nearestVertex + posCirc) / dist;

		for (int j = 0; j < 4; j++) {
			float projRect = glm::dot(vertices[j], edge);
			if (projRect > maxRect) { maxRect = projRect; }
			if (projRect < minRect) { minRect = projRect; }
		}

		float projCirc1 = glm::dot(posCirc + r * edge, edge);
		float projCirc2 = glm::dot(posCirc - r * edge, edge);
		if (projCirc1 > projCirc2) {
			maxCirc = projCirc1;
			minCirc = projCirc2;
		}
		else {
			maxCirc = projCirc2;
			minCirc = projCirc1;
		}

		depth = std::min(maxRect - minCirc, maxCirc - minRect);
		if (depth <= 0) { return 0; }
		if (depth < returnDepth) {
			returnDepth = depth;
			normal = edge;
		}
		normal = normal / glm::length(normal);

		// At this point we know there's been a collision, the axis to move on, and the depth of the penetration.
		if (glm::dot(normal, posRect - posCirc) > 0) {
			if (physA.staticPos) {
				circ.set_position(posCirc - returnDepth * normal);
			}
			else if (physB.staticPos) {
				rect.set_position(posRect + returnDepth * normal);
			}
			else {
				rect.set_position(posRect + returnDepth / 2 * normal);
				circ.set_position(posCirc - returnDepth / 2 * normal);
			}

		}
		else {
			if (physA.staticPos) {
				circ.set_position(posCirc + returnDepth * normal);
			}
			else if (physB.staticPos) {
				rect.set_position(posRect - returnDepth * normal);
			}
			else {
				rect.set_position(posRect - returnDepth / 2 * normal);
				circ.set_position(posCirc + returnDepth / 2 * normal);
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

		//moments of inertia

		float invIA, invIB;
		if (physB.staticRot) {
			invIB = 0;
		}
		else { invIB = 3 / (2 * physB.mass * r); }
		if (physA.staticRot) {
			invIA = 0;
		}
		else { invIA = 12 / (physA.mass * (w * w + h * h)); }

		//nearest Vertex
		float minDist = 1000000;
		float distToPoint = 0;
		glm::f32vec2 candidatePoint = { 0,0 };
		glm::f32vec2 nearestVertexx = { 0,0 };
		for (int i = 0; i < 4; i++) {
			glm::f32vec2 ab = vertices[i] - vertices[(i + 1) % 4];
			glm::f32vec2 ap = posCirc - vertices[(i + 1) % 4];
			float d = glm::dot(ab, ap) / glm::dot(ab, ab);
			if (d > 1) { candidatePoint = vertices[i];}
			else if (d < 0) { candidatePoint = vertices[(i + 1) % 4]; }
			else { candidatePoint = vertices[(i + 1) % 4] + d * ab; }
			distToPoint = glm::length(candidatePoint - posCirc);
			if (distToPoint < minDist) { minDist = distToPoint; nearestVertexx = candidatePoint; }
		}


		// Resolve as usual

		glm::f32vec2 rA = nearestVertexx - posRect;
		//std::cout << "rA " << rA.x << "," << rA.y << "\n";
		glm::f32vec2 rAp = { -rA.y, rA.x };
		glm::f32vec2 rB = nearestVertexx - posCirc;
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

