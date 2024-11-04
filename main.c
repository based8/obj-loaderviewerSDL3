#include <SDL.h>
#include <stdio.h>
#include <pthread.h>

#define BALL_SIZE 20

void *gameloop(void* pass)
{
    SDL_Renderer* renderer = renderer;
    // ballphys {X position, Y position, X velocity, Y velocity}
    int ballphys[4] = {200 - (BALL_SIZE/2), 200 - (BALL_SIZE/2), 1, 1};
    while(true)
    {
        SDL_FRect rect = {ballphys[0], ballphys[1], BALL_SIZE, BALL_SIZE};
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderRect(renderer, &rect);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
        ballphys[0]++;
        SDL_Delay(500);
    }
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

	window = SDL_CreateWindow("Back doing SDL :)", 400, 400, 0);
	if(!window)
	{
		printf("No window created");
		return 0;
	}
    renderer = SDL_CreateRenderer(window,0);

    pthread_t gameThread;    
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
            pthread_create(&gameThread, NULL, gameloop, renderer);
            pthread_join(gameThread, NULL);
        }
    }

	SDL_DestroyWindow(window);
	SDL_Quit();
}
