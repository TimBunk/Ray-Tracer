#include "..\include\Shape.h"

Shape::Shape()
{
}

Shape::~Shape()
{
}

Material const & Shape::GetMaterial() const
{
	return m_material;
}

void Shape::SetMaterial(Material const & material)
{
	m_material = material;
}
