#include "DisplayWin32.h"


LRESULT CALLBACK WndProc(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam)
{
	switch (umessage)
	{
		case WM_KEYDOWN:
		{
			// If a key is pressed, send it to the input object so it can record that state.
			std::cout << "Key: " << static_cast<unsigned int>(wparam) << std::endl;

			if (static_cast<unsigned int>(wparam) == 27) PostQuitMessage(0);
			else if ((static_cast<unsigned int>(wparam) == 37)) //�����
			{
				PostMessage(hwnd, VK_LEFT, wparam, lparam);
			}
			else if ((static_cast<unsigned int>(wparam) == 39)) //������
			{
				PostMessage(hwnd, VK_RIGHT, wparam, lparam);
			}
			return 0;
		}
		default:
		{
			return DefWindowProc(hwnd, umessage, wparam, lparam);
		}
	}
}


DisplayWin32::DisplayWin32(long clientHeight, long clientWidth, HINSTANCE hInstance, LPCWSTR appName)
{
	WNDCLASSEX wc;

	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(nullptr, IDI_WINLOGO);
	wc.hIconSm = wc.hIcon;
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hbrBackground = static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH));
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = appName;
	wc.cbSize = sizeof(WNDCLASSEX);

	// Register the window class.
	RegisterClassEx(&wc);


	RECT windowRect = { 0, 0, clientWidth, clientHeight };
	AdjustWindowRect(&windowRect, WS_OVERLAPPEDWINDOW, FALSE);

	auto dwStyle = WS_SYSMENU | WS_CAPTION | WS_MINIMIZEBOX | WS_THICKFRAME;

	auto posX = (GetSystemMetrics(SM_CXSCREEN) - clientWidth) / 2;
	auto posY = (GetSystemMetrics(SM_CYSCREEN) - clientHeight) / 2;

	hWnd = CreateWindowEx(WS_EX_APPWINDOW, appName, appName,
		dwStyle,
		posX, posY,
		windowRect.right - windowRect.left,
		windowRect.bottom - windowRect.top,
		nullptr, nullptr, hInstance, nullptr);

	ShowWindow(hWnd, SW_SHOW);
	SetForegroundWindow(hWnd);
	SetFocus(hWnd);

	ShowCursor(true);
}
