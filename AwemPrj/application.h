// std includes
#include <list>
#include <string>
#include <utility>
#include <unordered_map>

// forward declarations
class ApplicationWindow;

class Application
{
public:
	Application();
	Application(Application const&) = delete;
	~Application();
	void operator=(Application const&) = delete;

	ApplicationWindow* windowById(int);
	ApplicationWindow* newWindow(std::string name = "");
	void removeWindow(ApplicationWindow*);

	void run();
	void exit();

	static Application& instance();

private:
	void addWindow(ApplicationWindow*);

	std::list<ApplicationWindow*> m_windows;
	std::unordered_map<int, std::pair<ApplicationWindow*, std::list<ApplicationWindow*>::iterator>> m_windowById;
};