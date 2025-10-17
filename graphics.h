#include <SDL3/SDL_render.h>
#include "vectors.h"
#include "models.h"
#include <math.h>

#pragma once

class Graphics {

	std::vector<vector2D> projected;

	double itransform[4][4];
	double xtransform[4][4];
	double ytransform[4][4];
	double ztransform[4][4];

	// clipping planes.
	double r = 2; //right
	double l = 1; //left
	double t = 2; //top
	double b = 1; //bottom
	double f = 2; //far
	double n = 1; //near

	void get_transform(double theta, double alfa, double beta);
	vector4D apply_rotation(vector4D point4D, vector4D origin4D);
	void apply_transform(std::vector<vector4D> model, vector4D origin);

public :
	
	vector3D plane_pos = {10, 10, 10};

	double rotate_x = 0;
	double rotate_y = 0;
	double rotate_z = 0;

	
	void render_simple_wireframe(SDL_Renderer *renderer, Models *model);
	void render_wireframe(SDL_Renderer* renderer, Models* models);

	void clear(Models* model);

};