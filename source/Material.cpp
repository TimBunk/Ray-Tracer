#include "Material.h"

Material::Material()
{
	m_type = Type::diffuse;
	m_ambient = vec3(0.5f, 0.5f, 0.5f);
	m_diffuse = vec3(1.0f, 1.0f, 1.0f);
	m_specular = vec3(0.5f, 0.5f, 0.5f);
	m_shininess = 32.0f;
	m_pattern = Pattern::none;
	m_ambient2 = vec3(0.5f, 0.5f, 0.5f);
}