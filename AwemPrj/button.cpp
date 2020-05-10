// prject includes
#include "button.h"
#include "application.h"
#include "applicationwindow.h"

// std incldudes
#include <iostream>

// sdl includes
#include <SDL.h>

Button::Button(Item* parent):
	Item(parent),
	m_pressed(false){}

Button::~Button()
{
	if (m_window)
	{
		Application::instance().removeWindow(m_window);
		delete m_window;
	}
}

void Button::onMouseButtonEvent(SDL_MouseButtonEvent* e)
{
	if (!isPointInside(e->x, e->y))
		return;

	bool oldvalue = m_pressed;

	if (e->state == SDL_PRESSED)
	{
		m_pressed = !m_pressed;
		
		if (m_pressed)
			m_window = Application::instance().newWindow();
		else
		{
			Application::instance().removeWindow(m_window);
			delete m_window;
			m_window = nullptr;
		}
	}

	if (m_pressed != oldvalue)
		update(e->windowID);
}

void Button::update(int windowId)
{
	Application &app = Application::instance();
	if (auto window = app.windowById(windowId))
	{
		ApplicationWindow::RenderCall call = std::bind(&Button::render, this, std::placeholders::_1);
		window->insertCall(call);
	}
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