// sdl includes
#include <SDL.h>

// project includes
#include "application.h"
#include "applicationwindow.h"


Application::Application(){}

Application& Application::instance()
{
	static Application instance;
	return instance;
}

void Application::addWindow(ApplicationWindow* window)
{
	m_windows.push_back(window);
}

ApplicationWindow* Application::newWindow(std::string name)
{
	if (name.empty())
		name = "window" + std::to_string(m_windows.size());

	auto window = new ApplicationWindow(name);

	this->addWindow(window);

	return window;
}

void Application::run()
{
	SDL_Event e;
	bool quit = false;

	/// While application is running
	while (!quit)
	{
		int x = 0;
		int y = 0;
		/// Handle events on queue
		while (SDL_PollEvent(&e) != 0)
		{
			/// User requests quit
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}

			for (auto window : m_windows)
				window->handleEvent(&e);
		}

		auto renderer = window->renderer();
		//window->render();
		/// Clear screen
		SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(renderer);

		auto items = window->children();
		for (auto el : items)
			el->render(renderer);

		/// Update screen
		SDL_RenderPresent(renderer);
	}
}