// sdl includes
#include <SDL.h>
#include "SDL_events.h"

// std includes
#include <string>
#include <vector>
#include <queue>
#include <functional>

// project includes
#include "initializable.h"
#include "widgetcontainer.h"

/// Not sure if ApplicationWindow shall inherit Item
class ApplicationWindow:
	public Initializable
{
public:
	typedef std::function<void(SDL_Renderer*)> RenderCall;

	ApplicationWindow();
	ApplicationWindow(const std::string&);
	~ApplicationWindow();

	virtual void init() override;
	void setName(const std::string&);

	SDL_Renderer* renderer() const;
	/// Call after init
	void render();
	
	/// Recursively returns "deepest" child
	Item* childAt(float x, float y);
	/// Return all children except WidgetContainer
	/// Maybe shall return it as well
	std::vector<Item*> children();
	/// All children at that point
	std::vector<Item*> childrenAt(float x, float y);
	int windowId() const;

	/// Updates view
	void update();
	/// Inserts update callback
	void insertCall(RenderCall);
	/// Handle event
	void handleEvent(SDL_Event*);

private:
	bool m_shown = false;
	int m_windowId = -1;
	SDL_Window* m_window = nullptr;
	SDL_Renderer* m_renderer = nullptr;

	std::string m_name;
	const int m_screenWidth = 640;
	const int m_screenHeight = 480;

	WidgetContainer::Pointer m_container;
	std::queue<std::function<void(SDL_Renderer*)>> m_renderPoll;
};