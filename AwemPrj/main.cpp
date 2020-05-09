// sdl includes
#include <SDL.h>
#include <SDL_image.h>

// std includes
#include <iostream>
#include <string>

// project includes
#include "application.h"
#include "applicationwindow.h"

using namespace std;

void close()
{

	////Destroy window	
	//SDL_DestroyRenderer(gRenderer);
	//SDL_DestroyWindow(gWindow);
	//gWindow = NULL;
	//gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

int main(int argc, char* args[])
{
	Application &app = Application::instance();
	auto window = app.newWindow("app");
	window->ensureInitialized();

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

			auto children = window->children();
			for (auto el : children)
				el->handleEvent(&e);
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

	close();

	system("pause");
	return 0;
}