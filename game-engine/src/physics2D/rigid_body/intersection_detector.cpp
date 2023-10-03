#include "pch.h"
#include "intersection_detector.h"
#include "math/math.h"


// SAT helpers
namespace physics2D
{
    namespace intersection_detector
    {
        glm::f32vec2 get_interval(const physics2D::AABB& aabb, const glm::f32vec2& axis);
        glm::f32vec2 get_interval(const physics2D::box2D& box, const glm::f32vec2& axis);
        bool overlap_on_axis(const AABB& aabb1, const AABB& aabb2, const glm::f32vec2& axis);
        bool overlap_on_axis(const AABB& aabb, const box2D& box, const glm::f32vec2& axis);
        bool overlap_on_axis(const box2D& box1, const box2D& box2, const glm::f32vec2& axis);
    }
}


bool physics2D::intersection_detector::point_on_line(const glm::f32vec2& point, const line2D& line)
{
    bool result;
    float dx = line.end().x - line.start().x;
    float dy = line.end().y - line.start().y;
    
    if (dx == 0.0f)
    {
        result = math::cmp(point.x, line.start().x);
    }
    else
    {
        float m = dy / dx;
        float b = line.end().y - (m * line.end().x);
        result = point.y == m * point.x + b;
    }
    return result;
}

bool physics2D::intersection_detector::point_in_circle(const glm::f32vec2& point, const circle& _circle)
{
    return glm::distance2(_circle.center(), point) <= (_circle.radius() * _circle.radius());
}

bool physics2D::intersection_detector::point_in_AABB(const glm::f32vec2& point, const AABB& aabb)
{
    return aabb.min().x <= point.x && point.x <= aabb.max().x &&
           aabb.min().y <= point.y && point.y <= aabb.max().y;
}

bool physics2D::intersection_detector::point_in_box2D(const glm::f32vec2& point, const box2D& box)
{
    glm::f32vec2 rotated_point = point;
    math::vec::rotate(rotated_point, box.rigid_body().rotation(), box.rigid_body().position());

    return box.locale_min().x <= rotated_point.x && rotated_point.x <= box.locale_max().x &&
           box.locale_min().y <= rotated_point.y && rotated_point.y <= box.locale_max().y;
}

bool physics2D::intersection_detector::line_and_circle(const line2D& line, const circle& _circle)
{
    if (point_in_circle(line.start(), _circle) || point_in_circle(line.end(), _circle))
        return true;

    glm::f32vec2 ab = line.end() - line.start();
    glm::f32vec2 circle_center = _circle.center();
    glm::f32vec2 center_to_line_start = circle_center - line.start();
    float t = glm::dot(center_to_line_start, ab) / glm::dot(ab, ab);

    if (t < 0.0f || t > 1.0f) 
        return false;

    // find the closest point to the line segment
    const glm::f32vec2& closest_point = line.start() + t * ab;

    return point_in_circle(closest_point, _circle);
}

bool physics2D::intersection_detector::line_and_AABB(const line2D& line, const AABB& aabb)
{
    if (point_in_AABB(line.start(), aabb) || point_in_AABB(line.end(), aabb))
        return true;

    glm::f32vec2 unit_vector = line.end() - line.start();
    unit_vector = glm::normalize(unit_vector);
    unit_vector.x = (unit_vector.x != 0) ? 1.0f / unit_vector.x : 0.0f;
    unit_vector.y = (unit_vector.y != 0) ? 1.0f / unit_vector.y : 0.0f;

    glm::f32vec2 min = aabb.min();
    glm::f32vec2 max = aabb.min();

    min = (min - line.start()) * unit_vector;
    max = (max - line.start()) * unit_vector;
   
    float tmin = std::max(std::min(min.x, max.x), std::min(min.y, max.y));
    float tmax = std::min(std::max(min.x, max.x), std::max(min.y, max.y));

    if (tmax < 0 || tmin > tmax)
        return false;
    
    float t = (tmin < 0.0f) ? tmax : tmin;
    return t > 0.0f && t * t < line.length2();
}

bool physics2D::intersection_detector::line_and_box2D(const line2D& line, const box2D& box)
{
    float theta = box.rigid_body().rotation();
    glm::f32vec2 center = box.rigid_body().position();
    glm::f32vec2 local_start = line.start();
    glm::f32vec2 local_end = line.end();

    math::vec::rotate(local_start, theta, center);
    math::vec::rotate(local_end, theta, center);
    
    line2D local_line(local_start, local_end);
    AABB aabb(box.locale_min(), box.locale_max());

    return line_and_AABB(local_line, aabb);
}

bool physics2D::intersection_detector::raycast(const circle& _circle, const ray2D& ray, std::optional<raycast_result>& result)
{
    glm::f32vec2 origin_to_circle = _circle.center() - ray.origin();

    float radius_squared = _circle.radius() * _circle.radius();
    float origin_to_circle_length_squared = glm::length2(origin_to_circle);

    float a = glm::dot(origin_to_circle, ray.direction());
    float bSq = origin_to_circle_length_squared - (a * a);
    
    if (radius_squared - bSq < 0.0f)
        return false;

    float f = (float)std::sqrt(radius_squared - bSq);
    float t = 0;
    if (origin_to_circle_length_squared < radius_squared) 
        // ray starts inside the circle
        t = a + f;    
    else
        t = a - f;
    
    if (result.has_value())
    {
        raycast_result::reset(result.value());
        glm::f32vec2 point = ray.origin() + ray.direction() * t;
        glm::f32vec2 normal =  glm::normalize(point - _circle.center());
        result->init(point, normal, t, true);
    }

    return true;
}

