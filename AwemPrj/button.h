#pragma once
#include "item.h"

struct SDL_Renderer;
struct SDL_Texture;

class Button :
	public Item
{
public:
	Button(Item* parent = nullptr);

	virtual void render(SDL_Renderer*) override;
	void update(int);

protected:
	virtual void onMouseButtonEvent(SDL_MouseButtonEvent*) override;

private:
	bool m_pressed;
};