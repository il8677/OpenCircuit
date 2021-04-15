#pragma once
#include <imgui.h>

class ImVec4;

enum DIR {
	UP = 0, RIGHT, DOWN, LEFT
};

template<typename T>
struct vec4
{
	vec4(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) {};

	union {

		struct { T x, y, z, w; };
		struct { T r, g, b, a; };
		struct { T up, right, down, left; };
		T values[4];
	};
};

