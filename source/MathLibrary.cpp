#include <MathLibrary.h>

float degToRad(float degrees)
{
	return degrees * ((float)M_PI / 180.0f);
}

float radToDeg(float radians)
{
	return radians * (180.0f / (float)M_PI);
}

float random()
{
	return (float)std::rand() / (float)RAND_MAX;
}

float clamp(float value, float min, float max)
{
	float clampedValue = value;
	if (clampedValue < min) {
		clampedValue = min;
	}
	else if (clampedValue > max) {
		clampedValue = max;
	}
	return clampedValue;
}

vec3 reflect(vec3 const & direction, vec3 const & normal)
{
	return (direction - normal * normal.dot(direction) * 2);
}

vec3 refract(vec3 const & direction, vec3 const & normal, float const & ior)
{
	float cosi = clamp(-1, 1, direction.dot(normal));
	float etai = 1, etat = ior; // etai is the index of refraction of the medium the ray is in before entering the second medium
	vec3 n = normal;
	if (cosi < 0) {
		cosi = -cosi;
	}
	else {
		n = normal * -1;
		std::swap(etai, etat);
	}
	float eta = etai / etat;
	float k = 1 - eta * eta * (1 - cosi * cosi);
	return k < 0 ? vec3(0, 0, 0) : (direction * eta + n * (eta * cosi - sqrtf(k)));
}

float fresnel(vec3 const & direction, vec3 const & normal, float const & ior)
{
	float cosi = clamp(-1, 1, direction.dot(normal));
	float etai = 1, etat = ior;
	if (cosi > 0) {
		std::swap(etai, etat);
	}
	float sint = etai / etat * sqrt(std::max(0.f, 1 - cosi * cosi));
	if (sint >= 1) {
		return 1.0f;
	}
	float cost = sqrtf(std::max(0.f, 1 - sint * sint));
	cosi = std::fabs(cosi);
	float Rs = ((etat * cosi) - (etai * cost)) / ((etat * cosi) + (etai * cost));
	float Rp = ((etai * cosi) - (etat * cost)) / ((etai * cosi) + (etat * cost));
	return (Rs * Rs + Rp * Rp) / 2.0f;
}

int GetGreatestDimension(vec3 const & vec)
{
	if (vec.m_X > vec.m_Y) {
		if (vec.m_X > vec.m_Z) {
			return 0;
		}
		else {
			return 2;
		}
	}
	else if (vec.m_Y > vec.m_Z) {
		return 1;
	}
	return 2;
}

vec2::vec2()
{
	m_X = 0;
	m_Y = 0;
}

vec2::vec2(float a_X, float a_Y)
{
	m_X = a_X;
	m_Y = a_Y;
}

vec2 & vec2::operator=(const vec2 & rhs)
{
	m_X = rhs.m_X;
	m_Y = rhs.m_Y;
	return *this;
}

vec2 & vec2::operator+=(const vec2 & a_Rhs)
{
	m_X += a_Rhs.m_X;
	m_Y += a_Rhs.m_Y;
	return *this;
}

vec2 & vec2::operator-=(const vec2 & a_Rhs)
{
	m_X -= a_Rhs.m_X;
	m_Y -= a_Rhs.m_Y;
	return *this;
}

vec2 & vec2::operator*=(float a_Rhs)
{
	m_X *= a_Rhs;
	m_Y *= a_Rhs;
	return *this;
}

vec2 & vec2::operator/=(float a_Rhs)
{
	m_X /= a_Rhs;
	m_Y /= a_Rhs;
	return *this;
}

float vec2::operator[](int a_Index) const
{
	return v[a_Index];
}

float & vec2::operator[](int a_Index)
{
	return v[a_Index];
}

float vec2::dot(const vec2 & a_Rhs) const
{
	return m_X * a_Rhs.m_X + m_Y * a_Rhs.m_Y;
}

vec2& vec2::normalize()
{
	float l = length();
	if (m_X != 0) {
		m_X /= l;
	}
	if (m_Y != 0) {
		m_Y /= l;
	}
	return *this;
}

float vec2::length() const
{
	return sqrt(m_X * m_X + m_Y * m_Y);
}

vec2 operator+(const vec2 & a_Lhs, const vec2 & a_Rhs)
{
	return vec2(
		a_Lhs.m_X + a_Rhs.m_X,
		a_Lhs.m_Y + a_Rhs.m_Y);
}

vec2 operator-(const vec2 & a_Lhs, const vec2 & a_Rhs)
{
	return vec2(
		a_Lhs.m_X - a_Rhs.m_X,
		a_Lhs.m_Y - a_Rhs.m_Y);
}

vec2 operator*(const vec2 & a_Lhs, float a_Rhs)
{
	return vec2(
		a_Lhs.m_X * a_Rhs,
		a_Lhs.m_Y * a_Rhs);
}

vec2 operator/(const vec2 & a_Lhs, float a_Rhs)
{
	return vec2(
		a_Lhs.m_X / a_Rhs,
		a_Lhs.m_Y / a_Rhs);
}

bool operator==(const vec2 & a_Lhs, const vec2 & a_Rhs)
{
	return (a_Lhs.m_X == a_Rhs.m_X && a_Lhs.m_Y == a_Rhs.m_Y);
}

bool operator!=(const vec2 & a_Lhs, const vec2 & a_Rhs)
{
	return (a_Lhs.m_X != a_Rhs.m_X || a_Lhs.m_Y != a_Rhs.m_Y);
}

vec3::vec3()
{
	m_X = 0;
	m_Y = 0;
	m_Z = 0;
}

vec3::vec3(float a_X, float a_Y, float a_Z)
{
	m_X = a_X;
	m_Y = a_Y;
	m_Z = a_Z;
}

