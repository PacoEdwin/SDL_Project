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

int main(int argc, char* args[])
{
	Application &app = Application::instance();
	
	auto window = app.newWindow("app");

	app.run();
	return 0;
}