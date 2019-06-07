# Win32 API Wrapper

<!-- toc -->

- [Features](#Features)
- [Development Tools](#Development-Tools)
  * [Generate](#Generate)
  * [Clean Up](#Clean-Up)
- [Usage Guide](#Usage-Guide)
  * [Getting Started](#Getting-Started)
  * [Window](#Window)
    + [Set Up](#Set-Up)
    + [Values](#Values)
  * [User Functions](#User-Functions)
  * [Input](#Input)
    + [Keyboard](#Keyboard)
    + [Mouse](#Mouse)
      - [Mouse Position](#Mouse-Position)
  * [Demo Mode](#Demo-Mode)

<!-- tocstop -->

A C++ wrapper around the Win32 API. This wrapper handles window creation, configuration, events and running.

## Features

-  Window creation made easy.
-  Double Buffered GDI+ graphics.
-  Keyboard & Mouse input

## Development Tools

### Generate

To generate the project files, in the root directory for the project, enter in the command line: `Generate.bat`

This will generate project files for Visual Studio 2017, you can change the target by amending the `Generate.bat` file.

### Clean Up

The project includes a `.gitignore` file that will filter out the specific project files and outputs, but if you need to manually trigger a clean up then you can use `Clean.bat` from the command line, in the root directory.

## Usage Guide

### Getting Started

The wrapper is simple to implement, in your code you just need to include the `Application` header file: `#include "Core/Application.h"`

It is recommended that you extend the Application class to be able to implement custom functionality, a template for this is:

```
class MyApp : public Application
{
public:
	MyApp(LPCWSTR name, uint32_t w, uint32_t h) : Application(name, w, h) {}


	void setup() override {}		
	void end() override {}             
	void update(float dt) override {}  
	void input()override {}        	
	void double_click() override {}    
	void draw(HDC hdc) override {}     
};
```

And running the application in your main method is as simple as:

```
int main(int argc, char **argv)
{
    MyApp *app = new MyApp(L"HelloWorld", 400, 400);
    app->Run();
    delete app;
    return 0;
}
```

### Window

#### Set Up

Window setup is simply passing the following parameters to your application on construction:

`MyApp(LPCWSTR name, uint32_t w, uint32_t h)`

| Parameter | Purpose               | Example      |
|-----------|-----------------------|--------------|
| `name`    | Window title bar name | `L"Wrapper"` |
| `w`       | Window width          | 1280         |
| `h`       | Window height         | 1024         |

#### Values

You can query the state of the window with the following functions:

| Function                         | Purpose                                           |
|----------------------------------|---------------------------------------------------|
| `uint32_t get_window_width()`    | Return window width.                              |
| `uint32_t get_window_height()`   | Return window height.                             |
| `bool window_has_focus()`        | Return true if the window is in focus and active. |
| `void set_focus(bool has_focus)` | Set the focus state.                              |

### User Functions

The wrapper contains various user functions which hook into the main application, these can be implemented by a derived class and allow custom functionality in the application.

| Function           | Purpose                                |
|--------------------|----------------------------------------|
| `setup()`          | Called in constructor.                 |
| `update(float dt)` | Called in run, before invalidation.    |
| `draw(HDC hdc)`    | Called in WM_PAINT.                    |
| `end()`            | Called in destructor, as first call.   |
| `double_click()`   | Called when left mouse double clicked. |

For simplicity and to ensure separation of the base implementation from any custom implementation, these functions accept limited, or no parameters. It is recommended that you encapsulate all state that these will need into the derived class as member variables, rather than passing values around, or even changing the `Application` implementation.

### Input

The wrapper supports keyboard and mouse input, and implements a simple interface to access input state.

A key or mouse button has two boolean flags:

- `pressed`: True when pressed on that frame.
- `held`: True when pressed on that frame and the last frame.

These values are encapsulated in a `button_state` object.

#### Keyboard

To access a key state: `key(Key)`
This returns a `button_state` and you can then use this to check the two states mentioned above.

Supported Key values are:

- `A` - `Z`
- `K0` - `K9`
- `F1` - `F12`
- `UP`, `DOWN`, `LEFT`, `RIGHT`
- `SPACE`, `TAB`, `SHIFT`, `CTRL`, `INS`, `DEL`,
- `HOME`, `END`, `PGUP`, `PGDN`, `BACK`, `ESCAPE`, `ENTER`

#### Mouse

To access a key state: `mouse(Button)`
This returns a `button_state` and you can then use this to check the two states mentioned above.

Buttons supported are: 

| Button         | Value                |
|----------------|----------------------|
| `MOUSE_LEFT`   | Left mouse button.   |
| `MOUSE_MIDDLE` | Middle mouse button. |
| `MOUSE_RIGHT`  | Right mouse button.  |

##### Mouse Position

You can get the mouse position with: `std::vector<long> mouse_position()`

You can then access the values of x and y:

- Index 0: x
- Index 1: y

### Demo Mode

Demo mode for this software will generate an analogue clock face that updates every second.

<img src="https://raw.githubusercontent.com/ivSlesser/Win32-API-Wrapper/master/vendor/img/clock.png"/>

Demo mode is enabled by default, to disable you should specify `#undef DEMO_ON` in your application after the `Application.h` header is imported.