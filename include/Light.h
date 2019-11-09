#pragma once

#include "MathLibrary.h"

class Light {
public:
	Light();
	virtual ~Light();

	vec3 m_ambient;
	vec3 m_diffuse;
	vec3 m_specular;
};

class DirectionalLight : public Light
{
public:
	DirectionalLight();
	virtual ~DirectionalLight();

	vec3 m_direction;
};

class PointLight : public Light
{
public:
	PointLight();
	virtual ~PointLight();

	vec3 m_position;
	//http://wiki.ogre3d.org/tiki-index.php?page=-Point+Light+Attenuation
	float constant;
	float linear;
	float quadratic;
	float distance;
};