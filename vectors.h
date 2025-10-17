#include <vector>
#pragma once

struct vector4D {
	double x, y, z, w;
};
struct vector3D {
	double x, y, z;
};
struct vector2D {
	double x, y;
};

struct triangle {
	vector4D v1, v2, v3;
};