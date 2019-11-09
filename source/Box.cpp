#include "Box.h"

Box::Box(vec3 size)
{
	m_position = vec3();
	size *= 0.5f;
	m_bBox.m_min = size * -1;
	m_bBox.m_max = size;
	m_model = mat4::identity();
}

Box::~Box()
{
}

bool Box::Hit(const Ray & ray, HitInfo & info) const
{
	//http://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-box-intersection
	//http://blog.johnnovak.net/2016/10/22/the-nim-raytracer-project-part-4-calculating-box-normals/

	// Transform the ray from world space to object space
	mat4 worldToObject = m_model;
	worldToObject.inverse();
	vec4 rayOrigin = worldToObject * vec4(ray.m_origin, 1.0f);
	vec4 rayDirection = (worldToObject * vec4(ray.m_direction, 0.0f)).normalize();

	// Check for intersection
	Ray rayObjectSpace;
	rayObjectSpace.m_origin = vec3(rayOrigin.m_X, rayOrigin.m_Y, rayOrigin.m_Z);
	rayObjectSpace.m_direction = vec3(rayDirection.m_X, rayDirection.m_Y, rayDirection.m_Z);
	m_bBox.Hit(rayObjectSpace, info.m_distance);

	// Calculate the normal
	vec4 center = vec4(((m_bBox.m_min + m_bBox.m_max) * 0.5f), 1.0f);
	vec4 hitPoint = rayOrigin + (rayDirection * info.m_distance);
	vec4 diff = hitPoint - center;
	float bias = 1.001f;
	vec3 d = ((m_bBox.m_min - m_bBox.m_max) * 0.5f);

	info.m_normal = vec3((float)((int)(diff.m_X / std::abs(d.m_X) * bias)), (float)((int)(diff.m_Y / std::abs(d.m_Y) * bias)), (float)((int)(diff.m_Z / std::abs(d.m_Z) * bias))).normalize();
	vec4 n = (m_model * vec4(info.m_normal, 0.0f)).normalize();
	info.m_normal = vec3(n.m_X, n.m_Y, n.m_Z);
	// Calculate the hitPoint in world space
	hitPoint = m_model * hitPoint;
	info.m_hitPoint = vec3(hitPoint.m_X, hitPoint.m_Y, hitPoint.m_Z);
	info.m_shape = this;

	return true;
}

void Box::RotateX(float const & radians)
{
	m_model.rotateX(radians);
}

void Box::RotateY(float const & radians)
{
	m_model.rotateY(radians);
}

void Box::RotateZ(float const & radians)
{
	m_model.rotateZ(radians);
}

AABB Box::GetBbox() const
{
	float length = m_bBox.m_min.length();
	AABB bBox;
	bBox.m_min = vec3(-length, -length, -length);
	bBox.m_max = vec3(length, length, length);
	return bBox;
}

vec3 const& Box::GetPosition() const
{
	return m_position;
}

void Box::SetPosition(vec3 const & position)
{
	m_position = position;
	m_model.translate(position);
}
