#ifndef WIN32_INPUT_H
#define WIN32_INPUT_H

#include <map>
#include <vector>

struct button_state
{
    bool pressed = false;
    bool held = false;
};

enum BUTTONS
{
    MOUSE_LEFT,
    MOUSE_MIDDLE,
    MOUSE_RIGHT
};

struct win32_input_state
{
    std::map<uint16_t, uint8_t> key_map;
    bool new_key_state[256]{0};
    bool old_key_state[256]{0};
    button_state keyboard_state[256]{{0, 0}};

    std::vector<long> mouse_pos{0, 0};
    bool new_mouse_state[3]{0};
    bool old_mouse_state[3]{0};
    button_state mouse_state[3];
};

enum Keys
{
    A,
    B,
    C,
    D,
    E,
    F,
    G,
    H,
    I,
    J,
    K,
    L,
    M,
    N,
    O,
    P,
    Q,
    R,
    S,
    T,
    U,
    V,
    W,
    X,
    Y,
    Z,
    K0,
    K1,
    K2,
    K3,
    K4,
    K5,
    K6,
    K7,
    K8,
    K9,
    F1,
    F2,
    F3,
    F4,
    F5,
    F6,
    F7,
    F8,
    F9,
    F10,
    F11,
    F12,
    UP,
    DOWN,
    LEFT,
    RIGHT,
    SPACE,
    TAB,
    SHIFT,
    CTRL,
    INS,
    DEL,
    HOME,
    END,
    PGUP,
    PGDN,
    BACK,
    ESCAPE,
    ENTER,
};

#endif