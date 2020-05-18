#pragma once

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <stdio.h>

class game_window
{
private:

	SDL_Renderer *renderer;
	const int window_width = 1280;
	const int window_height = 720;

	SDL_Window *window = nullptr;
	bool window_closed = false;

public:
	game_window();
	~game_window();

	void pollEvent();
	void clear() const;

	bool isClosed();
	int getWindowHeight();
	int getWindowWidth();

	SDL_Renderer* get_renderer();

};
