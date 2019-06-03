#include "Application.h"

Application *Application::app = nullptr;

Application::Application(LPCWSTR window_name, uint32_t width, uint32_t height)
{
    app = this;

    window_dimensions.width = width;
    window_dimensions.height = height;
    setup(); // USER FUNCTION.
    Window(window_name);
}

Application::~Application()
{
    end(); // USER FUNCTION.
    clean_graphics_object();
    end_GDI_plus();
    // TODO: Clean up
}

void Application::Run()
{
    ShowWindow(m_handle, SW_SHOW);
    UpdateWindow(m_handle);

    while (app_state.application_running)
    {
        process_windows_events();
        update(1.0); // USER FUNCTION.
        clear_window();
    }
}

void Application::Window(LPCWSTR title)
{
    start_GDI_plus();
    register_window_class();

    RECT wr = {0, 0, window_dimensions.width, window_dimensions.height};
    AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);

    m_handle = CreateWindowEx(
        0, app_state.application_class_name, title,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        wr.right - wr.left, wr.bottom - wr.top,
        NULL, NULL, GetModuleHandleW(NULL), NULL);

    DeviceContext = GetDC(m_handle);

    if (!m_handle)
    {
        // TODO: Handle Error
    }
}

void Application::register_window_class()
{
    WNDCLASS wc = {};
    wc.style = 0; //CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = windows_event_handler;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = GetModuleHandleW(NULL);
    wc.hIcon = NULL;
    wc.hCursor = 0;
    wc.hbrBackground = 0;
    wc.lpszMenuName = NULL;
    wc.lpszClassName = app_state.application_class_name;

    RegisterClass(&wc);
}

void Application::process_windows_events()
{
    MSG msg;
    while (PeekMessageW(&msg, NULL, 0, 0, PM_REMOVE))
    {
        if (msg.message == WM_QUIT)
        {
            app_state.application_running = false;
        }

        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }
}

void Application::clear_window()
{
    RECT rect = {0, 0, window_dimensions.width, window_dimensions.height};
    InvalidateRect(m_handle, &rect, FALSE);
}

void Application::clean_graphics_object()
{
    DeleteDC(drawing_objects.hdc);
    DeleteDC(drawing_objects.hdcBuf);
    delete drawing_objects.gfxBuf;
    drawing_objects.gfxBuf = nullptr;
}

void Application::init_input()
{
    key_map[0x41] = Keys::A;
    key_map[0x42] = Keys::B;
    key_map[0x43] = Keys::C;
    key_map[0x44] = Keys::D;
    key_map[0x45] = Keys::E;
    key_map[0x46] = Keys::F;
    key_map[0x47] = Keys::G;
    key_map[0x48] = Keys::H;
    key_map[0x49] = Keys::I;
    key_map[0x4A] = Keys::J;
    key_map[0x4B] = Keys::K;
    key_map[0x4C] = Keys::L;
    key_map[0x4D] = Keys::M;
    key_map[0x4E] = Keys::N;
    key_map[0x4F] = Keys::O;
    key_map[0x50] = Keys::P;
    key_map[0x51] = Keys::Q;
    key_map[0x52] = Keys::R;
    key_map[0x53] = Keys::S;
    key_map[0x54] = Keys::T;
    key_map[0x55] = Keys::U;
    key_map[0x56] = Keys::V;
    key_map[0x57] = Keys::W;
    key_map[0x58] = Keys::X;
    key_map[0x59] = Keys::Y;
    key_map[0x5A] = Keys::Z;

    key_map[VK_F1] = Keys::F1;
    key_map[VK_F2] = Keys::F2;
    key_map[VK_F3] = Keys::F3;
    key_map[VK_F4] = Keys::F4;
    key_map[VK_F5] = Keys::F5;
    key_map[VK_F6] = Keys::F6;
    key_map[VK_F7] = Keys::F7;
    key_map[VK_F8] = Keys::F8;
    key_map[VK_F9] = Keys::F9;
    key_map[VK_F10] = Keys::F10;
    key_map[VK_F11] = Keys::F11;
    key_map[VK_F12] = Keys::F12;

    key_map[VK_DOWN] = Keys::DOWN;
    key_map[VK_LEFT] = Keys::LEFT;
    key_map[VK_RIGHT] = Keys::RIGHT;
    key_map[VK_UP] = Keys::UP;

    key_map[VK_BACK] = Keys::BACK;
    key_map[VK_ESCAPE] = Keys::ESCAPE;
    key_map[VK_RETURN] = Keys::ENTER;
    key_map[VK_PAUSE] = Keys::PAUSE;
    key_map[VK_SCROLL] = Keys::SCROLL;
    key_map[VK_TAB] = Keys::TAB;
    key_map[VK_DELETE] = Keys::DEL;
    key_map[VK_HOME] = Keys::HOME;
    key_map[VK_END] = Keys::END;
    key_map[VK_PRIOR] = Keys::PGUP;
    key_map[VK_NEXT] = Keys::PGDN;
    key_map[VK_INSERT] = Keys::INS;
    key_map[VK_SHIFT] = Keys::SHIFT;
    key_map[VK_CONTROL] = Keys::CTRL;
    key_map[VK_SPACE] = Keys::SPACE;

    key_map[0x30] = Keys::K0;
    key_map[0x31] = Keys::K1;
    key_map[0x32] = Keys::K2;
    key_map[0x33] = Keys::K3;
    key_map[0x34] = Keys::K4;
    key_map[0x35] = Keys::K5;
    key_map[0x36] = Keys::K6;
    key_map[0x37] = Keys::K7;
    key_map[0x38] = Keys::K8;
    key_map[0x39] = Keys::K9;
}

