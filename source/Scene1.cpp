#include "Scene1.h"

Scene1::Scene1(unsigned int screenWidth, unsigned int screenHeight) : Scene::Scene(screenWidth, screenHeight)
{
	for (int i = 0; i < 500; i++) {
		//float radius = random() * 2.5f;
		//vec3 position = vec3(random() * 30.0f, random() * 3.0f - 3.0f, random() * -30.0f);
		float radius = 2.0f;
		vec3 position = vec3(sin(i*0.05f) * i*0.075f, 0.0f, cos(i*0.05f) * i*0.075f);
		Sphere* sphere = new Sphere(radius);
		sphere->SetPosition(position);
		Material sphereMat;
		float r = random(), g = random(), b = random();
		sphereMat.m_ambient = vec3(r, g, b);
		sphereMat.m_diffuse = vec3(r, g, b);
		sphereMat.m_specular = vec3(0.5f, 0.5f, 0.5f);
		sphereMat.m_shininess = 32.0f;
		sphereMat.m_type = Type::diffuse;
		sphere->SetMaterial(sphereMat);
		m_spheres.push_back(sphere);
		m_shapes.push_back(sphere);
		/*float radius = random() * 1.5f + 1.0f;
		vec3 position = vec3(random() * 2.0f - 1.0f, 0.0f, random() * 2.0f - 1.0f).normalize();
		position *= random() * 10.0f + 10.0f;
		position.m_Y = 2.5f;
		Box* box = new Box(vec3(radius, radius, radius));
		box->RotateX(degToRad(random() * -90.0f + 45.0f));
		box->RotateY(degToRad(random() * -90.0f + 45.0f));
		box->SetPosition(position);
		Material boxMat;
		float r = random(), g = random(), b = random();
		boxMat.m_ambient = vec3(r, g, b);
		boxMat.m_diffuse = vec3(r, g, b);
		boxMat.m_specular = vec3(0.5f, 0.5f, 0.5f);
		boxMat.m_shininess = 32.0f;
		boxMat.m_type = Type::diffuse;
		box->SetMaterial(boxMat);
		m_spheres.push_back(box);
		m_shapes.push_back(box);*/

	}

	m_box = new Box(vec3(1, 1, 1));
	m_box->SetPosition(vec3(0, 0, -5));
	Material m;
	m.m_ambient = vec3(0.0f, 1.0f, 0.0f);
	m.m_diffuse = vec3(0.0f, 1.0f, 0.0f);
	m_box->SetMaterial(m);
	//m_shapes.push_back(m_box);

	m_plane = new Plane(vec3(0, 0, 0.0f), vec3(0,1,0));
	AABB bBoxPlane;
	bBoxPlane.m_min = vec3(-1000, -0.05f, -1000);
	bBoxPlane.m_max = vec3(1000, 0.05f, 1000.0f);
	Material planeMat;
	planeMat.m_ambient = vec3(1, 1, 1);
	planeMat.m_diffuse = vec3(1, 1, 1);
	planeMat.m_type = Type::reflectionAndDiffuse;
	m_plane->SetBbox(bBoxPlane);
	//m_shapes.push_back(m_plane);

	m_directionalLight = new DirectionalLight();
	m_directionalLight->m_ambient = vec3(0.2f, 0.2f, 0.2f);
	m_directionalLight->m_diffuse = vec3(0.5f, 0.5f, 0.5f);
	m_directionalLight->m_specular = vec3(1.0f, 1.0f, 1.0f);
	m_directionalLight->m_direction = vec3(1.0f, -1.0f, -1.0f).normalize();
	//m_directionalLight->m_direction = vec3(0.0f, -1.0f, 0.0f).normalize();

	m_pointLight = new PointLight();
	m_pointLight->linear = 0.014f;
	m_pointLight->quadratic = 0.0007f;
	m_pointLight->m_position = vec3(-1.25f, 2.0f, 0.0f);
	m_pointLight->distance = 325.0f;

	m_camera->SetPosition(vec3(0.0f, 18.0f, 50.0f));
	//m_camera->SetPosition(vec3(1.0f, 1.0f, 0.0f));
	//m_camera->SetPosition(vec3(-16.5f, 9.0f, 16.5f));
	m_camera->RotateX(degToRad(-10.0f));
	//m_camera->RotateY(degToRad(-45.0f));

	m_renderOptions.backgroundColor = vec3(0.53f,0.81f,0.98f);

	m_lights.push_back(m_directionalLight);
	//m_lights.push_back(pointLight);

	m_renderOptions.maxDepthBVH = 16;
	m_renderOptions.tresholdBVH = 2;
	//m_renderOptions.bias = 0.005f;
}

Scene1::~Scene1()
{
	std::vector<Shape*>::iterator it = m_spheres.begin();
	while (it != m_spheres.end()) {
		delete (*it);
		it = m_spheres.erase(it);
	}
	delete m_plane;

	delete m_directionalLight;
	delete m_pointLight;
}

void Scene1::Update()
{
}

void Scene1::Draw()
{
}
