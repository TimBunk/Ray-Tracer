#include "Sphere.h"

Sphere::Sphere()
{
	m_radius = 1.0f;
}

Sphere::Sphere(float radius)
{
	m_radius = radius;
}

Sphere::~Sphere()
{
}

bool Sphere::Hit(const Ray & ray, HitInfo& info) const
{
	//https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-sphere-intersection
	vec3 L = m_position - ray.m_origin;
	float tca = L.dot(ray.m_direction);
	if (tca < 0) { return false; }
	float d = L.dot(L) - tca * tca;
	if (d > m_radius) { return false; }
	float thc = sqrt(m_radius - d);

	float t0 = tca - thc;
	float t1 = tca + thc;
	if (t0 > t1) { t0 = t1; }
	if (t0 < 0) {
		t0 = t1;
		if (t0 < 0) { return false; }// both t0 and t1 are negative 
	}

	info.m_shape = this;
	info.m_distance = t0;
	info.m_hitPoint = ray.m_origin + (ray.m_direction * t0);
	// Calculate the normal
	info.m_normal = info.m_hitPoint - m_position;
	info.m_normal.normalize();

	return true;
}

AABB Sphere::GetBbox() const
{
	return AABB(vec3(-m_radius, -m_radius, -m_radius), vec3(m_radius, m_radius, m_radius));
}

vec3 const& Sphere::GetPosition() const
{
	return m_position;
}

float const& Sphere::GetRadius() const
{
	return m_radius;
}

void Sphere::SetPosition(vec3 const& position)
{
	m_position = position;
}

void Sphere::SetRadius(float const& radius)
{
	m_radius = radius;
}
