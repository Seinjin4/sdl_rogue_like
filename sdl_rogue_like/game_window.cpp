#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <iostream>
#include <stdio.h>

#include "game_window.h"

game_window::game_window()
{
	window = SDL_CreateWindow(
		"SDL Rogue-like",                  // window title
		SDL_WINDOWPOS_UNDEFINED,           // initial x position
		SDL_WINDOWPOS_UNDEFINED,           // initial y position
		window_width,                      // width, in pixels
		window_height,                     // height, in pixels
		SDL_WINDOW_INPUT_FOCUS             // flags - see below
	);

	if (window == NULL) {
		printf("Could not create window: %s\n", SDL_GetError());
		window_closed = true;
		SDL_DestroyWindow(window);
		SDL_Quit();
	}

	if( !(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
	{
		std::cout << "Failed to init SDL_image" << std::endl;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);

	if (renderer == nullptr)
	{
		std::cout << "Failed to create renderer" << std::endl;
	}
}


game_window::~game_window()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	IMG_Quit();
	SDL_Quit();
}

bool game_window::isClosed()
{
	return window_closed;
}

int game_window::getWindowHeight()
{
	return window_height;
}

int game_window::getWindowWidth()
{
	return window_width;
}

void game_window::pollEvent()
{
	SDL_Event event;
	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			window_closed = true;
			break;
		}

		if(event.type == SDL_KEYDOWN)
		{
			switch (event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				SDL_Quit();
				window_closed = true;
				break;
			}
		}

	}
}

void game_window::clear() const
{

	SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
	SDL_RenderPresent(renderer);
	SDL_RenderClear(renderer);
}

SDL_Renderer* game_window::get_renderer()
{
		return renderer;
}