void Application::start_GDI_plus()
{
    Gdiplus::GdiplusStartup(&drawing_objects.gdiplusToken, &drawing_objects.gdiplusStartupInput, NULL);
}

void Application::end_GDI_plus()
{
    Gdiplus::GdiplusShutdown(drawing_objects.gdiplusToken);
}

/* Clock Specific */
time_t the_time;
struct tm *time_info;
const int WIN_WIDTH = 400;
const int WIN_HEIGHT = 400;
const int DIAMETER = 380;
const int OFFSET = (WIN_WIDTH - DIAMETER) / 2;
const int cX = WIN_WIDTH / 2;
const int cY = WIN_HEIGHT / 2;
const int DOT_SIZE = 20;

//void DrawClock(Graphics* graphics)
void DrawClock(HDC device_context)
{
	the_time = time(NULL);
	time_info = localtime(&the_time);

	//Graphics graphics(hdc);
	Graphics gfx(device_context);
	Graphics *graphics = &gfx;

	Pen pen(Color(255, 0, 0, 0));

	SolidBrush brush(Color(255, 255, 255, 255));
	graphics->FillRectangle(&brush, 0, 0, WIN_WIDTH, WIN_HEIGHT);
	brush.SetColor(Color(255, 0, 0, 0));

	pen.SetWidth(2);
	graphics->DrawEllipse(&pen, OFFSET, OFFSET, DIAMETER, DIAMETER);

	/* Drawing central dot */
	graphics->FillEllipse(&brush, cX - (DOT_SIZE / 2), cY - (DOT_SIZE / 2), DOT_SIZE, DOT_SIZE);

	/* Hour Hand */
	double hAngle = ((360.0f / 12.0f) * time_info->tm_hour + (time_info->tm_min / 2.0f) + 270.0f) * _PI / 180.0f;
	float hR = DIAMETER / 2.0f - 30.0f;

	int hX = (int)(cX + hR * cos(hAngle));
	int hY = (int)(cY + hR * sin(hAngle));

	pen.SetWidth(5);
	graphics->DrawLine(&pen, cX, cY, hX, hY);

	/* Minute Hand */
	double mAngle = ((360.0f / 60.0f) * time_info->tm_min + 270.0f) * _PI / 180.0f;
	float mR = DIAMETER / 2.0f - 3.0f;

	int mX = (int)(cX + mR * cos(mAngle));
	int mY = (int)(cY + mR * sin(mAngle));

	pen.SetWidth(2);
	graphics->DrawLine(&pen, cX, cY, mX, mY);

	/* Second Hand */
	double sAngle = ((360.0f / 60.0f) * time_info->tm_sec + 270.0f) * _PI / 180.0f;
	float sR = DIAMETER / 2.0f - 3.0f;

	int sX = (int)(cX + mR * cos(sAngle));
	int sY = (int)(cY + mR * sin(sAngle));

	pen.SetWidth(1);
	graphics->DrawLine(&pen, cX, cY, sX, sY);

	/* Hour markers */
	int steps = (int)(360.0f / 12.0f);
	for (int angle = steps - 90; angle <= 270; angle += steps)
	{
		double angleRad = angle * _PI / 180.0f;
		// End Points
		int eX = (int)(cX + (DIAMETER * 0.5f) * cos(angleRad));
		int eY = (int)(cY + (DIAMETER * 0.5f) * sin(angleRad));

		// Start Points
		int stX = (int)(eX - (DIAMETER * 0.06f) * cos(angleRad));
		int stY = (int)(eY - (DIAMETER * 0.06f) * sin(angleRad));

		graphics->DrawLine(&pen, stX, stY, eX, eY);

		std::wstring str = std::to_wstring((angle / 30) + 3);
		int fontSize = DIAMETER / 20;
		int offset = (int)ceil(fontSize / 4.0f);
		if (str.length() > 1)
			offset *= 2;

		float nX = (float)(eX - (DIAMETER * 0.1f) * cos(angleRad) - offset);
		float nY = (float)(eY - (DIAMETER * 0.1f) * sin(angleRad) - offset);

		SolidBrush brush(Color(255, 0, 0, 0));
		FontFamily fontFamily(L"Times New Roman");
		Font font(&fontFamily, fontSize, FontStyleRegular, UnitPixel);
		PointF pointF(nX, nY);

		graphics->DrawString(str.c_str(), str.length(), &font, pointF, &brush);
	}
}

