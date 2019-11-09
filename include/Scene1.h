#pragma once

#include "Scene.h"
#include "Box.h"
#include "Sphere.h"
#include "Plane.h"

class Scene1 : public Scene
{
public:
	Scene1(unsigned int screenWidth, unsigned int screenHeight);
	~Scene1();

	void Update();
	void Draw();

private:
	std::vector<Shape*> m_spheres;
	Box* m_box;
	Plane* m_plane;
	DirectionalLight* m_directionalLight;
	PointLight* m_pointLight;
};