vec3 & vec3::operator=(const vec3 & rhs)
{
	m_X = rhs.m_X;
	m_Y = rhs.m_Y;
	m_Z = rhs.m_Z;
	return *this;
}

vec3 & vec3::operator+=(const vec3 & a_Rhs)
{
	m_X += a_Rhs.m_X;
	m_Y += a_Rhs.m_Y;
	m_Z += a_Rhs.m_Z;
	return *this;
}

vec3 & vec3::operator-=(const vec3 & a_Rhs)
{
	m_X -= a_Rhs.m_X;
	m_Y -= a_Rhs.m_Y;
	m_Z -= a_Rhs.m_Z;
	return *this;
}

vec3 & vec3::operator*=(float a_Rhs)
{
	m_X *= a_Rhs;
	m_Y *= a_Rhs;
	m_Z *= a_Rhs;
	return *this;
}

vec3 & vec3::operator/=(float a_Rhs)
{
	m_X /= a_Rhs;
	m_Y /= a_Rhs;
	m_Z /= a_Rhs;
	return *this;
}

float vec3::operator[](int a_Index) const
{
	return v[a_Index];
}

float & vec3::operator[](int a_Index)
{
	return v[a_Index];
}

float vec3::dot(const vec3 & a_Rhs) const
{
	return m_X * a_Rhs.m_X + m_Y * a_Rhs.m_Y + m_Z * a_Rhs.m_Z;
}

vec3 vec3::cross(const vec3 & a_Rhs) const
{
	return vec3(
		m_Y * a_Rhs.m_Z - m_Z * a_Rhs.m_Y,
		m_Z * a_Rhs.m_X - m_X * a_Rhs.m_Z,
		m_X * a_Rhs.m_Y - m_Y * a_Rhs.m_X);
}

vec3 & vec3::normalize()
{
	float l = length();
	if (m_X != 0) {
		m_X /= l;
	}
	if (m_Y != 0) {
		m_Y /= l;
	}
	if (m_Z != 0) {
		m_Z /= l;
	}
	return *this;
}

float vec3::length() const
{
	return sqrt(m_X * m_X + m_Y * m_Y + m_Z * m_Z);
}

vec3 operator+(const vec3 & a_Lhs, const vec3 & a_Rhs)
{
	return vec3(
		a_Lhs.m_X + a_Rhs.m_X,
		a_Lhs.m_Y + a_Rhs.m_Y,
		a_Lhs.m_Z + a_Rhs.m_Z);
}

vec3 operator-(const vec3 & a_Lhs, const vec3 & a_Rhs)
{
	return vec3(
		a_Lhs.m_X - a_Rhs.m_X,
		a_Lhs.m_Y - a_Rhs.m_Y,
		a_Lhs.m_Z - a_Rhs.m_Z);
}

vec3 operator*(const vec3 & a_Lhs, float a_Rhs)
{
	return vec3(
		a_Lhs.m_X * a_Rhs,
		a_Lhs.m_Y * a_Rhs,
		a_Lhs.m_Z * a_Rhs);
}

vec3 operator*(const vec3 & a_Lhs, const vec3 & a_Rhs)
{
	return vec3(
		a_Lhs.m_X * a_Rhs.m_X,
		a_Lhs.m_Y * a_Rhs.m_Y,
		a_Lhs.m_Z * a_Rhs.m_Z
	);
}

vec3 operator/(const vec3 & a_Lhs, float a_Rhs)
{
	return vec3(
		a_Lhs.m_X / a_Rhs,
		a_Lhs.m_Y / a_Rhs,
		a_Lhs.m_Z / a_Rhs);
}

bool operator==(const vec3 & a_Lhs, const vec3 & a_Rhs)
{
	return (a_Lhs.m_X == a_Rhs.m_X && a_Lhs.m_Y == a_Rhs.m_Y && a_Lhs.m_Z == a_Rhs.m_Z);
}

bool operator!=(const vec3 & a_Lhs, const vec3 & a_Rhs)
{
	return (a_Lhs.m_X != a_Rhs.m_X || a_Lhs.m_Y != a_Rhs.m_Y || a_Lhs.m_Z != a_Rhs.m_Z);
}

vec4::vec4()
{
	m_X = 0;
	m_Y = 0;
	m_Z = 0;
	m_W = 0;
}

vec4::vec4(float a_X, float a_Y, float a_Z, float a_W)
{
	m_X = a_X;
	m_Y = a_Y;
	m_Z = a_Z;
	m_W = a_W;
}

vec4::vec4(const vec3& a_Vec3, float a_W)
{
	m_X = a_Vec3.m_X;
	m_Y = a_Vec3.m_Y;
	m_Z = a_Vec3.m_Z;
	m_W = a_W;
}

vec4 & vec4::operator=(const vec4 & rhs)
{
	m_X = rhs.m_X;
	m_Y = rhs.m_Y;
	m_Z = rhs.m_Z;
	m_W = rhs.m_W;
	return *this;
}

vec4 & vec4::operator+=(const vec4 & a_Rhs)
{
	m_X += a_Rhs.m_X;
	m_Y += a_Rhs.m_Y;
	m_Z += a_Rhs.m_Z;
	m_W += a_Rhs.m_W;
	return *this;
}

vec4 & vec4::operator-=(const vec4 & a_Rhs)
{
	m_X -= a_Rhs.m_X;
	m_Y -= a_Rhs.m_Y;
	m_Z -= a_Rhs.m_Z;
	m_W -= a_Rhs.m_W;
	return *this;
}

