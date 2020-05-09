#pragma once
// std includes
#include <string>
#include <vector>

// sdl includes
#include "SDL_events.h"

struct SDL_Renderer;

class Item
{
public:
	Item() = default;

	void setId(const std::string&);
	void setOrder(int);
	void setPos(float x, float y);
	void setSize(float w, float h);
	void setVisible(bool);

	/// Returns deepest child
	virtual Item* childAt(float x, float y);
	/// Return all Items that contains point
	/// For now do not return container itself
	virtual std::vector<Item*> childrenAt(float x, float y);
	/// All Item  s except containers(for now)
	virtual std::vector<Item*> children();

	virtual void render(SDL_Renderer*);
	virtual void handleEvent(SDL_Event*);

protected:
	/// Virtual in case of any other parameters will be
	/// added in the future(rotation, polygons)
	virtual bool isPointInside(float x, float y) const;
	virtual void onMotion(SDL_MouseMotionEvent*);
	virtual void onMouseButtonEvent(SDL_MouseButtonEvent*);

	std::string m_id;
	float m_x, m_y;
	float m_w, m_h;
	bool m_visible = true;
};