
#include <SDL3/sdl.h>
#include "controller.h"
#include "graphics.h"
#include "models.h"

#include <iostream>



bool quit_app = false;

//save into json file
#define WINDOW_TITLE "based engine - orthographic"
const int WINDOW_W = 1300;
const int WINDOW_H = 900;



//Show fps and deltaTime and tickspeed
void performance_ui(SDL_Renderer* renderer, Uint32* fps, Uint32* delta) {
}

int main()
{
	Controller controller;
	Graphics graphics;
	Models models;

	models.parse_obj("data/teapot.obj");
	SDL_Window* window = SDL_CreateWindow(WINDOW_TITLE, WINDOW_W, WINDOW_H, 0);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, 0);

	SDL_Event event;

// ADD JSON FILE. Also for the WINDOW_H and WINDOW_W

	double lastTick = SDL_GetTicks();
	double deltaTime = 0;
	int fps_max = 60;
	int frameDelay = 1000 / fps_max;
	int frameCount = 0;
	double fpsTimer = SDL_GetTicks();
	
	// clean up this mess. add update tick functions. Fix the SDL_EVENTS to be better
	while(!quit_app)
	{
		double currentTick = SDL_GetTicks();
		deltaTime = currentTick - lastTick;

		if (deltaTime >= frameDelay) {

			while (SDL_PollEvent(&event) != 0)
			{

				controller.get_direction(&event);
				controller.update_pos(deltaTime);
										
				controller.clear(&event);
				if (controller.zoom(&event, deltaTime)) {
					graphics.plane_pos.z += controller.z_pos;
				}
				if (event.type == SDL_EVENT_QUIT)
				{
					quit_app = true;
				}
			}

				graphics.rotate_x += controller.x_axis;
				graphics.rotate_y += controller.y_axis;
				graphics.rotate_z += controller.z_axis;

				graphics.plane_pos.x += controller.x_pos;
				graphics.plane_pos.y += controller.y_pos;	

			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			SDL_RenderClear(renderer);


			graphics.clear(&models);
			models.create_imported_model(0, 0, 0);
			graphics.render_wireframe(renderer, &models);

			SDL_RenderPresent(renderer);
			frameCount++;
			lastTick = currentTick;

		}

		if (deltaTime < frameDelay) {
			SDL_Delay(frameDelay - deltaTime);
		}
		// find a concrete value for tickspeed
		if (currentTick - fpsTimer >= 64)  {

			std::cout << "FPS: " << frameCount * (1000/64) << std::fixed << "  last frame : " << deltaTime << "ms\n";
			frameCount = 0;
			fpsTimer = currentTick;



			if (controller.keyPressed) {
				
			}

				
		}
	}
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}