/* End of Clock Specific */

LRESULT CALLBACK Application::windows_event_handler(HWND win, UINT msg, WPARAM w, LPARAM l)
{
	PAINTSTRUCT ps;

	switch (msg)
	{
	case WM_CREATE:
	{
		win32_drawing_objects *obj = Application::App()->get_drawing_objects();
		const win32_window_dimensions *dim = Application::App()->get_window_dimension();

		obj->hdc = GetDC(win);
		obj->hdcBuf = CreateCompatibleDC(obj->hdc);
		obj->hbmpBuf = CreateCompatibleBitmap(obj->hdcBuf, dim->width, dim->height);
		obj->gfxBuf = Graphics::FromHDC(obj->hdcBuf);
		SelectObject(obj->hdcBuf, obj->hbmpBuf);

		DeleteObject(obj->hbmpBuf);

		return 0;
	}

	case WM_SETFOCUS:
		Application::App()->setFocus(true);
		return 0;

	case WM_KILLFOCUS:
		Application::App()->setFocus(false);
		return 0;

	case WM_KEYDOWN:
		Application::App()->set_key_state(w, true);
		return 0;

	case WM_KEYUP:
		Application::App()->set_key_state(w, false);
		return 0;

	case WM_ERASEBKGND:
		return 1;

	case WM_PAINT:
	{
		win32_drawing_objects *obj = Application::App()->get_drawing_objects();
		const win32_window_dimensions *dim = Application::App()->get_window_dimension();

		SelectObject(obj->hdcBuf, GetStockObject(WHITE_BRUSH));
		Rectangle(obj->hdcBuf, 0, 0, dim->width, dim->height);

		Application::App()->draw(obj->hdcBuf); // USER FUNCTION

		DrawClock(obj->hdcBuf);
		obj->hdc = BeginPaint(win, &ps);
		BitBlt(obj->hdc, 0, 0, dim->width, dim->height, obj->hdcBuf, 0, 0, SRCCOPY);
		EndPaint(win, &ps);
		return 0;
	}
	break;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	default:
		break;
	}
	return DefWindowProc(win, msg, w, l);
}