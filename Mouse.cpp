#include "Mouse.h"
#include <Windows.h>
#include "FakeWindows.h"

std::pair<int, int> Mouse::GetPos() const noexcept
{
	return { x,y };
}

int Mouse::GetPosX() const noexcept
{
	return x;
}

int Mouse::GetPosY() const noexcept
{
	return y;
}

bool Mouse::LeftIsPressedDown() const noexcept
{
	return leftIsPressedDown;
}

bool Mouse::RightIsPressedDown() const noexcept
{
	return rightIsPressedDown;
}

Mouse::Event Mouse::Read() noexcept
{
	if (buffer.size() > 0u)
	{
		Mouse::Event e = buffer.front();
		buffer.pop();
		return e;
	}
	else
	{
		return Mouse::Event();
	}
}

void Mouse::Flush() noexcept
{
	buffer = std::queue<Event>();
}

void Mouse::OnMouseMove(int newx, int newy) noexcept
{
	x = newx;
	y = newy;

	buffer.push(Mouse::Event(Mouse::Event::Type::Movement, *this));
	TrimBuffer();
}

void Mouse::OnLeftPressed(int x, int y) noexcept
{
	leftIsPressedDown = true;

	buffer.push(Mouse::Event(Mouse::Event::Type::LeftPress, *this));
	TrimBuffer();
}

void Mouse::OnLeftReleased(int x, int y) noexcept
{
	leftIsPressedDown = false;

	buffer.push(Mouse::Event(Mouse::Event::Type::LeftRelease, *this));
	TrimBuffer();
}

void Mouse::OnRightPressed(int x, int y) noexcept
{
	rightIsPressedDown = true;

	buffer.push(Mouse::Event(Mouse::Event::Type::RightPress, *this));
	TrimBuffer();
}

void Mouse::OnRightReleased(int x, int y) noexcept
{
	rightIsPressedDown = false;

	buffer.push(Mouse::Event(Mouse::Event::Type::RightRelease, *this));
	TrimBuffer();
}

void Mouse::OnWheelUp(int x, int y) noexcept
{
	buffer.push(Mouse::Event(Mouse::Event::Type::WheelUp, *this));
	TrimBuffer();
}

void Mouse::OnWheelDown(int x, int y) noexcept
{
	buffer.push(Mouse::Event(Mouse::Event::Type::WheelDown, *this));
	TrimBuffer();
}

void Mouse::TrimBuffer() noexcept
{
	while (buffer.size() > bufferSize)
	{
		buffer.pop();
	}
}

bool Mouse::IsMouseInWindow() const noexcept
{
	return isInWindow;
}

void Mouse::OnMouseEnterWindow() noexcept
{
	isInWindow = true;
	buffer.push(Mouse::Event(Mouse::Event::Type::EnterWindow, *this));
}

void Mouse::OnMouseLeaveWindow() noexcept
{
	isInWindow = false;
	buffer.push(Mouse::Event(Mouse::Event::Type::LeaveWindow, *this));
}

void Mouse::OnWheelDelta(int x, int y, int delta) noexcept
{
	wheelDeltaCarry += delta;
	while (wheelDeltaCarry >= WHEEL_DELTA)
	{
		wheelDeltaCarry -= WHEEL_DELTA;
		OnWheelUp(x, y);
	}
	while (wheelDeltaCarry <= -WHEEL_DELTA)
	{
		wheelDeltaCarry -= WHEEL_DELTA;
		OnWheelDown(x, y);
	}
}