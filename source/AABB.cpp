#include "AABB.h"

AABB::AABB()
{
	m_min = vec3(-0.5f, -0.5f, -0.5f);
	m_max = vec3(0.5f, 0.5f, 0.5f);
}

AABB::AABB(vec3 min, vec3 max)
{
	m_min = min;
	m_max = max;
}

bool AABB::Hit(const Ray & ray, float & t) const
{
	float tmin = (m_min.m_X - ray.m_origin.m_X) / ray.m_direction.m_X;
	float tmax = (m_max.m_X - ray.m_origin.m_X) / ray.m_direction.m_X;
	if (tmin > tmax) { std::swap(tmin, tmax); };
	float tymin = (m_min.m_Y - ray.m_origin.m_Y) / ray.m_direction.m_Y;
	float tymax = (m_max.m_Y - ray.m_origin.m_Y) / ray.m_direction.m_Y;
	if (tymin > tymax) { std::swap(tymin, tymax); };
	if ((tmin > tymax) || (tymin > tmax)) { return false; }
	if (tymin > tmin) { tmin = tymin; }
	if (tymax < tmax) { tmax = tymax; }
	float tzmin = (m_min.m_Z - ray.m_origin.m_Z) / ray.m_direction.m_Z;
	float tzmax = (m_max.m_Z - ray.m_origin.m_Z) / ray.m_direction.m_Z;
	if (tzmin > tzmax) { std::swap(tzmin, tzmax); }
	if ((tmin > tzmax) || (tzmin > tmax)) { return false; }
	if (tzmin > tmin) { tmin = tzmin; }
	if (tzmax < tmax) { tmax = tzmax; }
	t = tmin;
	return true;
}
