#include<Windows.h>


int APIENTRY WinMain(
	_In_ HINSTANCE const hInstance,
	_In_opt_ HINSTANCE const prevhInstance,
	_In_ LPSTR const lpCmdLine,
	_In_ int const nShowCmd
) {
	HWND hWindow = nullptr;

	{
		WNDCLASSEX wndClass = WNDCLASSEX();

		wndClass.cbSize = sizeof(WNDCLASSEX);
		wndClass.lpfnWndProc = nullptr;
		wndClass.hInstance = hInstance;
		wndClass.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
		wndClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
		wndClass.hbrBackground = static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
		wndClass.lpszClassName = "Window";
		wndClass.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);

		RegisterClassEx(&wndClass);
	}
}