bool physics2D::intersection_detector::circle_and_circle(const circle& c1, const circle& c2)
{
    glm::f32vec2 vec_between_centers = c1.center() - c2.center();
    float radiiSum = c1.radius() + c2.radius();
    return glm::length2(vec_between_centers) <= radiiSum * radiiSum;
}

bool physics2D::intersection_detector::circle_and_AABB(const circle& _circle, const AABB& box)
{
    glm::f32vec2 min = box.min();
    glm::f32vec2 max = box.max();

    glm::f32vec2 closest_point_to_circle = _circle.center();
    
    if (closest_point_to_circle.x < min.x)
    {
        closest_point_to_circle.x = min.x;
    }
    else if (closest_point_to_circle.x > max.x)
    {
        closest_point_to_circle.x = min.x;
    }

    if (closest_point_to_circle.y < min.y)
    {
        closest_point_to_circle.y = min.y;
    }
    else if (closest_point_to_circle.y > max.y)
    {
        closest_point_to_circle.y = min.y;
    }

    glm::f32vec2 circle_to_box = _circle.center() - closest_point_to_circle;
    return glm::length2(circle_to_box) <= _circle.radius() * _circle.radius();
}

bool physics2D::intersection_detector::circle_and_box(const circle& _circle, const box2D& box)
{
    // Treat the box just like an AABB, after we rotate the stuff
    glm::f32vec2 min = { 0.0f, 0.0f };
    glm::f32vec2 max = box.half_size() * 2.0f;

    glm::f32vec2 r = _circle.center() - box.rigid_body().position();
    math::vec::rotate(r, -box.rigid_body().rotation(), box.half_size());
    glm::f32vec2 local_circle_pos = r + box.half_size();

    glm::f32vec2 closest_point_to_circle = local_circle_pos;

    if (closest_point_to_circle.x < min.x)
    {
        closest_point_to_circle.x = min.x;
    }
    else if (closest_point_to_circle.x > max.x)
    {
        closest_point_to_circle.x = min.x;
    }

    if (closest_point_to_circle.y < min.y)
    {
        closest_point_to_circle.y = min.y;
    }
    else if (closest_point_to_circle.y > max.y)
    {
        closest_point_to_circle.y = min.y;
    }

    glm::f32vec2 circle_to_box = local_circle_pos - closest_point_to_circle;
    return glm::length2(circle_to_box) <= _circle.radius() * _circle.radius();
}

bool physics2D::intersection_detector::AABB_and_AABB(const AABB& aabb1, const AABB& aabb2)
{
    glm::f32vec2 axes_to_test[] = { {0, 1}, {1, 0} };
    for (const glm::f32vec2& axis : axes_to_test)
    {
        if (!overlap_on_axis(aabb1, aabb2, axis))
            return false;
    }

    return true;
}

bool physics2D::intersection_detector::AABB_and_box2D(const AABB& aabb, const box2D& box)
{
    glm::f32vec2 axes_to_test[] = { {0, 1}, {1, 0}, {0, 1}, {1, 0} };
    float rotation = box.rigid_body().rotation();

    math::vec::rotate(axes_to_test[2], rotation, box.rigid_body().position());
    math::vec::rotate(axes_to_test[3], rotation, box.rigid_body().position());

    for (glm::f32vec2& axis : axes_to_test)
    {   
        if (!overlap_on_axis(aabb, box, axis))
            return false;
    }

    return true;
}

// SAT helpers
namespace physics2D
{
    namespace intersection_detector
    {
        glm::f32vec2 get_interval(const physics2D::AABB& aabb, const glm::f32vec2& axis)
        {
            glm::f32vec2 result = { 0, 0 };

            glm::f32vec2 min = aabb.min();
            glm::f32vec2 max = aabb.max();

            glm::f32vec2 vertices[] = {
                {min.x, min.y}, {min.x, max.y},
                {max.x, min.y}, {max.x, max.y}
            };

            result.x = result.y = glm::dot(axis, vertices[0]);

            for (const glm::f32vec2& vertex : vertices)
            {
                float proj = glm::dot(axis, vertex);
                if (result.x > proj)
                    result.x = proj;
                if (result.y < proj)
                    result.y = proj;
            }

            return result;
        }

        glm::f32vec2 get_interval(const physics2D::box2D& box, const glm::f32vec2& axis)
        {
            glm::f32vec2 result = { 0, 0 };

            std::vector<glm::f32vec2> vertices = box.vertices();

            result.x = result.y = glm::dot(axis, vertices[0]);

            for (const glm::f32vec2& vertex : vertices)
            {
                float proj = glm::dot(axis, vertex);
                if (result.x > proj)
                    result.x = proj;
                if (result.y < proj)
                    result.y = proj;
            }

            return result;
        }
        bool overlap_on_axis(const AABB& aabb1, const AABB& aabb2, const glm::f32vec2& axis)
        {
            glm::f32vec2 interval1 = get_interval(aabb1, axis);
            glm::f32vec2 interval2 = get_interval(aabb2, axis);
            return interval2.x <= interval1.y && interval1.x <= interval2.y;
        }
        bool overlap_on_axis(const AABB& aabb, const box2D& box, const glm::f32vec2& axis)
        {
            glm::f32vec2 interval1 = get_interval(aabb, axis);
            glm::f32vec2 interval2 = get_interval(box, axis);
            return interval2.x <= interval1.y && interval1.x <= interval2.y;
        }

        bool overlap_on_axis(const box2D& box1, const box2D& box2, const glm::f32vec2& axis)
        {
            glm::f32vec2 interval1 = get_interval(box1, axis);
            glm::f32vec2 interval2 = get_interval(box2, axis);
            return interval2.x <= interval1.y && interval1.x <= interval2.y;
        }
    }
}