vec4 & vec4::operator*=(float a_Rhs)
{
	m_X *= a_Rhs;
	m_Y *= a_Rhs;
	m_Z *= a_Rhs;
	m_W *= a_Rhs;
	return *this;
}

vec4 & vec4::operator/=(float a_Rhs)
{
	m_X /= a_Rhs;
	m_Y /= a_Rhs;
	m_Z /= a_Rhs;
	m_W /= a_Rhs;
	return *this;
}

float vec4::operator[](int a_Index) const
{
	return v[a_Index];
}

float & vec4::operator[](int a_Index)
{
	return v[a_Index];
}

vec4 & vec4::normalize()
{
	float l = length();
	if (m_X != 0) {
		m_X /= l;
	}
	if (m_Y != 0) {
		m_Y /= l;
	}
	if (m_Z != 0) {
		m_Z /= l;
	}
	if (m_W != 0) {
		m_W /= l;
	}
	return *this;
}

float vec4::length() const
{
	return sqrt(m_X * m_X + m_Y * m_Y + m_Z * m_Z + m_W * m_W);
}

vec4 operator+(const vec4 & a_Lhs, const vec4 & a_Rhs)
{
	return vec4(
		a_Lhs.m_X + a_Rhs.m_X,
		a_Lhs.m_Y + a_Rhs.m_Y,
		a_Lhs.m_Z + a_Rhs.m_Z,
		a_Lhs.m_W + a_Rhs.m_W);
}

vec4 operator-(const vec4 & a_Lhs, const vec4 & a_Rhs)
{
	return vec4(
		a_Lhs.m_X - a_Rhs.m_X,
		a_Lhs.m_Y - a_Rhs.m_Y,
		a_Lhs.m_Z - a_Rhs.m_Z,
		a_Lhs.m_W - a_Rhs.m_W);
}

vec4 operator*(const vec4 & a_Lhs, float a_Rhs)
{
	return vec4(
		a_Lhs.m_X * a_Rhs,
		a_Lhs.m_Y * a_Rhs,
		a_Lhs.m_Z * a_Rhs,
		a_Lhs.m_W * a_Rhs);
}

vec4 operator*(const vec4 & a_Lhs, const vec4 & a_Rhs)
{
	return vec4(
		a_Lhs.m_X * a_Rhs.m_X,
		a_Lhs.m_Y * a_Rhs.m_Y,
		a_Lhs.m_Z * a_Rhs.m_Z,
		a_Lhs.m_W * a_Rhs.m_W);
}

vec4 operator/(const vec4 & a_Lhs, float a_Rhs)
{
	return vec4(
		a_Lhs.m_X / a_Rhs,
		a_Lhs.m_Y / a_Rhs,
		a_Lhs.m_Z / a_Rhs,
		a_Lhs.m_W / a_Rhs);
}

bool operator==(const vec4 & a_Lhs, const vec4 & a_Rhs)
{
	return (a_Lhs.m_X == a_Rhs.m_X && a_Lhs.m_Y == a_Rhs.m_Y && a_Lhs.m_Z == a_Rhs.m_Z && a_Lhs.m_W == a_Rhs.m_W);
}

bool operator!=(const vec4 & a_Lhs, const vec4 & a_Rhs)
{
	return (a_Lhs.m_X != a_Rhs.m_X || a_Lhs.m_Y != a_Rhs.m_Y || a_Lhs.m_Z != a_Rhs.m_Z || a_Lhs.m_W != a_Rhs.m_W);
}

mat2::mat2()
{
	m_00 = 0; m_01 = 0;
	m_10 = 0; m_11 = 0;
}

mat2::mat2(vec2 a_Row0, vec2 a_Row1)
{
	m_00 = a_Row0.m_X; m_01 = a_Row0.m_Y;
	m_10 = a_Row1.m_X; m_11 = a_Row1.m_Y;
}

mat2::mat2(float a_00, float a_01, float a_10, float a_11)
{
	m_00 = a_00; m_01 = a_01;
	m_10 = a_10; m_11 = a_11;
}

mat2 & mat2::operator=(const mat2 & rhs)
{
	m_00 = rhs.m_00; m_01 = rhs.m_01;
	m_10 = rhs.m_10; m_11 = rhs.m_11;
	return *this;
}

float mat2::determinant() const
{
	return m_00 * m_11 - m_01 * m_10;
}

mat2 mat2::identity()
{
	return mat2(
		1, 0,
		0, 1);
}


mat3::mat3()
{
	m_00 = 0; m_01 = 0; m_02 = 0;
	m_10 = 0; m_11 = 0; m_12 = 0;
	m_20 = 0; m_21 = 0; m_22 = 0;
}

mat3::mat3(vec3 a_Row0, vec3 a_Row1, vec3 a_Row2)
{
	m_00 = a_Row0.m_X; m_01 = a_Row0.m_Y; m_02 = a_Row0.m_Z;
	m_10 = a_Row1.m_X; m_11 = a_Row1.m_Y; m_12 = a_Row1.m_Z;
	m_20 = a_Row2.m_X; m_21 = a_Row2.m_Y; m_22 = a_Row2.m_Z;
}

mat3::mat3(float a_00, float a_01, float a_02, float a_10, float a_11, float a_12, float a_20, float a_21, float a_22)
{
	m_00 = a_00; m_01 = a_01; m_02 = a_02;
	m_10 = a_10; m_11 = a_11; m_12 = a_12;
	m_20 = a_20; m_21 = a_21; m_22 = a_22;
}

mat3 & mat3::operator=(const mat3 & rhs)
{
	m_00 = rhs.m_00; m_01 = rhs.m_01; m_02 = rhs.m_02;
	m_10 = rhs.m_10; m_11 = rhs.m_11; m_12 = rhs.m_12;
	m_20 = rhs.m_20; m_21 = rhs.m_21; m_22 = rhs.m_22;
	return *this;
}

