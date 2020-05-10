// std includes
#include <string>
#include <vector>
#include <unordered_map>

class ApplicationWindow;

class Application
{
public:
	Application();
	Application(Application const&) = delete;
	void operator=(Application const&) = delete;

	static Application& instance();

	ApplicationWindow* windowById(int);
	ApplicationWindow* newWindow(std::string name = "");

	void run();

private:
	void addWindow(ApplicationWindow*);

	std::vector<ApplicationWindow*> m_windows;
	std::unordered_map<int, ApplicationWindow*> m_windowById;
};