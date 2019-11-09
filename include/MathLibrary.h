#pragma once

#include <stdio.h>
#include <iostream>
// To use M_PI I need to define _USE_MATH_DEFINES and include math.h https://stackoverflow.com/questions/1727881/how-to-use-the-pi-constant-in-c
#define _USE_MATH_DEFINES
#include <math.h>
#include <algorithm>

class vec3;

float degToRad(float degrees);
float radToDeg(float radians);

// Returns a random number between 0 and 1
float random();
float clamp(float value, float min, float max);

vec3 reflect(vec3 const& direction, vec3 const& normal);
vec3 refract(vec3 const& direction, vec3 const& normal, float const& ior);// ior stands for index of refraction
float fresnel(vec3 const& direction, vec3 const& normal, float const& ior);

// x = 0, y = 1, z = 2
int GetGreatestDimension(vec3 const& vec);

class vec2
{
public:
#pragma warning(push)
// Disable warning c4201: nonstandard extension used : nameless struct / union
#pragma warning(disable: 4201)
	union {
		struct
		{
			float m_X;
			float m_Y;
		};
		float v[2];
	};
#pragma warning(pop)

public:
	vec2();
	vec2(float a_X, float a_Y);
	
	vec2& operator=(const vec2& rhs);

	vec2& operator+=(const vec2 &a_Rhs);
	vec2& operator-=(const vec2 &a_Rhs);
	vec2& operator*=(float a_Rhs);
	vec2& operator/=(float a_Rhs);

	float operator[](int a_Index) const;
	float& operator[](int a_Index);

	float dot(const vec2& a_Rhs) const;
	vec2& normalize();
	float length() const;
};

vec2 operator+(const vec2 &a_Lhs, const vec2 &a_Rhs);
vec2 operator-(const vec2 &a_Lhs, const vec2 &a_Rhs);
vec2 operator*(const vec2 &a_Lhs, float a_Rhs);
vec2 operator/(const vec2 &a_Lhs, float a_Rhs);
bool operator==(const vec2 &a_Lhs, const vec2 &a_Rhs);
bool operator!=(const vec2 &a_Lhs, const vec2 &a_Rhs);

class vec3 {
public:
#pragma warning(push)
// Disable warning c4201: nonstandard extension used : nameless struct / union
#pragma warning(disable: 4201)
	union {
		struct
		{
			float m_X;
			float m_Y;
			float m_Z;
		};
		float v[3];
	};
#pragma warning(pop)

public:
	vec3();
	vec3(float a_X, float a_Y, float a_Z);

	vec3& operator=(const vec3& rhs);

	vec3& operator+=(const vec3 &a_Rhs);
	vec3& operator-=(const vec3 &a_Rhs);
	vec3& operator*=(float a_Rhs);
	vec3& operator/=(float a_Rhs);

	float operator[](int a_Index) const;
	float& operator[](int a_Index);

	float dot(const vec3& a_Rhs) const;
	vec3 cross(const vec3& a_Rhs) const;
	vec3& normalize();
	float length() const;
};

vec3 operator+(const vec3 &a_Lhs, const vec3 &a_Rhs);
vec3 operator-(const vec3 &a_Lhs, const vec3 &a_Rhs);
vec3 operator*(const vec3 &a_Lhs, float a_Rhs);
vec3 operator*(const vec3 &a_Lhs, const vec3& a_Rhs);
vec3 operator/(const vec3 &a_Lhs, float a_Rhs);
bool operator==(const vec3 &a_Lhs, const vec3 &a_Rhs);
bool operator!=(const vec3 &a_Lhs, const vec3 &a_Rhs);

class vec4 {
public:
#pragma warning(push)
	// Disable warning c4201: nonstandard extension used : nameless struct / union
#pragma warning(disable: 4201)
	union {
		struct
		{
			float m_X;
			float m_Y;
			float m_Z;
			float m_W;
		};
		float v[4];
	};
#pragma warning(pop)

public:
	vec4();
	vec4(float a_X, float a_Y, float a_Z, float a_W);
	vec4(const vec3& a_Vec3, float a_W);

	vec4& operator=(const vec4& rhs);

