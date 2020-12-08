#include "Window.h"
#include <sstream>
#include "Application.h"

int CALLBACK WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	try
	{
	return Application{}.Go();
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