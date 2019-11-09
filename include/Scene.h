#pragma once

#include "BVHAccelerator.h"
#include "Light.h"
#include "Camera.h"

struct RenderOptions {
	float bias = 0.001f;
	unsigned int maxDepthRay = 5;
	unsigned int maxDepthBVH = 16;
	unsigned int tresholdBVH = 2;
	vec3 backgroundColor = vec3();
};

class Scene
{
public:
	Scene(unsigned int screenWidth, unsigned int screenHeight);
	virtual ~Scene();

	void Run();

	Camera const* GetCamera();
	std::vector<Shape*> const& GetShapes();
	std::vector<Light*> const& GetLights();
	RenderOptions const& GetRenderOptions();
	BVHAccelerator const* GetBvhAccelerator();


protected:
	virtual void Update() = 0;
	virtual void Draw() = 0;

	Camera* m_camera;
	std::vector<Shape*> m_shapes;
	std::vector<Light*> m_lights;
	RenderOptions m_renderOptions;
private:
	BVHAccelerator* m_bvhAccelerator;
};