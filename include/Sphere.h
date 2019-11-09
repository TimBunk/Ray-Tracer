#pragma once

#include "Shape.h"

class Sphere : public Shape
{
public:
	Sphere();
	Sphere(float radius);
	~Sphere();

	bool Hit(const Ray& ray, HitInfo& info) const;
	AABB GetBbox() const;

	vec3 const& GetPosition() const;
	float const& GetRadius() const;
	void SetPosition(vec3 const& position);
	void SetRadius(float const& radius);

private:
	vec3 m_position;
	float m_radius;
};