#include "Plane.h"

Plane::Plane(vec3 origin, vec3 normal)
{
	m_bbox = AABB();
	m_origin = origin;
	m_normal = normal;
}

Plane::~Plane()
{
}

bool Plane::Hit(Ray const& ray, HitInfo & info) const
{
	// http://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-plane-and-ray-disk-intersection
	float denom = m_normal.dot(ray.m_direction);
	if (std::abs(denom) > 0.0001f) {
		vec3 diff = m_origin - ray.m_origin;
		float t = diff.dot(m_normal) / denom;
		if (t >= 0) {
			info.m_shape = this;
			info.m_distance = t;
			info.m_hitPoint = ray.m_origin + (ray.m_direction * t);
			info.m_normal = m_normal;
			return true;
		}
	}
	return false;
}

vec2 Plane::GetUvCoordinate(vec3 const& hitPoint) const
{
	vec3 u, v;
	if (m_normal.m_Y != 0 && m_normal.m_X != 0) {
		u = vec3(m_normal.m_Y, -m_normal.m_X, 0).normalize();
	}
	else {
		u = vec3(m_normal.m_Y, m_normal.m_Z, 0).normalize();
	}
	v = m_normal.cross(u);
	vec2 uv = vec2(u.dot(hitPoint), v.dot(hitPoint));
	return uv;
}

vec3 const & Plane::GetPosition() const
{
	return m_origin;
}

AABB Plane::GetBbox() const
{
	return m_bbox;
}


vec3 const & Plane::GetOrigin() const
{
	return m_origin;
}

vec3 const & Plane::GetNormal() const
{
	return m_normal;
}

void Plane::SetBbox(AABB const & aabb)
{
	m_bbox = aabb;
}

void Plane::SetOrigin(vec3 const & origin)
{
	m_origin = origin;
}

void Plane::SetNormal(vec3 const & normal)
{
	m_normal = normal;
}