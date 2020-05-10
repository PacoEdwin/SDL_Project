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

class ApplicationWindow:
	public Initializable
{
public:
	typedef std::function<void(SDL_Renderer*)> RenderCall;

	ApplicationWindow();
	ApplicationWindow(const std::string&);

	virtual void init() override;
	void setName(const std::string&);

	SDL_Renderer* renderer() const;
	void render();
	
	Item* childAt(float x, float y);
	std::vector<Item*> children();
	std::vector<Item*> childrenAt(float x, float y);
	int windowId() const;

	void insertCall(RenderCall);
	void handleEvent(SDL_Event*);
	void update();

private:
	bool m_shown = false;
	int m_windowId = -1;
	SDL_Window* m_window = NULL;
	SDL_Renderer* m_renderer = NULL;

	std::string m_name;
	const int m_screenWidth = 640;
	const int m_screenHeight = 480;

	WidgetContainer::Pointer m_container;
	std::queue<std::function<void(SDL_Renderer*)>> m_renderPoll;
};