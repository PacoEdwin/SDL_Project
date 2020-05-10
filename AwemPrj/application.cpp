// sdl includes
#include <SDL.h>

// project includes
#include "application.h"
#include "applicationwindow.h"

// std includes
#include <iostream>

Application::Application(){}

Application::~Application()
{
	exit();
}

Application& Application::instance()
{
	static Application instance;
	return instance;
}

void Application::addWindow(ApplicationWindow* window)
{
	int id = window->windowId();

	m_windows.push_back(window);
	m_windowById[id] = { window,  std::prev(m_windows.end()) };
}

ApplicationWindow* Application::windowById(int value)
{
	auto output = m_windowById.find(value);
	if (output == m_windowById.end())
		return nullptr;

	return output->second.first;
}

void Application::removeWindow(ApplicationWindow* value)
{
	auto it = m_windowById.find(value->windowId());
	if (it != m_windowById.end())
	{
		m_windows.erase(it->second.second);
		m_windowById.erase(it);
	}
}

ApplicationWindow* Application::newWindow(std::string name)
{
	if (name.empty())
		name = "window" + std::to_string(m_windows.size());

	auto window = new ApplicationWindow(name);
	/// Probalby catch exceptions here
	try {
		window->init();
	}
	catch (std::exception &e) {
		std::cout << e.what() << std::endl;
		delete window;
		return nullptr;
	}

	this->addWindow(window);
	return window;
}

void Application::run()
{
	SDL_Event e;
	/// While application is running
	bool quit = false;
	while (!quit)
	{
		/// Update
		for (auto window : m_windows)
			window->update();
		
		int x = 0;
		int y = 0;
		/// Handle events on queue
		while (SDL_PollEvent(&e) != 0)
		{
			/// User requests quit
			if (e.type == SDL_QUIT)
			{
				quit = true;
				break;
			}

			/// Exit by key event
			/*if (e.type == SDL_KEYDOWN)
			{
				quit = true;
				break;
			}*/

			/// Handle events
			for (auto window : m_windows)
				window->handleEvent(&e);
		}
	}

	exit();
}

void Application::exit()
{
	while(!m_windows.empty())
	{
		auto window = *m_windows.begin();
		removeWindow(window);
		delete window;
	}	
}