float mat3::determinant() const
{
	float deteriminant = 0.0f;
	mat2 subMatrix;

	subMatrix.m_00 = m_11; subMatrix.m_01 = m_12;
	subMatrix.m_10 = m_21; subMatrix.m_11 = m_22;
	deteriminant += m_00 * subMatrix.determinant();

	subMatrix.m_00 = m_10; subMatrix.m_01 = m_12;
	subMatrix.m_10 = m_20; subMatrix.m_11 = m_22;
	deteriminant -= m_01 * subMatrix.determinant();

	subMatrix.m_00 = m_10; subMatrix.m_01 = m_11;
	subMatrix.m_10 = m_20; subMatrix.m_11 = m_21;
	deteriminant += m_02 * subMatrix.determinant();

	return deteriminant;
}

mat3 mat3::identity()
{
	return mat3(
		1, 0, 0,
		0, 1, 0,
		0, 0, 1);
}


mat4::mat4()
{
	m_00 = 0; m_01 = 0; m_02 = 0; m_03 = 0;
	m_10 = 0; m_11 = 0; m_12 = 0; m_13 = 0;
	m_20 = 0; m_21 = 0; m_22 = 0; m_23 = 0;
	m_30 = 0; m_31 = 0; m_32 = 0; m_33 = 0;
}

mat4::mat4(vec3 a_Row0, float a_03, vec3 a_Row1, float a_13, vec3 a_Row2, float a_23, vec3 a_Row3, float a_33)
{
	m_00 = a_Row0.m_X; m_01 = a_Row0.m_Y; m_02 = a_Row0.m_Z; m_03 = a_03;
	m_10 = a_Row1.m_X; m_11 = a_Row1.m_Y; m_12 = a_Row1.m_Z; m_13 = a_13;
	m_20 = a_Row2.m_X; m_21 = a_Row2.m_Y; m_22 = a_Row2.m_Z; m_23 = a_23;
	m_30 = a_Row3.m_X; m_31 = a_Row3.m_Y; m_32 = a_Row3.m_Z; m_33 = a_33;
}

mat4::mat4(float a_00, float a_01, float a_02, float a_03, float a_10, float a_11, float a_12, float a_13, float a_20, float a_21, float a_22, float a_23, float a_30, float a_31, float a_32, float a_33)
{
	m_00 = a_00; m_01 = a_01; m_02 = a_02; m_03 = a_03;
	m_10 = a_10; m_11 = a_11; m_12 = a_12; m_13 = a_13;
	m_20 = a_20; m_21 = a_21; m_22 = a_22; m_23 = a_23;
	m_30 = a_30; m_31 = a_31; m_32 = a_32; m_33 = a_33;
}

mat4 & mat4::operator=(const mat4 & rhs)
{
	m_00 = rhs.m_00; m_01 = rhs.m_01; m_02 = rhs.m_02; m_03 = rhs.m_03;
	m_10 = rhs.m_10; m_11 = rhs.m_11; m_12 = rhs.m_12; m_13 = rhs.m_13;
	m_20 = rhs.m_20; m_21 = rhs.m_21; m_22 = rhs.m_22; m_23 = rhs.m_23;
	m_30 = rhs.m_30; m_31 = rhs.m_31; m_32 = rhs.m_32; m_33 = rhs.m_33;
	return *this;
}

mat4 & mat4::operator+=(const mat4 & a_Rhs)
{
	m_00 += a_Rhs.m_00; m_01 += a_Rhs.m_01; m_02 += a_Rhs.m_02; m_03 += a_Rhs.m_03;
	m_10 += a_Rhs.m_10; m_11 += a_Rhs.m_11; m_12 += a_Rhs.m_12; m_13 += a_Rhs.m_13;
	m_20 += a_Rhs.m_20; m_21 += a_Rhs.m_21; m_22 += a_Rhs.m_22; m_23 += a_Rhs.m_23;
	m_30 += a_Rhs.m_30; m_31 += a_Rhs.m_31; m_32 += a_Rhs.m_32; m_33 += a_Rhs.m_33;
	return *this;
}

mat4 & mat4::operator-=(const mat4 & a_Rhs)
{
	m_00 -= a_Rhs.m_00; m_01 -= a_Rhs.m_01; m_02 -= a_Rhs.m_02; m_03 -= a_Rhs.m_03;
	m_10 -= a_Rhs.m_10; m_11 -= a_Rhs.m_11; m_12 -= a_Rhs.m_12; m_13 -= a_Rhs.m_13;
	m_20 -= a_Rhs.m_20; m_21 -= a_Rhs.m_21; m_22 -= a_Rhs.m_22; m_23 -= a_Rhs.m_23;
	m_30 -= a_Rhs.m_30; m_31 -= a_Rhs.m_31; m_32 -= a_Rhs.m_32; m_33 -= a_Rhs.m_33;
	return *this;
}

