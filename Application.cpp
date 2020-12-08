#include "Application.h"
#include <sstream>
#include <iomanip>
#include <Windows.h>

Application::Application()
	:
	wnd(1280,720,"This Is A Window Title")
{
}

int Application::Go()
{
	while (true)
	{
		if (const auto code = Window::ProcessMessages())
		{
			return *code;
		}
		DoFrameLogic();
		Sleep(1); //IDK WHAT THIS DOES BUT IT DOSENT BRICK MY CPU ANYMORE THANX DISCORD <3
	}
	
}

void Application::DoFrameLogic()
{
	const float t = timer.Peek();
	std::ostringstream oss;
	oss << "Time elapsed" << std::setprecision(1) << std::fixed << t << "s";
	wnd.SetTitle(oss.str());

	const float c = sin(timer.Peek());
	wnd.GFX().ClearBuffer(c, c, 1.0f);

	wnd.GFX().EndFrame();
}