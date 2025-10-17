#include <SDL3/SDL_events.h>

#pragma once

enum direction {
	UP='W',
	DOWN='S',
	LEFT='A',
	RIGHT='D',
	UP_ARROW = '^',
	DOWN_ARROW = 'u',
	LEFT_ARROW = '<',
	RIGHT_ARROW = '>',
	TOPLEFT='*',
	TOPRIGHT='@',
};
#define direction_count 10

class Controller {
public:

	double x_axis = 0;
	double y_axis = 0;
	double z_axis = 0;

	double x_pos = 0;
	double y_pos = 0;
	double z_pos = 0;

	bool keyPressed = false;
	bool zooming = false;

	void get_direction(const SDL_Event* event);
	bool zoom(const SDL_Event* event, double deltaTime);
	void update_pos(double deltaTime);
	void clear(const SDL_Event* event);

private:
	char keyDirection[direction_count];
};