mat4 & mat4::operator*=(const mat4 & a_Rhs)
{
	float element0, element1, element2, element3;

	element0 = m_00 * a_Rhs.m_00 + m_01 * a_Rhs.m_10 + m_02 * a_Rhs.m_20 + m_03 * a_Rhs.m_30;
	element1 = m_00 * a_Rhs.m_01 + m_01 * a_Rhs.m_11 + m_02 * a_Rhs.m_21 + m_03 * a_Rhs.m_31;
	element2 = m_00 * a_Rhs.m_02 + m_01 * a_Rhs.m_12 + m_02 * a_Rhs.m_22 + m_03 * a_Rhs.m_32;
	element3 = m_00 * a_Rhs.m_03 + m_01 * a_Rhs.m_13 + m_02 * a_Rhs.m_23 + m_03 * a_Rhs.m_33;
	m_00 = element0;	m_01 = element1;	m_02 = element2;	m_03 = element3;

	element0 = m_10 * a_Rhs.m_00 + m_11 * a_Rhs.m_10 + m_12 * a_Rhs.m_20 + m_13 * a_Rhs.m_30;
	element1 = m_10 * a_Rhs.m_01 + m_11 * a_Rhs.m_11 + m_12 * a_Rhs.m_21 + m_13 * a_Rhs.m_31;
	element2 = m_10 * a_Rhs.m_02 + m_11 * a_Rhs.m_12 + m_12 * a_Rhs.m_22 + m_13 * a_Rhs.m_32;
	element3 = m_10 * a_Rhs.m_03 + m_11 * a_Rhs.m_13 + m_12 * a_Rhs.m_23 + m_13 * a_Rhs.m_33;
	m_10 = element0;	m_11 = element1;	m_12 = element2;	m_13 = element3;

	element0 = m_20 * a_Rhs.m_00 + m_21 * a_Rhs.m_10 + m_22 * a_Rhs.m_20 + m_23 * a_Rhs.m_30;
	element1 = m_20 * a_Rhs.m_01 + m_21 * a_Rhs.m_11 + m_22 * a_Rhs.m_21 + m_23 * a_Rhs.m_31;
	element2 = m_20 * a_Rhs.m_02 + m_21 * a_Rhs.m_12 + m_22 * a_Rhs.m_22 + m_23 * a_Rhs.m_32;
	element3 = m_20 * a_Rhs.m_03 + m_21 * a_Rhs.m_13 + m_22 * a_Rhs.m_23 + m_23 * a_Rhs.m_33;
	m_20 = element0;	m_21 = element1;	m_22 = element2;	m_23 = element3;

	element0 = m_30 * a_Rhs.m_00 + m_31 * a_Rhs.m_10 + m_32 * a_Rhs.m_20 + m_33 * a_Rhs.m_30;
	element1 = m_30 * a_Rhs.m_01 + m_31 * a_Rhs.m_11 + m_32 * a_Rhs.m_21 + m_33 * a_Rhs.m_31;
	element2 = m_30 * a_Rhs.m_02 + m_31 * a_Rhs.m_12 + m_32 * a_Rhs.m_22 + m_33 * a_Rhs.m_32;
	element3 = m_30 * a_Rhs.m_03 + m_31 * a_Rhs.m_13 + m_32 * a_Rhs.m_23 + m_33 * a_Rhs.m_33;
	m_30 = element0;	m_31 = element1;	m_32 = element2;	m_33 = element3;
	return *this;
}

float mat4::operator[](int a_Index) const
{
	return m[a_Index];
}

float & mat4::operator[](int a_Index)
{
	return m[a_Index];
}

float mat4::determinant() const
{
	float deteriminant = 0.0f;
	mat3 subMatrix;

	subMatrix.m_00 = m_11; subMatrix.m_01 = m_12; subMatrix.m_02 = m_13;
	subMatrix.m_10 = m_21; subMatrix.m_11 = m_22; subMatrix.m_12 = m_23;
	subMatrix.m_20 = m_31; subMatrix.m_21 = m_32; subMatrix.m_22 = m_33;
	deteriminant += m_00 * subMatrix.determinant();

	subMatrix.m_00 = m_10; subMatrix.m_01 = m_12; subMatrix.m_02 = m_13;
	subMatrix.m_10 = m_20; subMatrix.m_11 = m_22; subMatrix.m_12 = m_23;
	subMatrix.m_20 = m_30; subMatrix.m_21 = m_32; subMatrix.m_22 = m_33;
	deteriminant -= m_01 * subMatrix.determinant();

	subMatrix.m_00 = m_10; subMatrix.m_01 = m_11; subMatrix.m_02 = m_13;
	subMatrix.m_10 = m_20; subMatrix.m_11 = m_21; subMatrix.m_12 = m_23;
	subMatrix.m_20 = m_30; subMatrix.m_21 = m_31; subMatrix.m_22 = m_33;
	deteriminant += m_02 * subMatrix.determinant();

	subMatrix.m_00 = m_10; subMatrix.m_01 = m_11; subMatrix.m_02 = m_12;
	subMatrix.m_10 = m_20; subMatrix.m_11 = m_21; subMatrix.m_12 = m_22;
	subMatrix.m_20 = m_30; subMatrix.m_21 = m_31; subMatrix.m_22 = m_32;
	deteriminant -= m_03 * subMatrix.determinant();

	return deteriminant;
}

