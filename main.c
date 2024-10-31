#include <SDL.h>
#include <SDL_init.h>
#include <SDL_video.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("Failed video initialization: %s", SDL_GetError());
		return 0;

	}

	SDL_Window *window = SDL_CreateWindow("Back doing SDL :)", 820, 460, SDL_WINDOW_FULLSCREEN);
	if(!window)
	{
		printf("No window created");
		return 0;
	}
	SDL_Delay(3000);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
