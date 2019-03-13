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
    GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR gdiplusToken;

    HDC hdc;
    HDC hdcBuf;
    HBITMAP hbmpBuf;
    Graphics *gfxBuf;
};

struct application_state
{
    LPCSTR application_class_name = "WrappyApp";
    bool app_state.application_running = true;
};

class Application
{
  public:
    virtual ~Application();
    static Application *app;
    ß
    static Application *CreateApplication(const char *window_name, unsigned int width, unsigned int height)
    {
        app = new Application(window_name, width, height);
        return app;
    }

    static Application *App()
    {
        if (app)
        {
            return app;
        }
    }

    void Run();

    // Insertion functions, used to insert user code into specific areas. 
    virtual void setup() {};            // Called in constructor.
    virtual void update(float dt) {};   // Called in run, before invalidation.
    virtual void draw(HDC hdc) {};      // Called in WM_PAINT.
    virtual void end() {};              // Called in destructor, as first call.

    // Accessors
    const win32_window_dimensions *get_window_dimension() const { return &window_dimensions; }
    inline const unsigned int get_window_width() const { return window_dimensions.width; }
    inline const unsigned int get_window_height() const { return window_dimensions.height; }

    win32_drawing_objects *get_drawing_objects() { return &drawing_objects; }
    inline Graphics *gfx_buffer() const { return drawing_objects.gfxBuf; }

  private:
    Application(const char *window_name, unsigned int width, unsigned int height);

    // Functions
    void Window(std::string title);
    void register_window_class();
    void process_windows_events();
    void clear_window();
    void clean_graphics_object();

    void start_GDI_plus();
    void end_GDI_plus();

    // Variables
    HWND m_handle;
    HDC DeviceContext;

    win32_window_dimensions window_dimensions;
    win32_drawing_objects drawing_objects;
    application_state app_state;
};ßßßß

#endif