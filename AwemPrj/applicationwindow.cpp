// project includes
#include "applicationwindow.h"
#include "image.h"
#include "button.h"

// std includes
#include <string>
#include <iostream>

// sdl includes
#include <SDL_image.h>

ApplicationWindow::ApplicationWindow()
{
	m_name = "default";
}

ApplicationWindow::ApplicationWindow(const std::string& name):
	m_name(name) {}

ApplicationWindow::~ApplicationWindow()
{
	if (m_window)
		SDL_DestroyWindow(m_window);

	if(m_renderer)
		SDL_DestroyRenderer(m_renderer);
}

void ApplicationWindow::setName(const std::string& value)
{
	m_name = value;
}

int ApplicationWindow::windowId() const
{
	return m_windowId;
}

void ApplicationWindow::init()
{
	/// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::string errorMsg = "SDL could not initialize! SDL Error: " + std::string(SDL_GetError());
		throw std::runtime_error(errorMsg);
	}

	/// Set texture filtering to linear
	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		throw std::logic_error("Warning: Linear texture filtering not enabled!");

	/// Create window
	m_window = SDL_CreateWindow(m_name.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_screenWidth, m_screenHeight, SDL_WINDOW_SHOWN);
	if (!m_window)
	{
		std::string errorMsg = "Window could not be created! SDL Error: " + std::string(SDL_GetError());
		throw std::runtime_error(errorMsg);
	}

	/// Create renderer for window
	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
	if (!m_renderer)
	{
		std::string errorMsg = "Renderer could not be created! SDL Error: " + std::string(SDL_GetError());
		throw std::runtime_error(errorMsg);
	}

	SDL_SetRenderDrawColor(m_renderer, 0xFF, 0xFF, 0xFF, 0xFF);

	m_windowId = SDL_GetWindowID(m_window);

	/// Initialize PNG loading
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		std::string errorMsg = "SDL_image could not initialize! SDL_mage Error: " + std::string(IMG_GetError());
		throw std::runtime_error(errorMsg);
	}

	auto image1 = new Image("./trash.jpg");
	image1->setId("img1");
	image1->setPos(160, 0);
	image1->setSize(480, 480);

	auto image2 = new Image("./puppy.jpg");
	image2->setId("img2");
	image2->setPos(160, 0);
	image2->setSize(480, 480);
	image2->setVisible(false);

	m_container = std::make_shared<WidgetContainer>();
	m_container->addItem(image1);
	m_container->addItem(image2);

	/// 2 ways of setting parent
	auto button = new Button(m_container.get());
	button->setPos(0, 400);
	button->setSize(160, 80);
	m_container->addItem(button);

	image1->setParent(m_container.get());
	image2->setParent(m_container.get());

	render();
}

SDL_Renderer* ApplicationWindow::renderer() const
{
	return m_renderer;
}

Item* ApplicationWindow::childAt(float x, float y)
{
	return m_container->childAt(x, y);
}

std::vector<Item*> ApplicationWindow::children()
{
	return m_container->children();
}

std::vector<Item*> ApplicationWindow::childrenAt(float x, float y)
{
	return m_container->childrenAt(x, y);
}

void ApplicationWindow::insertCall(ApplicationWindow::RenderCall value)
{
	m_renderPoll.push(value);
}

void ApplicationWindow::update()
{
	if (!m_renderPoll.empty())
	{
		while (!m_renderPoll.empty())
		{
			auto call = m_renderPoll.front();
			m_renderPoll.pop();

			call(m_renderer);
		}

		SDL_RenderPresent(m_renderer);
	}
}

void ApplicationWindow::render()
{
	SDL_SetRenderDrawColor(m_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(m_renderer);

	auto childern = m_container->children();
	for (auto child : childern)
		child->render(m_renderer);

	SDL_RenderPresent(m_renderer);
}

void ApplicationWindow::handleEvent(SDL_Event* e)
{
	switch (e->type)
	{
		case SDL_WINDOWEVENT: {
			m_shown = e->window.windowID == m_windowId;
			break;
		}

		case SDL_MOUSEBUTTONDOWN: {
			m_shown = e->button.windowID == m_windowId;
			break;
		}
	}

	if (!m_shown)
		return;

	auto children = this->children();
	for (auto child : children)
		child->handleEvent(e);
}