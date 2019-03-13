#ifndef WIN32_EVENT_HANDLER_H
#define WIN32_EVENT_HANDLER_H
#include <windows.h>
static LRESULT CALLBACK windows_event_handler(HWND win, UINT msg, WPARAM w, LPARAM l)
{
    PAINTSTRUCT ps;

    switch (msg)
    {
    case WM_CREATE:
        win32_drawing_objects *obj = Application::App()->get_drawing_objects();
        win32_window_dimensions *dim = Application::App()->get_window_dimension();

        obj->hdc = GetDC(win);
        obj->hdcBuf = CreateCompatibleDC(obj->hdc);
        obj->hbmpBuf = CreateCompatibleBitmap(obj->hdcBuf, dim->width, dim->height);
        obj->gfxBuf = Graphics::FromHDC(obj->hdcBuf);
        SelectObject(obj->hdcBuf, obj->hbmpBuf);

        /* Alt Code */
        // TODO: If this works then remove out of drawing objects and just make a temporary.
        DeleteObject(obj->hbmpBuf);
        /* End Alt Code */
        return 0;

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
        win32_window_dimensions *dim = Application::App()->get_window_dimension();

        /* Alt Code */
        SelectObject(obj->hdcBuf, GetStockObject(WHITE_BRUSH));
        Rectangle(obj->hdcBuf, 0, 0, dim->width, dim->height);
        Application::App()->draw(obj->hdcBuf); // USER FUNCTION
        DrawClock(obj->hdcBuf);
        obj->hdc = BeginPaint(win, &ps);
        BitBlt(obj->hdc, 0, 0, dim->width, dim->height, obj->hdcBuf, 0, 0, SRCCOPY);
        EndPaint(win, &ps);
        /* End Alt Code */

        //HDC temp = BeginPaint(win, &ps);
        /* Start :: Custom Drawing*/
        //Application::App()->draw(temp);
        //DrawClock(Application::App()->gfx_buffer());
        /* End :: Custom Drawing*/
        //BitBlt(temp, 0, 0, dim->width, dim->height, obj->hdcBuf, 0, 0, SRCCOPY);
        //EndPaint(win, &ps);
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

#endif