#ifndef WRAPPY_APPLICATION_H
#define WRAPPY_APPLICATION_H

#include "Structs.h"
#include "WIN32_Input.h"

class Application
{
  public:
    virtual ~Application();
    static Application *app;
    static Application *CreateApplication(LPCWSTR window_name, unsigned int width, unsigned int height)
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

    virtual void setup(){};          // Called in constructor.
    virtual void update(float dt){}; // Called in run, before invalidation.
    virtual void draw(HDC hdc){};    // Called in WM_PAINT.
    virtual void end(){};            // Called in destructor, as first call.

    // Accessors
    const win32_window_dimensions *get_window_dimension() const { return &window_dimensions; }
    inline const uint32_t get_window_width() const { return window_dimensions.width; }
    inline const uint32_t get_window_height() const { return window_dimensions.height; }

    win32_drawing_objects *get_drawing_objects() { return &drawing_objects; }
    inline Graphics *gfx_buffer() const { return drawing_objects.gfxBuf; }

    void set_focus(bool has_focus) { app_state.application_has_focus = has_focus; }
    const bool window_has_focus() const { return app_state.application_has_focus; }

    button_state key(Keys key); // Get button_state for key.

    void process_input_state();

private:
    Application(LPCWSTR window_name, uint32_t width, uint32_t height);

    std::map<int, Keys> key_map;

	void set_key_state(WPARAM w, bool state);

    // Functions
    void Window(LPCWSTR title);
    void register_window_class();
    void process_windows_events();
    void clear_window();
    void clean_graphics_object();
    void init_input();

    void start_GDI_plus();
    void end_GDI_plus();

    // Variables
    HWND m_handle;
    HDC DeviceContext;

    win32_window_dimensions window_dimensions;
    win32_drawing_objects drawing_objects;
    win32_application_state app_state;
    win32_input_state input_state;

    static LRESULT CALLBACK windows_event_handler(HWND win, UINT msg, WPARAM w, LPARAM l);
};

#endif