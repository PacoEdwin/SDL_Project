// sdl includes
#include <SDL.h>

// std includes
#include <string>
#include <vector>

// project includes
#include "initializable.h"
#include "widgetcontainer.h"
#include "SDL_events.h"

class ApplicationWindow:
	public Initializable
{
public:
	ApplicationWindow();
	ApplicationWindow(const std::string&);

	virtual void init() override;
	void setName(const std::string&);

	SDL_Renderer* renderer() const;
	void render();

	Item* childAt(float x, float y);
	std::vector<Item*> children();
	std::vector<Item*> childrenAt(float x, float y);

	void handleEvent(SDL_Event*);

private:
	std::string m_name;
	SDL_Window* m_window = NULL;
	SDL_Renderer* m_renderer = NULL;

	const int m_screenHeight = 480;
	const int m_screenWidth = 640;

	WidgetContainer::Pointer m_container;
};