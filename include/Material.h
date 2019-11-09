#pragma once

#include "MathLibrary.h"

enum Type {
	diffuse,
	reflection,
	reflectionAndDiffuse,
	refraction
};

enum Pattern {
	none,
	checkerboard
};

struct Material
{
	Type m_type = Type::diffuse;
	vec3 m_ambient = vec3(0.5f, 0.5f, 0.5f);
	vec3 m_diffuse = vec3(1.0f, 1.0f, 1.0f);
	vec3 m_specular = vec3(0.5f, 0.5f, 0.5f);
	float m_shininess = 32.0f;
	float ior = 1.5f;//ior stands for index of refraction
	Pattern m_pattern = Pattern::none;
	vec3 m_ambient2 = vec3(0.5f, 0.5f, 0.5f);
};