#ifndef WRAPPY_APPLICATION_H
#define WRAPPY_APPLICATION_H

#include "Structs.h"
#include "WIN32_Input.h"

#define DEMO_ON
//#undef DEMO_ON

class Application
{
public:
    virtual ~Application();
    static Application *CreateApplication(LPCWSTR window_name, unsigned int w, unsigned int h);
    static Application *App();

    void Run();

    // SECTION: User defined functions
    virtual void setup(){};          // INFO: Called in constructor.
    virtual void update(float dt){}; // INFO: Called in run, before invalidation.
    virtual void draw(HDC hdc){};    // INFO: Called in WM_PAINT.
    virtual void end(){};            // INFO: Called in destructor, as first call.
    virtual void double_click(){};   // INFO: Called when left mouse double clicked.

    // SECTION: Accessors

    // // SECTION: Object Accessors
    inline win32_window_dimensions *get_window_dimension() { return &window_dimensions; }
    inline win32_input_state get_input_state() { return input_state; }
    inline win32_drawing_objects *get_drawing_objects() { return &drawing_objects; }
    button_state key(Keys key);         // INFO: Get button_state for keyboard.
    button_state mouse(BUTTONS button); // INFO: Get button_state for mouse.

    // // SECTION: Variable Accessors
    inline uint32_t get_window_width() { return window_dimensions.width; }
    inline uint32_t get_window_height() { return window_dimensions.height; }
    inline Graphics *gfx_buffer() { return drawing_objects.gfxBuf; }
    inline bool window_has_focus() { return app_state.application_has_focus; }

    // SECTION: Mutators

protected:

private:
    Application(LPCWSTR window_name, uint32_t w, uint32_t h);
    static LRESULT CALLBACK windows_event_handler(HWND win, UINT msg, WPARAM w, LPARAM l);

    // SECTION: Private Mutators
    void set_key_state(WPARAM w, bool state);
    void set_mouse_state(BUTTON b, bool state);
    void set_mouse_position(long &x, long &y);
    inline void set_focus(bool has_focus) { app_state.application_has_focus = has_focus; }

    // SECTION: Private Functions
    void Window(LPCWSTR title);
    void register_window_class();
    void process_windows_events();
    void clear_window();
    void clean_graphics_object();
    void init_input();
    void process_input_state();

    void start_GDI_plus();
    void end_GDI_plus();

    // SECTION: Variables
    static Application *app;
    HWND m_handle;
    HDC DeviceContext;
    win32_window_dimensions window_dimensions;

    std::map<int, Keys> key_map;
    win32_input_state input_state;

    win32_drawing_objects drawing_objects;
    win32_application_state app_state;
};

#endif