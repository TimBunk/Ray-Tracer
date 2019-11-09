#include "Light.h"

Light::Light() 
{
	m_ambient = vec3(0.2f, 0.2f, 0.2f);
	m_diffuse = vec3(0.5f, 0.5f, 0.5f);
	m_specular = vec3(1.0f, 1.0f, 1.0f);
}

Light::~Light() 
{
}

DirectionalLight::DirectionalLight() 
{
	m_direction = vec3(0, 0, -1);
}

DirectionalLight::~DirectionalLight() 
{
}

PointLight::PointLight() 
{
	m_position = vec3();
	//http://wiki.ogre3d.org/tiki-index.php?page=-Point+Light+Attenuation
	constant = 1.0f;
	linear = 0.09f;
	quadratic = 0.032f;
	distance = 50.0f;
}

PointLight::~PointLight() 
{
}