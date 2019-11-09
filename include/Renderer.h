#pragma once

#include <SFML/Graphics.hpp>

#include <cstdint>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <random>

#include "Plane.h"
#include "Scene.h"

class Renderer
{
public:
	Renderer();
	~Renderer();

	void Draw(Scene* scene, sf::Uint8* pixels);

private:
	vec3 CastRay(Ray const& ray, std::vector<Light*> const& lights, RenderOptions const& options, unsigned int depth, BVHAccelerator const* bvhAccelerator);
	vec3 ApplyLight(Ray const& ray, std::vector<Light*> const& lights, RenderOptions const& options, HitInfo const& hitInfo, BVHAccelerator const* bvhAccelerator);
	//void GetClosestShape(Ray const& ray, std::vector<Shape*> const& shapes, HitInfo& hitInfo);
	//bool CheckForAnyIntersection(Ray const& ray, std::vector<Shape*> const& shapes);
	//bool DoesRayReachShape(Ray const& ray, std::vector<Shape*> const& shapes, RenderOptions const& options, float const& maxDistance, Shape const* shape, vec3 const& hitPoint);

	vec3 ApplyCheckerboard(Shape const* shape, vec3 const& hitPoint);
};