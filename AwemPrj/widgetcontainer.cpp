// project includes
#include "widgetcontainer.h"

WidgetContainer::WidgetContainer(Item* parent):
	Item(parent) {}

WidgetContainer::WidgetContainer(const std::vector<Item*>& container):
	m_container(container) {}

void WidgetContainer::setContainer(const std::vector<Item*>& value)
{
	m_container = value;
}

void WidgetContainer::addItem(Item* value)
{
	m_container.push_back(value);
}

Item* WidgetContainer::childAt(float x, float y)
{
	for (Item* el : m_container)
		if (el->childAt(x, y))
			return el;

	return nullptr;
}

std::vector<Item*> WidgetContainer::children()
{
	std::vector<Item*> output;
	for (Item* el : m_container)
	{
		auto elChildren = el->children();
		output.insert(std::end(output), std::begin(elChildren), std::end(elChildren));
	}

	return output;
}

std::vector<Item*> WidgetContainer::childrenAt(float x, float y)
{
	std::vector<Item*> output;
	for (Item* el : m_container)
	{
		auto elChildren = el->childrenAt(x, y);
		for (Item* child : elChildren)
			if (child)
				output.push_back(child);
	}

	return output;
}