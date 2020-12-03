#include "Window.h"

int CALLBACK WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	try
	{
		//create multiple windows
		Window wnd(1280, 720, "Uni3D");
		//Window wnd2(200, 650, "Uni3Dmk2");

		MSG msg;
		BOOL Result;
		while ((Result = GetMessage(&msg, nullptr, 0, 0)) > 0)
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			//Keyboard Test
			if (wnd.keyboard.IsKeyPressed(VK_MENU))
			{
				MessageBox(nullptr, "alt Key was pressed", "alt key was pressed", MB_OK | MB_ICONEXCLAMATION);
			}
		}

		if (Result == -1)
		{
			return -1;
		}

		return msg.wParam;
	}
	catch (const MyException & e)
	{
		MessageBox(nullptr, e.what(), e.GetType(), MB_OK | MB_ICONEXCLAMATION);
	}
	catch (const std::exception & e)
	{
		MessageBox(nullptr, e.what(), "Exception is Standard", MB_OK | MB_ICONEXCLAMATION);
	}
	catch (...)
	{
		MessageBox(nullptr, "No details here", "Unknown Exception", MB_OK | MB_ICONEXCLAMATION);
	}

	return -1;
	
}