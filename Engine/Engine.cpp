#include<Windows.h>

namespace Pipeline{
	void Procedure(HWND const hWindow, UINT const uMessage, WPARAM const wParameter, LPARAM const lParameter);
}

namespace Engine
{
	LRESULT CALLBACK Procedure(HWND const hWindow, UINT const uMessage, WPARAM const wParameter, LPARAM const lParameter)
	{
		switch (uMessage)
		{
		case WM_CREATE:
		{
			Pipeline::Procedure(hWindow, uMessage, wParameter, lParameter);
			return 0;
		}
		case WM_APP:
		{
			Pipeline::Procedure(hWindow, uMessage, wParameter, lParameter);
			return 0;
		}
		case WM_MOUSEWHEEL: case WM_MOUSEHWHEEL: case WM_MOUSEMOVE:
		case WM_KEYDOWN: case WM_LBUTTONDOWN: case WM_RBUTTONDOWN:
		case WM_KEYUP: case WM_LBUTTONUP: case WM_RBUTTONUP:
		case WM_SYSKEYDOWN: case WM_MBUTTONDOWN: case WM_XBUTTONDOWN:
		case WM_SYSKEYUP: case WM_MBUTTONUP: case WM_XBUTTONUP:
		{
			return 0;
		}
		case WM_DESTROY:
		{
			Pipeline::Procedure(hWindow, uMessage, wParameter, lParameter);
			PostQuitMessage(0);
			return 0;
		}
		case WM_SIZE:
		{
			Pipeline::Procedure(hWindow, uMessage, wParameter, lParameter);
			return 0;
		}
		default:
		{
			return DefWindowProc(hWindow, uMessage, wParameter, lParameter);
		}

		}
		return 0;
	}
}