#include <fstream>
#include <string>
#include "vectors.h"

#pragma once

class Models {
	std::vector<vector4D> vertecies;
	std::vector<triangle> faces;
public:
	vector4D origin;
	std::vector<vector4D> cube;
	std::vector<vector4D> plane;
	std::vector<triangle> model;

	void create_cube(double x_offset, double y_offset, double z_offset);
	void create_plane(double x_offset, double y_offset, double z_offset);
	void create_imported_model(double x_offset, double y_offset, double z_offset);

	void parse_obj(std::string filename);

};

