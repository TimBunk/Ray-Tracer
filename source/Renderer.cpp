#include "Renderer.h"

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

void Renderer::Draw(Scene* scene, sf::Uint8 * pixels)
{
	Camera const* camera = scene->GetCamera();
	RenderOptions const& options = scene->GetRenderOptions();
	std::vector<Light*> const& lights = scene->GetLights();
	BVHAccelerator const* bvhAccelerator = scene->GetBvhAccelerator();

	unsigned int const& screenWidth = camera->GetScreenWidth();
	unsigned int const& screenHeight = camera->GetScreenHeight();
	Ray cameraRay;

	for (unsigned int x = 0; x < screenWidth; x++) {
		for (unsigned int y = 0; y < screenHeight; y++) {

			camera->GetCameraToWorldRay(x, y, cameraRay);

			unsigned int depth = 0;
			vec3 color = CastRay(cameraRay, lights, options, depth, bvhAccelerator);

			pixels[4 * (y * screenWidth + x) + 0] = (sf::Uint8)(color.m_X * 255.0f);
			pixels[4 * (y * screenWidth + x) + 1] = (sf::Uint8)(color.m_Y * 255.0f);
			pixels[4 * (y * screenWidth + x) + 2] = (sf::Uint8)(color.m_Z * 255.0f);
			pixels[4 * (y * screenWidth + x) + 3] = (sf::Uint8)(255.0f);
		}
	}
}

vec3 Renderer::CastRay(Ray const& ray, std::vector<Light*> const& lights, RenderOptions const& options, unsigned int depth, BVHAccelerator const* bvhAccelerator)
{
	if (depth > options.maxDepthRay) {
		return options.backgroundColor;
	}
	HitInfo hitInfo;
	bvhAccelerator->Hit(ray, hitInfo);
	vec3 color = vec3();
	if (hitInfo.m_shape != NULL) {
		switch (hitInfo.m_shape->GetMaterial().m_type)
		{
			case Type::diffuse:
			{
				color += ApplyLight(ray, lights, options, hitInfo, bvhAccelerator);
				break;
			}
			case Type::reflection:
			{
				Ray reflectionRay;
				reflectionRay.m_origin = hitInfo.m_hitPoint + hitInfo.m_normal * options.bias;
				reflectionRay.m_direction = reflect(ray.m_direction, hitInfo.m_normal).normalize();
				color += CastRay(reflectionRay, lights, options, ++depth, bvhAccelerator);
				break;
			}
			case Type::reflectionAndDiffuse:
			{
				vec3 lightColor;
				lightColor += ApplyLight(ray, lights, options, hitInfo, bvhAccelerator);
				float kr = fresnel(ray.m_direction, hitInfo.m_normal, 1.5f);
				Ray reflectionRay;
				reflectionRay.m_origin = hitInfo.m_hitPoint + hitInfo.m_normal * options.bias;
				reflectionRay.m_direction = reflect(ray.m_direction, hitInfo.m_normal).normalize();
				vec3 reflectionColor = CastRay(reflectionRay, lights, options, ++depth, bvhAccelerator);
				color += reflectionColor * kr + lightColor * (1 - kr);
				break;
			}
			case Type::refraction:
			{
				Material const& m = hitInfo.m_shape->GetMaterial();
				//http://www.scratchapixel.com/lessons/3d-basic-rendering/introduction-to-shading/reflection-refraction-fresnel
				float kr = fresnel(ray.m_direction, hitInfo.m_normal, m.ior);
				bool outside = ray.m_direction.dot(hitInfo.m_normal) < 0;
				vec3 refractionColor = vec3();
				// compute refraction if it is not a case of total internal reflection
				if (kr < 1) {
					Ray refractionRay;
					refractionRay.m_origin = outside ? hitInfo.m_hitPoint - (hitInfo.m_normal * options.bias) : hitInfo.m_hitPoint + (hitInfo.m_normal * options.bias);
					refractionRay.m_direction = refract(ray.m_direction, hitInfo.m_normal, m.ior).normalize();
					refractionColor = CastRay(refractionRay, lights, options, ++depth, bvhAccelerator);
				}
				Ray reflectionRay;
				reflectionRay.m_origin = outside ? hitInfo.m_hitPoint + (hitInfo.m_normal * options.bias) : hitInfo.m_hitPoint - (hitInfo.m_normal * options.bias);
				reflectionRay.m_direction = reflect(ray.m_direction, hitInfo.m_normal).normalize();
				vec3 reflectionColor = CastRay(reflectionRay, lights, options, ++depth, bvhAccelerator);

				// mix the two
				color += reflectionColor * kr + refractionColor * (1 - kr);
				break;
			}
		}
	}
	else {
		return options.backgroundColor;
	}
	return color;
}

