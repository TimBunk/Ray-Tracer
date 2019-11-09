#pragma once

#include "Ray.h"

class Camera
{
public:
	Camera(unsigned int screenWidth, unsigned int screenHeight, float FOV);
	~Camera();

	void GetCameraToWorldRay(const int& pixelX, const int& pixelY, Ray& ray) const;
	void RotateX(float const& radians);
	void RotateY(float const& radians);

	vec3 GetPosition() const;
	mat4 const& GetModelMatrix() const;
	float const& GetFOV() const;
	unsigned int const& GetScreenWidth() const;
	unsigned int const& GetScreenHeight() const;

	void SetPosition(vec3 const& position);
	void SetModelMatrix(mat4 const& model);
	void SetFOV(float const& FOV);
	void SetScreenWidth(unsigned int const& screenWidth);
	void SetScreenHeight(unsigned int const& screenHeight);

private:
	vec3 m_position;
	mat4 m_model;
	float m_FOV;// Field of view
	unsigned int m_screenWidth;
	unsigned int m_screenHeight;
};