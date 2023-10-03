#pragma once

#include "renderer2D/line2D.h"
#include "../primitives/circle.h"
#include "../primitives/AABB.h"
#include "../primitives/box2D.h"
#include "../primitives/ray2D.h"
#include "../primitives/raycast_result.h"

namespace physics2D
{
	namespace intersection_detector
	{
		using namespace renderer2D;
		/* point vs primitive tests */
		bool point_on_line(const glm::f32vec2& point, const line2D& line);
		bool point_in_circle(const glm::f32vec2& point, const circle& _circle);
		bool point_in_AABB(const glm::f32vec2& point, const AABB& aabb);
		bool point_in_box2D(const glm::f32vec2& point, const box2D& box);
		/* line vs primitive tests */
		bool line_and_circle(const line2D& line, const circle& _circle);
		bool line_and_AABB(const line2D& line, const AABB& aabb);
		bool line_and_box2D(const line2D& line, const box2D& box);
		/* ray vs primitive tests */
		bool raycast(const circle& _circle, const ray2D& ray, std::optional<raycast_result>& res);
		/* circle vs primitive tests */
		inline bool circle_and_line(const circle& _circle, const line2D& line) { return line_and_circle(line, _circle); }
		bool circle_and_circle(const circle& c1, const circle& c2);
		bool circle_and_AABB(const circle& _circle, const AABB& aabb);
		bool circle_and_box(const circle& _circle, const box2D& box);
		/* AABB vs primitive tests */
		inline bool AABB_and_circle(const AABB& aabb, const circle& _circle) { return circle_and_AABB(_circle, aabb); }
		bool AABB_and_AABB(const AABB& aabb1, const AABB& aabb2);
		bool AABB_and_box2D(const AABB& aabb, const box2D& box);
	};
}