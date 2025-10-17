
#include "controller.h"
#include <iostream>
#include <string>


void Controller::get_direction(const SDL_Event * event)
{

	if (event->key.type == SDL_EVENT_KEY_DOWN && !keyPressed) {
		
		if (event->key.scancode == SDL_SCANCODE_W) {
			keyDirection[0] = UP;
		}
		if (event->key.scancode == SDL_SCANCODE_S) {
			keyDirection[1] = DOWN;
		}
		if (event->key.scancode == SDL_SCANCODE_A) {
			keyDirection[2] = LEFT;
		}
		if (event->key.scancode == SDL_SCANCODE_D) {
			keyDirection[3] = RIGHT;
		}
		if (event->key.scancode == SDL_SCANCODE_Q) {
			keyDirection[4] = TOPLEFT;
		}
		if (event->key.scancode == SDL_SCANCODE_E) {
			keyDirection[5] = TOPRIGHT;
		}
		if (event->key.scancode == SDL_SCANCODE_UP) {
			keyDirection[6] = UP_ARROW;
		}
		if (event->key.scancode == SDL_SCANCODE_DOWN) {
			keyDirection[7] = DOWN_ARROW;
		}
		if (event->key.scancode == SDL_SCANCODE_LEFT) {
			keyDirection[8] = LEFT_ARROW;
		}
		if (event->key.scancode == SDL_SCANCODE_RIGHT) {
			keyDirection[9] = RIGHT_ARROW;
		}
		keyPressed = true;
	}
	return;
}

void Controller::clear(const SDL_Event* event) {
	if (event->key.type == SDL_EVENT_KEY_UP) {
		x_pos = 0;
		y_pos = 0;
		z_pos = 0;
		x_axis = 0;
		y_axis = 0;
		z_axis = 0;
		memset(keyDirection, 0, sizeof(keyDirection));
		keyPressed = false;
	}
}

void Controller::update_pos(double deltaTime) {

	for (int i = 0; i < direction_count; i++) {
		if (keyDirection[i] == UP) {
			y_pos = 0.1 * deltaTime;
		}
		if (keyDirection[i] == DOWN) {
			y_pos = -0.1 * deltaTime;
		}
		if (keyDirection[i] == LEFT) {
			x_pos = -0.1 * deltaTime;
		}
		if (keyDirection[i] == RIGHT) {
			x_pos = 0.1 * deltaTime;
		}

		if (keyDirection[i] == UP_ARROW) {
			z_axis = 0.005 * deltaTime;
		}
		if (keyDirection[i] == DOWN_ARROW) {
			z_axis = -0.005 * deltaTime;
		}
		if (keyDirection[i] == LEFT_ARROW) {
			x_axis = 0.005 * deltaTime;
		}
		if (keyDirection[i] == RIGHT_ARROW) {
			x_axis = -0.005 * deltaTime;
		}

		if (keyDirection[i] == TOPLEFT) {
			y_axis = 0.005 * deltaTime;
		}
		if (keyDirection[i] == TOPRIGHT) {
			y_axis = -0.005 * deltaTime;
		}
	}
	return;
}

bool Controller::zoom(const SDL_Event* event, double deltaTime) {
	if (event->type == SDL_EVENT_MOUSE_WHEEL){
		if (event->wheel.y > 0) {
			z_pos = 0.5 * deltaTime;
			return true;
		}
		else if (event->wheel.y < 0) {
			z_pos = -0.5 * deltaTime;
			return true;
		}
	}
	return false;
}