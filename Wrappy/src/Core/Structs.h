#ifndef STRUCTS_H
#define STRUCTS_H

#include <windows.h>
#include <gdiplus.h>
#pragma comment(lib, "gdiplus.lib")

#define _PI 3.14159265359
using namespace Gdiplus;

#include <stdio.h>
#include <time.h>
#include <math.h>
#include <stdio.h>
#include <string>
#include <cstdint>
#include <map>

struct win32_window_dimensions
{
	uint32_t width;
	uint32_t height;
};

struct win32_drawing_objects
{
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;

	HDC hdc;
	HDC hdcBuf;
	HBITMAP hbmpBuf;
	Graphics *gfxBuf;
};

struct win32_application_state
{
	LPCWSTR application_class_name = L"WrappyApp";
	bool application_running = true;

	bool application_has_focus = true;

	uint32_t mouse_pos_x = 0;
	uint32_t mouse_pos_y = 0;
};

#endif