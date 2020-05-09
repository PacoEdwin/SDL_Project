// prject includes
#include "button.h"

// std incldudes
#include <iostream>

// sdl includes
#include <SDL.h>

Button::Button():
	m_pressed(false) {}

void Button::onMouseButtonEvent(SDL_MouseButtonEvent* e)
{
	if (!isPointInside(e->x, e->y))
		return;

	if (e->state == SDL_PRESSED)
		m_pressed = !m_pressed;
	else
		std::cout << "Wierd?" << std::endl;
}

void Button::render(SDL_Renderer* renderer)
{
	SDL_Rect renderRect = { m_x, m_y, m_w, m_h };

	if (m_pressed)
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
	else
		SDL_SetRenderDrawColor(renderer, 0, 255, 0, 0);

	SDL_RenderFillRect(renderer, &renderRect);
}