mat4 & mat4::inverse()
{
	float determinant;
	mat3 subMatrix;
	mat4 matrixOfMinors;
	// Row1
	subMatrix.m_00 = m_11; subMatrix.m_01 = m_12; subMatrix.m_02 = m_13;
	subMatrix.m_10 = m_21; subMatrix.m_11 = m_22; subMatrix.m_12 = m_23;
	subMatrix.m_20 = m_31; subMatrix.m_21 = m_32; subMatrix.m_22 = m_33;
	matrixOfMinors.m_00 = subMatrix.determinant();

	subMatrix.m_00 = m_10; subMatrix.m_01 = m_12; subMatrix.m_02 = m_13;
	subMatrix.m_10 = m_20; subMatrix.m_11 = m_22; subMatrix.m_12 = m_23;
	subMatrix.m_20 = m_30; subMatrix.m_21 = m_32; subMatrix.m_22 = m_33;
	matrixOfMinors.m_01 = subMatrix.determinant();

	subMatrix.m_00 = m_10; subMatrix.m_01 = m_11; subMatrix.m_02 = m_13;
	subMatrix.m_10 = m_20; subMatrix.m_11 = m_21; subMatrix.m_12 = m_23;
	subMatrix.m_20 = m_30; subMatrix.m_21 = m_31; subMatrix.m_22 = m_33;
	matrixOfMinors.m_02 = subMatrix.determinant();

	subMatrix.m_00 = m_10; subMatrix.m_01 = m_11; subMatrix.m_02 = m_12;
	subMatrix.m_10 = m_20; subMatrix.m_11 = m_21; subMatrix.m_12 = m_22;
	subMatrix.m_20 = m_30; subMatrix.m_21 = m_31; subMatrix.m_22 = m_32;
	matrixOfMinors.m_03 = subMatrix.determinant();
	// Calculate the determinant of this matrix
	determinant = m_00 * matrixOfMinors.m_00 - m_01 * matrixOfMinors.m_01 + m_02 * matrixOfMinors.m_02 - m_03 * matrixOfMinors.m_03;
	// If the determinant equals zero then return otherwise you will get values being -nan(id)
	if (determinant == 0.0f) {
		return *this;
	}
	//Row2
	subMatrix.m_00 = m_01; subMatrix.m_01 = m_02; subMatrix.m_02 = m_03;
	subMatrix.m_10 = m_21; subMatrix.m_11 = m_22; subMatrix.m_12 = m_23;
	subMatrix.m_20 = m_31; subMatrix.m_21 = m_32; subMatrix.m_22 = m_33;
	matrixOfMinors.m_10 = subMatrix.determinant();

	subMatrix.m_00 = m_00; subMatrix.m_01 = m_02; subMatrix.m_02 = m_03;
	subMatrix.m_10 = m_20; subMatrix.m_11 = m_22; subMatrix.m_12 = m_23;
	subMatrix.m_20 = m_30; subMatrix.m_21 = m_32; subMatrix.m_22 = m_33;
	matrixOfMinors.m_11 = subMatrix.determinant();

	subMatrix.m_00 = m_00; subMatrix.m_01 = m_01; subMatrix.m_02 = m_03;
	subMatrix.m_10 = m_20; subMatrix.m_11 = m_21; subMatrix.m_12 = m_23;
	subMatrix.m_20 = m_30; subMatrix.m_21 = m_31; subMatrix.m_22 = m_33;
	matrixOfMinors.m_12 = subMatrix.determinant();

	subMatrix.m_00 = m_00; subMatrix.m_01 = m_01; subMatrix.m_02 = m_02;
	subMatrix.m_10 = m_20; subMatrix.m_11 = m_21; subMatrix.m_12 = m_22;
	subMatrix.m_20 = m_30; subMatrix.m_21 = m_31; subMatrix.m_22 = m_32;
	matrixOfMinors.m_13 = subMatrix.determinant();
	//Row3
	subMatrix.m_00 = m_01; subMatrix.m_01 = m_02; subMatrix.m_02 = m_03;
	subMatrix.m_10 = m_11; subMatrix.m_11 = m_12; subMatrix.m_12 = m_13;
	subMatrix.m_20 = m_31; subMatrix.m_21 = m_32; subMatrix.m_22 = m_33;
	matrixOfMinors.m_20 = subMatrix.determinant();

	subMatrix.m_00 = m_00; subMatrix.m_01 = m_02; subMatrix.m_02 = m_03;
	subMatrix.m_10 = m_10; subMatrix.m_11 = m_12; subMatrix.m_12 = m_13;
	subMatrix.m_20 = m_30; subMatrix.m_21 = m_32; subMatrix.m_22 = m_33;
	matrixOfMinors.m_21 = subMatrix.determinant();

	subMatrix.m_00 = m_00; subMatrix.m_01 = m_01; subMatrix.m_02 = m_03;
	subMatrix.m_10 = m_10; subMatrix.m_11 = m_11; subMatrix.m_12 = m_13;
	subMatrix.m_20 = m_30; subMatrix.m_21 = m_31; subMatrix.m_22 = m_33;
	matrixOfMinors.m_22 = subMatrix.determinant();

	subMatrix.m_00 = m_00; subMatrix.m_01 = m_01; subMatrix.m_02 = m_02;
	subMatrix.m_10 = m_10; subMatrix.m_11 = m_11; subMatrix.m_12 = m_12;
	subMatrix.m_20 = m_30; subMatrix.m_21 = m_31; subMatrix.m_22 = m_32;
	matrixOfMinors.m_23 = subMatrix.determinant();
	//Row4
	subMatrix.m_00 = m_01; subMatrix.m_01 = m_02; subMatrix.m_02 = m_03;
	subMatrix.m_10 = m_11; subMatrix.m_11 = m_12; subMatrix.m_12 = m_13;
	subMatrix.m_20 = m_21; subMatrix.m_21 = m_22; subMatrix.m_22 = m_23;
	matrixOfMinors.m_30 = subMatrix.determinant();

	subMatrix.m_00 = m_00; subMatrix.m_01 = m_02; subMatrix.m_02 = m_03;
	subMatrix.m_10 = m_10; subMatrix.m_11 = m_12; subMatrix.m_12 = m_13;
	subMatrix.m_20 = m_20; subMatrix.m_21 = m_22; subMatrix.m_22 = m_23;
	matrixOfMinors.m_31 = subMatrix.determinant();

	subMatrix.m_00 = m_00; subMatrix.m_01 = m_01; subMatrix.m_02 = m_03;
	subMatrix.m_10 = m_10; subMatrix.m_11 = m_11; subMatrix.m_12 = m_13;
	subMatrix.m_20 = m_20; subMatrix.m_21 = m_21; subMatrix.m_22 = m_23;
	matrixOfMinors.m_32 = subMatrix.determinant();

	subMatrix.m_00 = m_00; subMatrix.m_01 = m_01; subMatrix.m_02 = m_02;
	subMatrix.m_10 = m_10; subMatrix.m_11 = m_11; subMatrix.m_12 = m_12;
	subMatrix.m_20 = m_20; subMatrix.m_21 = m_21; subMatrix.m_22 = m_22;
	matrixOfMinors.m_33 = subMatrix.determinant();

	mat4& matrixOfCofactors = matrixOfMinors;
	matrixOfCofactors.m_01 *= -1; matrixOfCofactors.m_03 *= -1;
	matrixOfCofactors.m_10 *= -1; matrixOfCofactors.m_12 *= -1;
	matrixOfCofactors.m_21 *= -1; matrixOfCofactors.m_23 *= -1;
	matrixOfCofactors.m_30 *= -1; matrixOfCofactors.m_32 *= -1;

	mat4& matrixAdjugate = matrixOfCofactors.transpose();

	m_00 = 1.0f / determinant * matrixAdjugate.m_00; m_01 = 1.0f / determinant * matrixAdjugate.m_01; m_02 = 1.0f / determinant * matrixAdjugate.m_02; m_03 = 1.0f / determinant * matrixAdjugate.m_03;
	m_10 = 1.0f / determinant * matrixAdjugate.m_10; m_11 = 1.0f / determinant * matrixAdjugate.m_11; m_12 = 1.0f / determinant * matrixAdjugate.m_12; m_13 = 1.0f / determinant * matrixAdjugate.m_13;
	m_20 = 1.0f / determinant * matrixAdjugate.m_20; m_21 = 1.0f / determinant * matrixAdjugate.m_21; m_22 = 1.0f / determinant * matrixAdjugate.m_22; m_23 = 1.0f / determinant * matrixAdjugate.m_23;
	m_30 = 1.0f / determinant * matrixAdjugate.m_30; m_31 = 1.0f / determinant * matrixAdjugate.m_31; m_32 = 1.0f / determinant * matrixAdjugate.m_32; m_33 = 1.0f / determinant * matrixAdjugate.m_33;
	return *this;
}

