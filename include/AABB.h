#pragma once

#include "Ray.h"

class AABB {
public:
	AABB();
	AABB(vec3 min, vec3 max);
	bool Hit(const Ray& ray, float& t) const;
	vec3 m_min, m_max;
};