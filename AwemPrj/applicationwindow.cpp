// project includes
#include "applicationwindow.h"
#include "image.h"
#include "button.h"

// std includes
#include <iostream>

// sdl includes
#include <SDL_image.h>

ApplicationWindow::ApplicationWindow()
{
	m_name = "default";
}

ApplicationWindow::ApplicationWindow(const std::string& name):
	m_name(name) {}

void ApplicationWindow::setName(const std::string& value)
{
	m_name = value;
}

void ApplicationWindow::init()
{
	/// Probably shall throw execption here

	/// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		return;
	}

	/// Set texture filtering to linear
	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
	{
		printf("Warning: Linear texture filtering not enabled!");
		return;
	}

	/// Create window
	m_window = SDL_CreateWindow(m_name.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_screenWidth, m_screenHeight, SDL_WINDOW_SHOWN);
	if (!m_window)
	{
		printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
		return;
	}

	/// Create renderer for window
	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
	if (!m_renderer)
	{
		printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
		return;
	}

	SDL_SetRenderDrawColor(m_renderer, 0xFF, 0xFF, 0xFF, 0xFF);

	/// Initialize PNG loading
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		printf("SDL_image could not initialize! SDL_mage Error: %s\n", IMG_GetError());
		return;
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

	auto button = new Button();
	button->setPos(0, 400);
	button->setSize(160, 80);

	m_container = std::make_shared<WidgetContainer>();
	m_container->addItem(image1);
	m_container->addItem(image2);
	m_container->addItem(button);
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

void ApplicationWindow::render()
{
	/// Clear screen
	SDL_SetRenderDrawColor(m_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(m_renderer);

	auto chld = children();
	for (auto el : chld)
		el->render(m_renderer);

	/// Update screen
	SDL_RenderPresent(m_renderer);
}

void ApplicationWindow::handleEvent(SDL_Event* e)
{
	auto children = this->children();
	for (auto child : children)
		child->handleEvent(e);
}