	vec4& operator+=(const vec4 &a_Rhs);
	vec4& operator-=(const vec4 &a_Rhs);
	vec4& operator*=(float a_Rhs);
	vec4& operator/=(float a_Rhs);

	float operator[](int a_Index) const;
	float& operator[](int a_Index);

	vec4& normalize();
	float length() const;
};

vec4 operator+(const vec4 &a_Lhs, const vec4 &a_Rhs);
vec4 operator-(const vec4 &a_Lhs, const vec4 &a_Rhs);
vec4 operator*(const vec4 &a_Lhs, float a_Rhs);
vec4 operator*(const vec4 &a_Lhs, const vec4& a_Rhs);
vec4 operator/(const vec4 &a_Lhs, float a_Rhs);
bool operator==(const vec4 &a_Lhs, const vec4 &a_Rhs);
bool operator!=(const vec4 &a_Lhs, const vec4 &a_Rhs);

class mat2 
{
public:
#pragma warning(push)
// Disable warning c4201: nonstandard extension used : nameless struct / union
#pragma warning(disable: 4201)
	union {
		struct
		{
			float m_00; float m_01;
			float m_10; float m_11;
		};
		float m[4];
	};
#pragma warning(pop)

public:
	mat2();
	mat2(vec2 a_Row0,
		vec2 a_Row1);
	mat2(float a_00, float a_01,
		float a_10, float a_11);

	mat2& operator=(const mat2& rhs);

	float determinant() const;

	static mat2 identity();
};

class mat3
{
public:
#pragma warning(push)
// Disable warning c4201: nonstandard extension used : nameless struct / union
#pragma warning(disable: 4201)
	union {
		struct
		{
			float m_00; float m_01; float m_02;
			float m_10; float m_11; float m_12;
			float m_20; float m_21; float m_22;
		};
		float m[9];
	};
#pragma warning(pop)

public:
	mat3();
	mat3(vec3 a_Row0,
		vec3 a_Row1,
		vec3 a_Row2);
	mat3(float a_00, float a_01, float a_02,
		float a_10, float a_11, float a_12,
		float a_20, float a_21, float a_22);

	mat3& operator=(const mat3& rhs);

	float determinant() const;

	static mat3 identity();
};

class mat4
{
public:
#pragma warning(push)
	// Disable warning c4201: nonstandard extension used : nameless struct / union
#pragma warning(disable: 4201)
	union {
		struct
		{
			float m_00; float m_01; float m_02; float m_03;
			float m_10; float m_11; float m_12; float m_13;
			float m_20; float m_21; float m_22; float m_23;
			float m_30; float m_31; float m_32; float m_33;
		};
		float m[16];
	};
#pragma warning(pop)

public:
	mat4();
	mat4(vec3 a_Row0, float a_03,
		vec3 a_Row1, float a_13,
		vec3 a_Row2, float a_23,
		vec3 a_Row3, float a_33);
	mat4(float a_00, float a_01, float a_02, float a_03,
		float a_10, float a_11, float a_12, float a_13,
		float a_20, float a_21, float a_22, float a_23,
		float a_30, float a_31, float a_32, float a_33);

	mat4& operator=(const mat4& rhs);

	mat4& operator+=(const mat4 &a_Rhs);
	mat4& operator-=(const mat4 &a_Rhs);
	mat4& operator*=(const mat4 &a_Rhs);

	float operator[](int a_Index) const;
	float& operator[](int a_Index);

	float determinant() const;
	mat4& inverse();
	mat4& transpose();

	static mat4 identity();
	mat4& rotateX(float a_Radians);
	mat4& rotateY(float a_Radians);
	mat4& rotateZ(float a_Radians);
	mat4& translate(const vec3 &a_Translation);

	//static mat4 lookat(const vec3 &a_Eye, const vec3 &a_Center, const vec3 &a_Up);
	//static mat4 projection(float a_FovY, float a_AspectRatio, float a_Near, float a_Far);
};

mat4 operator+(const mat4 &a_Lhs, const mat4 &a_Rhs);
mat4 operator-(const mat4 &a_Lhs, const mat4 &a_Rhs);
mat4 operator*(const mat4 &a_Lhs, const mat4 &a_Rhs);
vec4 operator*(const mat4 &a_Lhs, const vec4 &a_Rhs);