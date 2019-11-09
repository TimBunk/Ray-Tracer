#pragma once

#include "MathLibrary.h"

struct Ray {
	vec3 m_origin = vec3();
	vec3 m_direction = vec3(0, 0, -1);
};