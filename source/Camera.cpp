#include "Camera.h"

Camera::Camera(unsigned int screenWidth, unsigned int screenHeight, float FOV)
{
	m_screenWidth = screenWidth;
	m_screenHeight = screenHeight;
	m_FOV = FOV;
	m_model = mat4::identity();
}

Camera::~Camera()
{
}

void Camera::GetCameraToWorldRay(const int & pixelX, const int & pixelY, Ray & ray) const
{
	float aspectRatio = (float)m_screenWidth / (float)m_screenHeight;
	float scale = std::tan(degToRad(m_FOV * 0.5f));
	// Go from raster space to NDC space(Maps from 0 to 1)
	float pixelCameraX = ((float)pixelX + 0.5f) / (float)m_screenWidth;
	float pixelCameraY = ((float)pixelY + 0.5f) / (float)m_screenHeight;
	// Go from NDC space to screen space(Maps from -1 to 1)
	pixelCameraX = 2.0f * pixelCameraX - 1.0f;
	pixelCameraY = 1.0f - 2.0f * pixelCameraY;
	// Screen space to camera space
	pixelCameraX = pixelCameraX * aspectRatio * scale;
	pixelCameraY = pixelCameraY * scale;

	ray.m_origin = m_position;
	vec3 rayDirection = vec3(pixelCameraX, pixelCameraY, -1.0f);
	vec4 rayDirection2 = m_model * vec4(rayDirection, 0.0f);
	rayDirection2.normalize();
	ray.m_direction = vec3(rayDirection2.m_X, rayDirection2.m_Y, rayDirection2.m_Z);
}

void Camera::RotateX(float const & radians)
{
	m_model.rotateX(radians);
}

void Camera::RotateY(float const & radians)
{
	m_model.rotateY(radians);
}

vec3 Camera::GetPosition() const
{
	return m_position;
}

mat4 const & Camera::GetModelMatrix() const
{
	return m_model;
}

float const & Camera::GetFOV() const
{
	return m_FOV;
}

unsigned int const & Camera::GetScreenWidth() const
{
	return m_screenWidth;
}

unsigned int const & Camera::GetScreenHeight() const
{
	return m_screenHeight;
}

void Camera::SetPosition(vec3 const & position)
{
	m_position = position;
}

void Camera::SetModelMatrix(mat4 const & model)
{
	m_model = model;
}

void Camera::SetFOV(float const & FOV)
{
	m_FOV = FOV;
}

void Camera::SetScreenWidth(unsigned int const & screenWidth)
{
	m_screenWidth = screenWidth;
}

void Camera::SetScreenHeight(unsigned int const & screenHeight)
{
	m_screenHeight = screenHeight;
}
