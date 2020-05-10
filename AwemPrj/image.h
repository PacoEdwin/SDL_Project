#pragma once
#include "item.h"

struct SDL_Texture;
struct SDL_Renderer;

class Image:
	public Item
{
public:
	Image(const std::string&, Item* parent = nullptr);
	virtual ~Image() override;

	void setPath(const std::string&);

	virtual void render(SDL_Renderer*) override;

protected:
	virtual void onMotion(SDL_MouseMotionEvent*) override;

private:
	void update(int windowId);
	bool loadImage(SDL_Renderer*);

	std::string m_path;
	SDL_Texture* m_texture = nullptr;

	int m_imageHeight, m_imageWidth;
};