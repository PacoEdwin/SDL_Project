#pragma once
#include "item.h"

struct SDL_Renderer;
struct SDL_Texture;

class ApplicationWindow;

class Button :
	public Item
{
public:
	Button(Item* parent = nullptr);
	virtual ~Button() override;

	void update(int);
	virtual void render(SDL_Renderer*) override;

protected:
	virtual void onMouseButtonEvent(SDL_MouseButtonEvent*) override;

private:
	bool m_pressed;
	ApplicationWindow* m_window = nullptr;
};