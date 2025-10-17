#include "graphics.h"
#include "models.h"
#include <vector>
#include <iostream>

void Graphics::get_transform(double theta, double alfa, double beta) {

	double transform[4][4] =   { { 2 / (r - l),		   0.0, 0.0,	  -1 * ((r + l) / (r - l))}
								,{ 0.0,			2 / (t - b), 0.0,	      -1 * ((t + b) / (t - b))}
								,{ 0.0,			0.0,	   2 / (f - n), -1 * ((f + n) / (f - n))}
								,{ 0.0,			0.0,	   0.0,	       1					} };

	double rotx_transform[4][4] =  { { 1  ,			0.0,		  0.0,	       0}
									,{ 0.0,			cos(theta)	, sin(theta) , 0}
									,{ 0.0,			-sin(theta) , cos(theta) , 0}
									,{ 0.0,			0		    , 0		     , 1} };

	double roty_transform[4][4] =  { { cos(alfa)  ,	0.0,		  -sin(alfa) , 0}
									,{ 0.0,			1  	,		  0.0		 , 0}
									,{ sin(alfa),	0.0,		  cosf(alfa) , 0}
									,{ 0	   ,	0.0,		  0		     , 1} };

	double rotz_transform[4][4] =  { { cos(beta)  , -sin(beta),	  0.0,		   0}
									,{ sin(beta),	cos(beta)	, 0.0		 , 0}
									,{ 0.0,			0.0 ,		  1			 , 0}
									,{ 0.0,			0.0 ,		  0			 , 1} };
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			itransform[i][j] = transform[i][j];
			xtransform[i][j] = rotx_transform[i][j];
			ytransform[i][j] = roty_transform[i][j];
			ztransform[i][j] = rotz_transform[i][j];
		}
	}
}

void Graphics::apply_transform(std::vector<vector4D> model_vertecies, vector4D origin) {



	std::vector<vector4D> model_matrix;
	
	model_matrix.reserve(model_vertecies.size() * sizeof(vector4D));
	model_matrix = model_vertecies;
	
	vector4D origin_matrix = origin;

	projected.reserve(model_vertecies.size() * sizeof(vector2D));
	get_transform(rotate_x, rotate_y, rotate_z);

	vector4D origin4D = {
		itransform[0][0] * origin_matrix.x +
		itransform[0][1] * origin_matrix.y +
		itransform[0][2] * origin_matrix.z +
		itransform[0][3] * origin_matrix.w ,

		itransform[1][0] * origin_matrix.x +
		itransform[1][1] * origin_matrix.y +
		itransform[1][2] * origin_matrix.z +
		itransform[1][3] * origin_matrix.w ,

		itransform[2][0] * origin_matrix.x +
		itransform[2][1] * origin_matrix.y +
		itransform[2][2] * origin_matrix.z +
		itransform[2][3] * origin_matrix.w ,

		itransform[3][0] * origin_matrix.x +
		itransform[3][1] * origin_matrix.y +
		itransform[3][2] * origin_matrix.z +
		itransform[3][3] * origin_matrix.w };

	for (int i = 0; i < model_matrix.size(); i++) {

		vector4D point4D = {
			itransform[0][0] * model_matrix[i].x +
			itransform[0][1] * model_matrix[i].y +
			itransform[0][2] * model_matrix[i].z +
			itransform[0][3] * model_matrix[i].w ,

			itransform[1][0] * model_matrix[i].x +
			itransform[1][1] * model_matrix[i].y +
			itransform[1][2] * model_matrix[i].z +
			itransform[1][3] * model_matrix[i].w ,

			itransform[2][0] * model_matrix[i].x +
			itransform[2][1] * model_matrix[i].y +
			itransform[2][2] * model_matrix[i].z +
			itransform[2][3] * model_matrix[i].w ,

			itransform[3][0] * model_matrix[i].x +
			itransform[3][1] * model_matrix[i].y +
			itransform[3][2] * model_matrix[i].z +
			itransform[3][3] * model_matrix[i].w };


		vector4D rotated_point4D = apply_rotation(point4D, origin4D);


		vector3D normalized_point3D = {
			rotated_point4D.x / rotated_point4D.w,
			rotated_point4D.y / rotated_point4D.w,
			rotated_point4D.z / rotated_point4D.w
		};


		vector2D point2D = { 1300*(normalized_point3D.x+1)/2, 900*(1-normalized_point3D.y)/2 };
		projected.emplace_back(point2D);

		
	}
	model_matrix.clear();
	

}

