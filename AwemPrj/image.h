#pragma once
#include "item.h"

struct SDL_Texture;
struct SDL_Renderer;

class Image:
	public Item
{
public:
	Image() = default;
	Image(const std::string&);

	void setPath(const std::string&);

	virtual void render(SDL_Renderer*) override;

protected:
	virtual void onMotion(SDL_MouseMotionEvent*) override;

private:
	bool loadImage(SDL_Renderer*);

	std::string m_path;
	SDL_Texture* m_texture;

	int m_imageHeight, m_imageWidth;
};