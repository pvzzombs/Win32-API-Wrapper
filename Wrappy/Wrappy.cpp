// ---Core App -----------------------
#include "Core/Application.h"

int main(int argc, char** argv)
{
	auto app = Wrappy::Application::CreateApplication();
	app->Run();
	delete app;
	return 0;
}
