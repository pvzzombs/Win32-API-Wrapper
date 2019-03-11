#ifndef WRAPPY_APPLICATION_H
#define WRAPPY_APPLICATION_H

#include <windows.h>
#include <gdiplus.h>
#pragma comment(lib, "gdiplus.lib")

#include <stdio.h>
#include <time.h>
#include <math.h>
#include <stdio.h>
#include <string>

#define _PI 3.14159265359
using namespace Gdiplus;

namespace Wrappy
{
	class Application
	{
	public:
		static Application* CreateApplication()
		{
			return new Application();
		}

		virtual ~Application();
		void Run();

		// Window Related
		void Window(std::string title, int width, int height);
		void registerWindowClass();
		static void onPaint();

		// Message Related
		static LRESULT CALLBACK WindowsEvents(HWND win, UINT msg, WPARAM w, LPARAM l);
		void processWindowsEvents();

		// GDI+ Related
		void startGDIplus();
		void endGDIplus();

	private:
		Application();
		HWND m_handle;
		LPCSTR windowClassName = "WrappyApp";
		GdiplusStartupInput gdiplusStartupInput;
		ULONG_PTR           gdiplusToken;
		HDC					DeviceContext;
		bool				running;
	};
}

#endif