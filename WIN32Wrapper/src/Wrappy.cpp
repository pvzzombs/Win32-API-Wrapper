// ---Core App -----------------------
#include "Core/Application.h"

class MyApp : public Application
{
public:
    MyApp(LPCWSTR name, uint32_t w, uint32_t h) : Application(name, w, h) {}

    void setup() override {}          // INFO: Ran once on app creation.
    void end() override {}            // INFO: Ran once on app end.
    void update(float dt) override {} // INFO: Called every frame.
    void input() override {}          // INFO: Called every frame.
    void double_click() override {}   // INFO: Called only when left mouse is double clicked.
    void draw(HDC hdc) override {}    // INFO: Called every frame - Use with #undef DEMO_ON
};

int main(int argc, char **argv)
{
    MyApp *app = new MyApp(L"HelloWorld", 400, 400);
    app->Run();
    delete app;
    return 0;
}