vec3 Renderer::ApplyLight(Ray const & ray, std::vector<Light*> const & lights, RenderOptions const& options, HitInfo const & hitInfo, BVHAccelerator const* bvhAccelerator)
{
	Material const& material = hitInfo.m_shape->GetMaterial();
	vec3 color = vec3();
	for (unsigned int i = 0; i < lights.size(); i++) {
		vec3 lightDir;
		float attenuation = 1.0f;

		// Check if the light is a directionalLight
		DirectionalLight const* directionalLight = dynamic_cast<DirectionalLight const*>(lights[i]);
		if (directionalLight != NULL) {
			lightDir = directionalLight->m_direction * -1;
			// Check for shadows
			Ray shadowRay;
			shadowRay.m_origin = hitInfo.m_hitPoint + hitInfo.m_normal * options.bias;
			shadowRay.m_direction = lightDir;
			if (bvhAccelerator->HitFast(shadowRay)) { continue; }
		}
		// Otherwise it is a point light
		else {
			PointLight const* pointLight = static_cast<PointLight const*>(lights[i]);
			lightDir = (pointLight->m_position - hitInfo.m_hitPoint).normalize();

			Ray shadowRay;
			shadowRay.m_origin = pointLight->m_position;
			shadowRay.m_direction = lightDir * -1;
			HitInfo hitInfoTmp;
			bvhAccelerator->Hit(shadowRay, hitInfoTmp);
			if (hitInfoTmp.m_shape != hitInfo.m_shape) { continue; }

			float distance = (pointLight->m_position - hitInfo.m_hitPoint).length();
			// 750 is radius
			//float attenuation = clamp(1.0f - distance * distance / (750.0f*750.0f), 0.0f, 1.0f);
			//attenuation *= attenuation;
			attenuation = 1.0f / (pointLight->constant + pointLight->linear * distance + pointLight->quadratic * (distance * distance));
		}

		// Ambient
		vec3 ambient = vec3();
		// Check for a checkerboard pattern
		if (material.m_pattern == Pattern::checkerboard) {
			ambient = lights[i]->m_ambient * ApplyCheckerboard(hitInfo.m_shape, hitInfo.m_hitPoint);
		}
		else {
			ambient = lights[i]->m_ambient * material.m_ambient;
		}
		// Diffuse
		vec3 diffuse = lights[i]->m_diffuse * ((lights[i]->m_diffuse * material.m_diffuse) * std::max(0.0f, hitInfo.m_normal.dot(lightDir)));
		// Specular
		vec3 halfWayDir = (ray.m_direction + lightDir).normalize();
		float spec = std::pow(std::max(hitInfo.m_normal.dot(halfWayDir), 0.0f), material.m_shininess);
		vec3 specular = lights[i]->m_specular * ((lights[i]->m_specular * material.m_specular) * spec);
		// Attenuation, only applies for pointLights
		ambient *= attenuation;
		diffuse *= attenuation;
		specular *= attenuation;
		// Combined
		color += ambient + diffuse + specular;

	}
	return color;
}

vec3 Renderer::ApplyCheckerboard(Shape const* shape, vec3 const& hitPoint)
{
	Plane const* p = dynamic_cast<Plane const*>(shape);
	if (p != NULL) {
		vec2 uv = p->GetUvCoordinate(hitPoint);
		uv.m_X -= (float)std::floor(uv.m_X);
		uv.m_Y -= (float)std::floor(uv.m_Y);
		if (uv.m_X <= 0.5f) {
			if (uv.m_Y <= 0.5f) {
				return shape->GetMaterial().m_ambient;
			}
			else {
				return shape->GetMaterial().m_ambient2;
			}
		}
		else {
			if (uv.m_Y <= 0.5f) {
				return shape->GetMaterial().m_ambient2;
			}
			else {
				return shape->GetMaterial().m_ambient;
			}
		}
	}
	return shape->GetMaterial().m_ambient;
}