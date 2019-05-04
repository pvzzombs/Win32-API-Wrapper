#ifndef WIN32_EVENT_HANDLER_H
#define WIN32_EVENT_HANDLER_H
#include <map>

struct button_states
{
    bool pressed = false;
    bool released = false;
    bool held = false;
};

enum Keys
{
    A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
    K0, K1, K2, K3, K4, K5, K6, K7, K8, K9,
    F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12,
    UP, DOWN, LEFT, RIGHT,
    SPACE, TAB, SHIFT, CTRL, INS, DEL, HOME, END, PGUP, PGDN,
    BACK, ESCAPE, ENTER, PAUSE, SCROLL,
};

struct win32_input_state
{
    std::map<uint16_t, uint8_t> key_map;
    bool		    new_key_state[256] { 0 };
    bool		    old_key_state[256] { 0 };
    button_states	keyboard_state[256];

    bool		    new_mouse_state[5]{ 0 };
    bool		    old_mouse_state[5]{ 0 };
    button_states	mouse_state[5];
};


#endif