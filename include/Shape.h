#pragma once

#include "Material.h"
#include "AABB.h"

class Shape;

struct HitInfo {
	Shape const* m_shape = NULL;
	float m_distance = INFINITY;
	vec3 m_hitPoint = vec3();
	vec3 m_normal = vec3();
};

class Shape
{
public:
	Shape();
	virtual ~Shape();

	virtual bool Hit(const Ray& ray, HitInfo& info) const = 0;
	virtual AABB GetBbox() const = 0;
	virtual vec3 const& GetPosition() const = 0;

	Material const& GetMaterial() const;
	void SetMaterial(Material const& material);

private:
	Material m_material;
};