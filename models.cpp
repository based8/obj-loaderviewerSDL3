#include "models.h"
#include <iostream>
#include <sstream>



void Models::parse_obj(std::string filename) {
	std::ifstream obj_file(filename);

	if (!obj_file) {
		std::cout << "%s empty or nonexistent" << "\n";
		return;
	}

	
	char buffer[1024];
	char header[128];
	vector4D vertex;
	triangle face;

	int v = 0;
	int f = 0;
	
	while (!obj_file.eof()) {
		obj_file.getline(buffer, sizeof(buffer));
		
		std::istringstream sstream(buffer);
		sstream >> header;

		if (strcmp(header, "v") == 0) {
			v++;
		}
		else if (strcmp(header, "f") == 0) {
			f++;
		}
	}
	std::cout << "Vectors: " << v << "   Triangles: " << f << "\n";
	vertecies.reserve(v * sizeof(vector4D));
	obj_file.close();
	std::ifstream new_obj_file(filename);

	while (!new_obj_file.eof()) {
		new_obj_file.getline(buffer, sizeof(buffer));
		std::istringstream sstream(buffer);
		sstream >> header;

		if (strcmp(header, "v") == 0) {

			sstream >> vertex.x >> vertex.y >> vertex.z;
			vertex.w = 1;
			vertecies.emplace_back(vertex);

		}
		else if (strcmp(header, "f") == 0) {
			int index1, index2, index3;

			sstream >> index1 >> index2 >> index3;

			index1--; index2--; index3--;

			face.v1 = vertecies[index1];
			face.v2 = vertecies[index2];
			face.v3 = vertecies[index3];

			std::cout << vertecies[index1].x << " " << vertecies[index1].y << " " << vertecies[index1].z << "\n";

			faces.emplace_back(face);

		}
	}

}

void Models::create_cube(double x_offset, double y_offset, double z_offset) {
	//obj obj;
	//obj.extract_from_obj("data/teapot.obj");

	vector4D new_cube[18] = {
	{0 + x_offset, 0 + y_offset, 0 + z_offset, 1} ,
	{0 + x_offset, 10 + y_offset, 0 + z_offset, 1} ,
	{10 + x_offset, 10 + y_offset, 0 + z_offset, 1} ,
	{10 + x_offset, 0 + y_offset, 0 + z_offset, 1},

	{0 + x_offset,  0 + y_offset, 0 + z_offset, 1} ,
	{0 + x_offset,  0 + y_offset, 10 + z_offset, 1} ,
	{0 + x_offset,  10 + y_offset, 10 + z_offset, 1} ,
	{0 + x_offset,  10 + y_offset, 0 + z_offset, 1},

	{0 + x_offset, 0 + y_offset, 0 + z_offset, 1} ,
	{0 + x_offset, 0 + y_offset, 10 + z_offset, 1} ,
	{10 + x_offset, 0 + y_offset, 10 + z_offset, 1} ,
	{10 + x_offset, 0 + y_offset, 0 + z_offset, 1},

	{10 + x_offset, 0 + y_offset, 10 + z_offset, 1},
	{10 + x_offset, 10 + y_offset, 10 + z_offset, 1},
	{0 + x_offset, 10 + y_offset, 10 + z_offset, 1},
	{10 + x_offset, 10 + y_offset, 10 + z_offset, 1},
	{10 + x_offset, 10 + y_offset, 0 + z_offset, 1},
	{10 + x_offset, 0 + y_offset, 0 + z_offset, 1},
	};

	vector4D new_origin = {
		5, 5, 5, 1
	};

	origin = new_origin;

	cube.reserve(sizeof(new_cube));
	for (int i = 0; i < 18; i++) {
		cube.emplace_back(new_cube[i]);
	}

	return;
}
void Models::create_plane(double x_offset, double y_offset, double z_offset) {
	vector4D new_plane[5] = {
	{0 + x_offset, 0 + y_offset, 0 + z_offset, 1} ,
	{0 + x_offset, 10 + y_offset, 0 + z_offset, 1} ,
	{10 + x_offset, 10 + y_offset, 0 + z_offset, 1} ,
	{10 + x_offset, 0 + y_offset, 0 + z_offset, 1},
	{0 + x_offset, 0 + y_offset, 0 + z_offset, 1}
	};
	vector4D new_origin = {
		5, 5, 0, 1
	};

	origin = new_origin;

	plane.reserve(sizeof(new_plane));
	for (int i = 0; i < 5; i++) {
		plane.emplace_back(new_plane[i]);
	}

	return;
}

void Models::create_imported_model(double x_offset, double y_offset, double z_offset) {

	triangle _face;
	for (const auto& face : faces) {
		_face = {
			{face.v1.x + x_offset, face.v1.y + y_offset, face.v1.z + z_offset, 1 },
			{face.v2.x + x_offset, face.v2.y + y_offset, face.v2.z + z_offset, 1 },
			{face.v3.x + x_offset, face.v3.y + y_offset, face.v3.z + z_offset, 1} };

		model.emplace_back(face);
	}
	vector4D new_origin = {
	1, 1, 0, 1
	};

	origin = new_origin;

}