mat4 & mat4::transpose()
{
	float value1, value2;
	value1 = m_01; value2 = m_10; m_01 = value2; m_10 = value1;
	value1 = m_02; value2 = m_20; m_02 = value2; m_20 = value1;
	value1 = m_03; value2 = m_30; m_03 = value2; m_30 = value1;
	value1 = m_12; value2 = m_21; m_12 = value2; m_21 = value1;
	value1 = m_13; value2 = m_31; m_13 = value2; m_31 = value1;
	value1 = m_23; value2 = m_32; m_23 = value2; m_32 = value1;
	return *this;
}

mat4 mat4::identity()
{
	return mat4(
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1);
}

mat4 & mat4::rotateX(float a_Radians)
{
	m_11 = std::cos(a_Radians);
	m_12 = -std::sin(a_Radians);
	m_21 = std::sin(a_Radians);
	m_22 = std::cos(a_Radians);
	return *this;
}

mat4 & mat4::rotateY(float a_Radians)
{
	m_00 = std::cos(a_Radians);
	m_02 = std::sin(a_Radians);
	m_20 = -std::sin(a_Radians);
	m_22 = std::cos(a_Radians);
	return *this;
}

mat4 & mat4::rotateZ(float a_Radians)
{
	m_00 = std::cos(a_Radians);
	m_01 = -std::sin(a_Radians);
	m_10 = std::sin(a_Radians);
	m_11 = std::cos(a_Radians);
	return *this;
}

mat4 & mat4::translate(const vec3 & a_Translation)
{
	m_03 = a_Translation.m_X;
	m_13 = a_Translation.m_Y;
	m_23 = a_Translation.m_Z;
	return *this;
}

mat4 operator+(const mat4 & a_Lhs, const mat4 & a_Rhs)
{
	return mat4(
		a_Lhs.m_00 + a_Rhs.m_00, a_Lhs.m_01 + a_Rhs.m_01, a_Lhs.m_02 + a_Rhs.m_02, a_Lhs.m_03 + a_Rhs.m_03,
		a_Lhs.m_10 + a_Rhs.m_10, a_Lhs.m_11 + a_Rhs.m_11, a_Lhs.m_12 + a_Rhs.m_12, a_Lhs.m_13 + a_Rhs.m_13,
		a_Lhs.m_20 + a_Rhs.m_20, a_Lhs.m_21 + a_Rhs.m_21, a_Lhs.m_22 + a_Rhs.m_22, a_Lhs.m_23 + a_Rhs.m_23,
		a_Lhs.m_30 + a_Rhs.m_30, a_Lhs.m_31 + a_Rhs.m_31, a_Lhs.m_32 + a_Rhs.m_32, a_Lhs.m_33 + a_Rhs.m_33);
}

