#include "Scene.h"

Scene::Scene(unsigned int screenWidth, unsigned int screenHeight)
{
	m_camera = new Camera(screenWidth, screenHeight, 45.0f);
	m_renderOptions = RenderOptions();
	m_bvhAccelerator = new BVHAccelerator();
}

Scene::~Scene()
{
	delete m_camera;
	delete m_bvhAccelerator;
}

void Scene::Run()
{
	Update();
	Draw();
	m_bvhAccelerator->Build(m_shapes, m_renderOptions.maxDepthBVH, m_renderOptions.tresholdBVH);
}

Camera const * Scene::GetCamera()
{
	return m_camera;
}

std::vector<Shape*> const & Scene::GetShapes()
{
	return m_shapes;
}

std::vector<Light*> const & Scene::GetLights()
{
	return m_lights;
}

RenderOptions const & Scene::GetRenderOptions()
{
	return m_renderOptions;
}

BVHAccelerator const * Scene::GetBvhAccelerator()
{
	return m_bvhAccelerator;
}
