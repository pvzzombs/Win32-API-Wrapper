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

struct win32_window_dimensions
{
	unsigned int width;
	unsigned int height;
};

struct win32_drawing_objects
{
	HDC			hdc;
	HDC			hdcBuf;
	HBITMAP		hbmpBuf;
	Graphics*	gfxBuf;
};

class Application
{
public:
	static Application* app;
	static Application* CreateApplication(const char* window_name, unsigned int width, unsigned int height)
	{
		app = new Application(window_name, width, height);
		return app;
	}

	static Application* App()
	{
		if (app)
		{
			return app;
		}
	}

	virtual ~Application();
	void Run();

	// Window Related
	void Window(std::string title);
	void register_window_class();
	void process_windows_events();
	void clear_window();
    void clean_graphics_object();

	// GDI+ Related
	void start_GDI_plus();
	void end_GDI_plus();

	// Accessors
	const win32_window_dimensions* get_window_dimension() const { return &window_dimensions; }
	inline const unsigned int get_window_width() const { return window_dimensions.width; }
	inline const unsigned int get_window_height() const { return window_dimensions.height; }

	win32_drawing_objects* get_drawing_objects() { return &drawing_objects; }
	Graphics* gfx_buffer() const { return drawing_objects.gfxBuf; }
	void set_drawing_objects(win32_drawing_objects& obj) { drawing_objects = obj;  }
	
private:
	Application(const char* window_name, unsigned int width, unsigned int height);

	HWND				m_handle;
	LPCSTR				windowClassName = "WrappyApp";
	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR           gdiplusToken;
	HDC					DeviceContext;
	bool				running;

	win32_window_dimensions window_dimensions;
	win32_drawing_objects	drawing_objects;
};

#endif