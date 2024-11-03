#include <SDL.h>
#include <SDL_init.h>
#include <SDL_video.h>
#include <stdio.h>

void lines(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderLine(renderer, 240,450,400,450);
}

int main(int argc, char* argv[])
{
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Event event;

	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("Failed video initialization: %s", SDL_GetError());
		return 0;

	}

	window = SDL_CreateWindow("Back doing SDL :)", 820, 460, 0);
	if(!window)
	{
		printf("No window created");
		return 0;
	}
    renderer = SDL_CreateRenderer(window,0);
    
    bool quit = false;
    while(!quit)
    {
        while( SDL_PollEvent(&event) != 0)
        {
            if(event.type == SDL_EVENT_QUIT)
            {
                quit = true;
            }
            
            SDL_SetRenderDrawColor(renderer,0,0,0,255);
            SDL_RenderClear(renderer);
            lines(renderer);   
            SDL_RenderPresent(renderer);
   
        }
    }

	SDL_DestroyWindow(window);
	SDL_Quit();
}
