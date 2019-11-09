#pragma once

#include "Shape.h"

class Plane : public Shape
{
public:
	Plane(vec3 origin, vec3 normal);
	virtual ~Plane();

	bool Hit(Ray const& ray, HitInfo& info) const;

	vec2 GetUvCoordinate(vec3 const& hitPoint) const;

	vec3 const& GetPosition() const;
	AABB GetBbox() const;
	vec3 const& GetOrigin() const;
	vec3 const& GetNormal() const;

	void SetBbox(AABB const& aabb);
	void SetOrigin(vec3 const& origin);
	void SetNormal(vec3 const& normal);

private:
	AABB m_bbox;
	vec3 m_origin;
	vec3 m_normal;
};