// ---Core App -----------------------
#include "Core/Application.h"

int main(int argc, char** argv)
{
	auto app = Application::CreateApplication(L"Hello", 400, 400);
	app->Run();
	delete app;
	return 0;
}
