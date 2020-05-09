// std includes
#include <string>
#include <vector>

class ApplicationWindow;

class Application
{
public:
	Application();
	Application(Application const&) = delete;
	void operator=(Application const&) = delete;

	static Application& instance();

	ApplicationWindow* newWindow(std::string name = "");
	
	void run();

private:
	void addWindow(ApplicationWindow*);

	std::vector<ApplicationWindow*> m_windows;
};