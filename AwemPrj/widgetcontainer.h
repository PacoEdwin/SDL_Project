#pragma once
// project includes
#include "item.h"

// std includes
#include <vector>
#include <memory>

class WidgetContainer:
	public Item
{
public:
	typedef std::shared_ptr<WidgetContainer> Pointer;

	WidgetContainer() = default;
	WidgetContainer(const std::vector<Item*>&);

	void setContainer(const std::vector<Item*>&);
	void addItem(Item*);

	/// Returns deepest child
	virtual Item* childAt(float x, float y) override;
	/// Return all Items that contains point
	/// For now do not return container itself
	virtual std::vector<Item*> childrenAt(float x, float y) override;
	virtual std::vector<Item*> children() override;

private:
	std::vector<Item*> m_container;
};