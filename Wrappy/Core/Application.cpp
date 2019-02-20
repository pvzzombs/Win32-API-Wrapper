#include "Application.h"

time_t the_time;
struct tm *time_info;

const int WIN_WIDTH = 400;
const int WIN_HEIGHT = 400;
const int DIAMETER = 380;
const int OFFSET = (WIN_WIDTH - DIAMETER) / 2;
const int cX = WIN_WIDTH / 2;
const int cY = WIN_HEIGHT / 2;
const int DOT_SIZE = 20;

void DrawClock(HDC hdc)
{
	the_time = time(NULL);
	time_info = localtime(&the_time);

	Graphics graphics(hdc);

	Pen pen(Color(255, 0, 0, 0));

	SolidBrush brush(Color(255, 255, 255, 255));
	graphics.FillRectangle(&brush, 0, 0, WIN_WIDTH, WIN_HEIGHT);
	brush.SetColor(Color(255, 0, 0, 0));

	pen.SetWidth(2);
	graphics.DrawEllipse(&pen, OFFSET, OFFSET, DIAMETER, DIAMETER);

	/* Drawing central dot */
	graphics.FillEllipse(&brush, cX - (DOT_SIZE / 2), cY - (DOT_SIZE / 2), DOT_SIZE, DOT_SIZE);

	/* Hour Hand */
	double hAngle = ((360.0f / 12.0f) * time_info->tm_hour + (time_info->tm_min / 2.0f) + 270.0f) * _PI / 180.0f;
	float hR = DIAMETER / 2.0f - 30.0f;

	int hX = (int)(cX + hR * cos(hAngle));
	int hY = (int)(cY + hR * sin(hAngle));

	pen.SetWidth(5);
	graphics.DrawLine(&pen, cX, cY, hX, hY);

	/* Minute Hand */
	double mAngle = ((360.0f / 60.0f) * time_info->tm_min + 270.0f) * _PI / 180.0f;
	float mR = DIAMETER / 2.0f - 3.0f;

	int mX = (int)(cX + mR * cos(mAngle));
	int mY = (int)(cY + mR * sin(mAngle));

	pen.SetWidth(2);
	graphics.DrawLine(&pen, cX, cY, mX, mY);

	/* Second Hand */
	double sAngle = ((360.0f / 60.0f) * time_info->tm_sec + 270.0f) * _PI / 180.0f;
	float sR = DIAMETER / 2.0f - 3.0f;

	int sX = (int)(cX + mR * cos(sAngle));
	int sY = (int)(cY + mR * sin(sAngle));

	pen.SetWidth(1);
	graphics.DrawLine(&pen, cX, cY, sX, sY);

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

		graphics.DrawLine(&pen, stX, stY, eX, eY);

		std::wstring str = std::to_wstring((angle / 30) + 3);
		int fontSize = DIAMETER / 20;
		int offset = (int)ceil(fontSize / 4.0f);
		if (str.length() > 1) offset *= 2;

		float nX = (float)(eX - (DIAMETER * 0.1f) * cos(angleRad) - offset);
		float nY = (float)(eY - (DIAMETER * 0.1f) * sin(angleRad) - offset);

		SolidBrush  brush(Color(255, 0, 0, 0));
		FontFamily  fontFamily(L"Times New Roman");
		Font        font(&fontFamily, fontSize, FontStyleRegular, UnitPixel);
		PointF      pointF(nX, nY);

		graphics.DrawString(str.c_str(), str.length(), &font, pointF, &brush);
	}
}

namespace Wrappy
{
	Application::Application()
	{
		Window("Test", 400, 400);
	}

	Application::~Application()
	{
		endGDIplus();
		// TODO: Clean up
	}

	void Application::Run()
	{
		while (true);
	}

	void Application::Window(std::string title, int width, int height)
	{
		startGDIplus();
		registerWindowClass();

		RECT wr = { 0, 0, width, height };
		AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);

		m_handle = CreateWindowEx(
						0, windowClassName, title.c_str(),
						WS_OVERLAPPEDWINDOW,
						CW_USEDEFAULT, CW_USEDEFAULT, 
						wr.right - wr.left, wr.bottom - wr.top,
						NULL, NULL, GetModuleHandleW(NULL), NULL
		);

		if (!m_handle)
		{
			// TODO: Handle Error
		}

		ShowWindow(m_handle, SW_SHOW);
		UpdateWindow(m_handle);

		while (true)
		{
			processWindowsEvents();
		}
	}

	void Application::registerWindowClass()
	{
		WNDCLASS wc = { };
		wc.style = 0;
		wc.lpfnWndProc = &Application::WindowsEvents;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hInstance = GetModuleHandleW(NULL);
		wc.hIcon = NULL;
		wc.hCursor = 0;
		wc.hbrBackground = 0;
		wc.lpszMenuName = NULL;
		wc.lpszClassName = windowClassName;
		RegisterClass(&wc);
	}

	LRESULT CALLBACK Application::WindowsEvents(HWND win, UINT msg, WPARAM w, LPARAM l)
	{
		switch (msg)
		{
		case WM_CREATE:
			SetTimer(win, 1, 1000, NULL);
			break;

		case WM_TIMER:
			InvalidateRect(win, NULL, FALSE);
			break;

		case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(win, &ps);
			printf("Paint\n");
			DrawClock(hdc);
			EndPaint(win, &ps);
		}
		break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;

		default:
			return DefWindowProc(win, msg, w, l);
		}
		return 0;
	}

	void Application::processWindowsEvents()
	{
		MSG msg;
		while (PeekMessageW(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessageW(&msg);
		}
	}
	void Application::startGDIplus()
	{
		GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
	}

	void Application::endGDIplus()
	{
		GdiplusShutdown(gdiplusToken);
	}
}