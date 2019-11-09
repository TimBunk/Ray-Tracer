#pragma once

#include "Shape.h"

class Box : public Shape
{
public:
	Box(vec3 size);
	~Box();

	bool Hit(const Ray& ray, HitInfo& info) const;

	void RotateX(float const& radians);
	void RotateY(float const& radians);
	void RotateZ(float const& radians);

	AABB GetBbox() const;
	vec3 const& GetPosition() const;

	void SetPosition(vec3 const& position);

private:
	vec3 m_position;
	mat4 m_model;
	AABB m_bBox;
};