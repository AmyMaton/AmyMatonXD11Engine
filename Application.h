#pragma once
#include "Window.h"
#include "Timer.h"


class Application
{
public:
	Application();
	//messzage loop
	int Go();
private:
	void DoFrameLogic();
private:
	Window wnd;
	Timer timer;
};