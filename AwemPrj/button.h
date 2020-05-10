#pragma once
// project includes
#include "item.h"

// forward declarations
struct SDL_Renderer;
struct SDL_Texture;
class ApplicationWindow;

class Button :
	public Item
{
public:
	Button(Item* parent = nullptr);
	virtual ~Button() override;

	/// Render is called after init 
	virtual void render(SDL_Renderer*) override;

protected:
	virtual void onMouseButtonEvent(SDL_MouseButtonEvent*) override;

private:
	bool m_pressed;
	ApplicationWindow* m_window = nullptr;
};