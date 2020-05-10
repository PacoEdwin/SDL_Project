// project includes
#include "item.h"

// std includes
#include <iostream>

Item::Item():
	m_parent(nullptr) {}

Item::Item(Item* parent) :
	m_parent(parent) {}

Item::~Item() {}

void Item::setPos(float x, float y)
{
	m_x = x, m_y = y;
}

void Item::setSize(float w, float h)
{
	m_w = w, m_h = h;
}

void Item::setId(const std::string& value)
{
	m_id = value;
}

void Item::setParent(Item* value)
{
	m_parent = value;
}
/// Not rotated
bool Item::isPointInside(float x, float y) const
{
	if (m_x <= x && m_y <= y &&
		(m_x + m_w) >= x && (m_y + m_h) >= y)
		return true;

	return false;
}

Item* Item::childAt(float x, float y)
{
	if (isPointInside(x, y))
		return this;

	return nullptr;
}

std::vector<Item*> Item::children()
{
	return { this };
}

std::vector<Item*> Item::childrenAt(float x, float y)
{
	auto output = childAt(x, y);

	return { output };
}

void Item::setVisible(bool value)
{
	m_visible = value;
}

void Item::handleEvent(SDL_Event* e)
{
	switch (e->type)
	{
		case SDL_MOUSEMOTION: {
			this->onMotion(&e->motion);
			break;
		}

		case SDL_MOUSEBUTTONDOWN: {
			this->onMouseButtonEvent(&e->button);
			break;
		}
	}
}

void Item::render(SDL_Renderer*)
{

}

void Item::onMotion(SDL_MouseMotionEvent*)
{

}

void Item::onMouseButtonEvent(SDL_MouseButtonEvent*)
{

}