mat4 operator-(const mat4 & a_Lhs, const mat4 & a_Rhs)
{
	return mat4(
		a_Lhs.m_00 - a_Rhs.m_00, a_Lhs.m_01 - a_Rhs.m_01, a_Lhs.m_02 - a_Rhs.m_02, a_Lhs.m_03 - a_Rhs.m_03,
		a_Lhs.m_10 - a_Rhs.m_10, a_Lhs.m_11 - a_Rhs.m_11, a_Lhs.m_12 - a_Rhs.m_12, a_Lhs.m_13 - a_Rhs.m_13,
		a_Lhs.m_20 - a_Rhs.m_20, a_Lhs.m_21 - a_Rhs.m_21, a_Lhs.m_22 - a_Rhs.m_22, a_Lhs.m_23 - a_Rhs.m_23,
		a_Lhs.m_30 - a_Rhs.m_30, a_Lhs.m_31 - a_Rhs.m_31, a_Lhs.m_32 - a_Rhs.m_32, a_Lhs.m_33 - a_Rhs.m_33);
}

mat4 operator*(const mat4 & a_Lhs, const mat4 & a_Rhs)
{
	return mat4(
		a_Lhs.m_00 * a_Rhs.m_00 + a_Lhs.m_01 * a_Rhs.m_10 + a_Lhs.m_02 * a_Rhs.m_20 + a_Lhs.m_03 * a_Rhs.m_30,
		a_Lhs.m_00 * a_Rhs.m_01 + a_Lhs.m_01 * a_Rhs.m_11 + a_Lhs.m_02 * a_Rhs.m_21 + a_Lhs.m_03 * a_Rhs.m_31,
		a_Lhs.m_00 * a_Rhs.m_02 + a_Lhs.m_01 * a_Rhs.m_12 + a_Lhs.m_02 * a_Rhs.m_22 + a_Lhs.m_03 * a_Rhs.m_32,
		a_Lhs.m_00 * a_Rhs.m_03 + a_Lhs.m_01 * a_Rhs.m_13 + a_Lhs.m_02 * a_Rhs.m_23 + a_Lhs.m_03 * a_Rhs.m_33,

		a_Lhs.m_10 * a_Rhs.m_00 + a_Lhs.m_11 * a_Rhs.m_10 + a_Lhs.m_12 * a_Rhs.m_20 + a_Lhs.m_13 * a_Rhs.m_30,
		a_Lhs.m_10 * a_Rhs.m_01 + a_Lhs.m_11 * a_Rhs.m_11 + a_Lhs.m_12 * a_Rhs.m_21 + a_Lhs.m_13 * a_Rhs.m_31,
		a_Lhs.m_10 * a_Rhs.m_02 + a_Lhs.m_11 * a_Rhs.m_12 + a_Lhs.m_12 * a_Rhs.m_22 + a_Lhs.m_13 * a_Rhs.m_32,
		a_Lhs.m_10 * a_Rhs.m_03 + a_Lhs.m_11 * a_Rhs.m_13 + a_Lhs.m_12 * a_Rhs.m_23 + a_Lhs.m_13 * a_Rhs.m_33,

		a_Lhs.m_20 * a_Rhs.m_00 + a_Lhs.m_21 * a_Rhs.m_10 + a_Lhs.m_22 * a_Rhs.m_20 + a_Lhs.m_23 * a_Rhs.m_30,
		a_Lhs.m_20 * a_Rhs.m_01 + a_Lhs.m_21 * a_Rhs.m_11 + a_Lhs.m_22 * a_Rhs.m_21 + a_Lhs.m_23 * a_Rhs.m_31,
		a_Lhs.m_20 * a_Rhs.m_02 + a_Lhs.m_21 * a_Rhs.m_12 + a_Lhs.m_22 * a_Rhs.m_22 + a_Lhs.m_23 * a_Rhs.m_32,
		a_Lhs.m_20 * a_Rhs.m_03 + a_Lhs.m_21 * a_Rhs.m_13 + a_Lhs.m_22 * a_Rhs.m_23 + a_Lhs.m_23 * a_Rhs.m_33,

		a_Lhs.m_30 * a_Rhs.m_00 + a_Lhs.m_31 * a_Rhs.m_10 + a_Lhs.m_32 * a_Rhs.m_20 + a_Lhs.m_33 * a_Rhs.m_30,
		a_Lhs.m_30 * a_Rhs.m_01 + a_Lhs.m_31 * a_Rhs.m_11 + a_Lhs.m_32 * a_Rhs.m_21 + a_Lhs.m_33 * a_Rhs.m_31,
		a_Lhs.m_30 * a_Rhs.m_02 + a_Lhs.m_31 * a_Rhs.m_12 + a_Lhs.m_32 * a_Rhs.m_22 + a_Lhs.m_33 * a_Rhs.m_32,
		a_Lhs.m_30 * a_Rhs.m_03 + a_Lhs.m_31 * a_Rhs.m_13 + a_Lhs.m_32 * a_Rhs.m_23 + a_Lhs.m_33 * a_Rhs.m_33);
}

vec4 operator*(const mat4 & a_Lhs, const vec4 & a_Rhs)
{
	return vec4(
		a_Lhs.m_00 * a_Rhs.m_X + a_Lhs.m_01 * a_Rhs.m_Y + a_Lhs.m_02 * a_Rhs.m_Z + a_Lhs.m_03 * a_Rhs.m_W,
		a_Lhs.m_10 * a_Rhs.m_X + a_Lhs.m_11 * a_Rhs.m_Y + a_Lhs.m_12 * a_Rhs.m_Z + a_Lhs.m_13 * a_Rhs.m_W,
		a_Lhs.m_20 * a_Rhs.m_X + a_Lhs.m_21 * a_Rhs.m_Y + a_Lhs.m_22 * a_Rhs.m_Z + a_Lhs.m_23 * a_Rhs.m_W,
		a_Lhs.m_30 * a_Rhs.m_X + a_Lhs.m_31 * a_Rhs.m_Y + a_Lhs.m_32 * a_Rhs.m_Z + a_Lhs.m_33 * a_Rhs.m_W);
}
