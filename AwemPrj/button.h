#pragma once
#include "item.h"

struct SDL_Renderer;
struct SDL_Texture;

class Button :
	public Item
{
public:
	Button();

	virtual void render(SDL_Renderer*) override;

protected:
	virtual void onMouseButtonEvent(SDL_MouseButtonEvent*) override;

private:
	bool m_pressed;

	SDL_Texture* m_texture;
};