vector4D Graphics::apply_rotation(vector4D point4D, vector4D origin4D) {
	point4D.x -= origin4D.x;
	point4D.y -= origin4D.y;
	point4D.z -= origin4D.z;
	point4D.w -= origin4D.z;

	point4D = {
		xtransform[0][0] * point4D.x +
		xtransform[0][1] * point4D.y +
		xtransform[0][2] * point4D.z +
		xtransform[0][3] * point4D.w,

		xtransform[1][0] * point4D.x +
		xtransform[1][1] * point4D.y +
		xtransform[1][2] * point4D.z +
		xtransform[1][3] * point4D.w,

		xtransform[2][0] * point4D.x +
		xtransform[2][1] * point4D.y +
		xtransform[2][2] * point4D.z +
		xtransform[2][3] * point4D.w  ,

		xtransform[3][0] * point4D.x +
		xtransform[3][1] * point4D.y +
		xtransform[3][2] * point4D.z +
		xtransform[3][3] * point4D.w };

	point4D = {
		ytransform[0][0] * point4D.x +
		ytransform[0][1] * point4D.y +
		ytransform[0][2] * point4D.z +
		ytransform[0][3] * point4D.w ,

		ytransform[1][0] * point4D.x +
		ytransform[1][1] * point4D.y +
		ytransform[1][2] * point4D.z +
		ytransform[1][3] * point4D.w ,

		ytransform[2][0] * point4D.x +
		ytransform[2][1] * point4D.y +
		ytransform[2][2] * point4D.z +
		ytransform[2][3] * point4D.w,

		ytransform[3][0] * point4D.x +
		ytransform[3][1] * point4D.y +
		ytransform[3][2] * point4D.z +
		ytransform[3][3] * point4D.w };

	point4D = {
		ztransform[0][0] * point4D.x +
		ztransform[0][1] * point4D.y +
		ztransform[0][2] * point4D.z +
		ztransform[0][3] * point4D.w,

		ztransform[1][0] * point4D.x +
		ztransform[1][1] * point4D.y +
		ztransform[1][2] * point4D.z +
		ztransform[1][3] * point4D.w ,

		ztransform[2][0] * point4D.x +
		ztransform[2][1] * point4D.y +
		ztransform[2][2] * point4D.z +
		ztransform[2][3] * point4D.w ,

		ztransform[3][0] * point4D.x +
		ztransform[3][1] * point4D.y +
		ztransform[3][2] * point4D.z +
		ztransform[3][3] * point4D.w };
	point4D.x += origin4D.x;
	point4D.y += origin4D.y;
	point4D.z += origin4D.z;
	point4D.w += origin4D.z;
	point4D.x += plane_pos.x;
	point4D.y += plane_pos.y;
	point4D.z += plane_pos.z;
	point4D.w += plane_pos.z;

	return point4D;
}



void Graphics::render_simple_wireframe(SDL_Renderer *renderer, Models *model) {
	apply_transform(model->cube, model->origin);
	SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
	vector2D point_last = projected.front();
	for (const auto& point : projected) {
		//std::cout << point.x << "  " << point.y << "\n";
		SDL_RenderLine(renderer, point.x, point.y, point_last.x, point_last.y);
		point_last = point;
	}
	clear(model);
}
void Graphics::render_wireframe(SDL_Renderer* renderer, Models* models) {
	SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
	std::vector<vector4D> vertecies;
	vertecies.reserve(3);
	for (const auto& polygon : models->model) {
		vertecies.clear();
		
		vertecies.emplace_back(polygon.v1);
		vertecies.emplace_back(polygon.v2);
		vertecies.emplace_back(polygon.v3);


		apply_transform(vertecies, models->origin);
		
		vector2D point_last = projected.front();

		for (const auto& point : projected) {
			SDL_RenderLine(renderer, point.x, point.y, point_last.x, point_last.y);
			point_last = point;
		}
		clear(models);
		
	}
}


void Graphics::clear(Models* model) {
	model->cube.clear();
	model->model.clear();
	projected.clear();
}