// project includes
#include "image.h"
#include "application.h"
#include "applicationwindow.h"

// std includes
#include <string>
#include <iostream>

// sdl includes
#include "SDL.h"
#include "SDL_image.h"

Image::Image(const std::string& path, Item* parent):
	Item(parent),
	m_path(path) {}

void Image::setPath(const std::string& value)
{
	m_path = value;
}

Image::~Image()
{
	if(m_texture)
		SDL_DestroyTexture(m_texture);
}

bool Image::loadImage(SDL_Renderer* renderer)
{
	if (m_path.empty())
	{
		std::cout << "No path" << std::endl;
		return false;
	}

	SDL_Texture* newTexture = NULL;

	SDL_Surface* loadedSurface = IMG_Load(m_path.c_str());
	if (!loadedSurface)
	{
		std::cout << "Unable to load img: " << IMG_GetError() << std::endl;
		return false;
	}

	m_imageHeight = loadedSurface->h;
	m_imageWidth = loadedSurface->w;

	SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

	newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
	if (!newTexture)
	{
		printf("Unable to create texture from %s! SDL Error: %s\n", m_path.c_str(), SDL_GetError());
		return false;
	}

	SDL_FreeSurface(loadedSurface);
	m_texture = newTexture;

	return true;
}

void Image::render(SDL_Renderer* renderer)
{
	if (!this->m_visible || !loadImage(renderer))
		return;

	SDL_Rect image = { 0, 0, m_imageWidth, m_imageHeight };
	SDL_Rect renderQuad = { m_x, m_y, m_w, m_h };

	SDL_RenderCopy(renderer, m_texture, &image, &renderQuad);
}

void Image::onMotion(SDL_MouseMotionEvent* e)
{
	bool oldValue = m_visible;

	int x = e->x, y = e->y;
	if (this->isPointInside(x, y))
	{
		if (m_id == "img1")
			m_visible = false;
		else
			m_visible = true;
	}
	else
	{
		if (m_id == "img1")
			m_visible = true;
		else
			m_visible = false;
	}

	if (oldValue != m_visible)
		update(e->windowID);
}

void Image::update(int windowId)
{
	Application &app = Application::instance();
	if (auto window = app.windowById(windowId))
	{
		ApplicationWindow::RenderCall call = std::bind(&Image::render, this, std::placeholders::_1);
		window->insertCall(call);
	}
}
