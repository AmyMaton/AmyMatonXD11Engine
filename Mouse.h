#pragma once
#include <queue>

class Mouse
{
	friend class Window;
public:
	class Event
	{
	public:
		enum class Type
		{
			LeftPress,
			LeftRelease,
			RightPress,
			RightRelease,
			WheelUp,
			WheelDown,
			Movement,
			Invalid,
			EnterWindow,
			LeaveWindow
		};
	private:
		Type type;
		bool leftIsPressedDown;
		bool rightIsPressedDown;
		int x;
		int y;
	public:
		Event() noexcept
			:
			type(Type::Invalid),
			leftIsPressedDown(false),
			rightIsPressedDown(false),
			x(0),
			y(0)
		{}
		Event(Type type, const Mouse& parent) noexcept
			:
			type(type),
			leftIsPressedDown(parent.leftIsPressedDown),
			rightIsPressedDown(parent.rightIsPressedDown),
			x(parent.x),
			y(parent.y)
		{}
		bool IsValid() const noexcept
		{
			return type != Type::Invalid;
		}
		Type GetType() const noexcept
		{
			return type;
		}
		std::pair<int, int> GetPos() const noexcept
		{
			return{ x,y };
		}
		int GetPosX() const noexcept
		{
			return x;
		}
		int GetPosY() const noexcept
		{
			return y;
		}
		bool LeftIsPressed() const noexcept
		{
			return leftIsPressedDown;
		}
		bool RightIsPressed() const noexcept
		{
			return rightIsPressedDown;
		}
	};
public:
	Mouse() = default;
	Mouse(const Mouse&) = delete;
	Mouse& operator=(const Mouse&) = delete;
	std::pair<int, int> GetPos() const noexcept;
	int GetPosX() const noexcept;
	int GetPosY() const noexcept;
	bool LeftIsPressedDown() const noexcept;
	bool RightIsPressedDown() const noexcept;
	Mouse::Event Read() noexcept;

	bool IsMouseInWindow() const noexcept;

	bool IsEmpty() const noexcept
	{
		return buffer.empty();
	}
	void Flush() noexcept;
private:
	void OnMouseMove(int x, int y) noexcept;
	void OnLeftPressed(int x, int y) noexcept;
	void OnLeftReleased(int x, int y) noexcept;
	void OnRightPressed(int x, int y) noexcept;
	void OnRightReleased(int x, int y) noexcept;
	void OnWheelUp(int x, int y) noexcept;
	void OnWheelDown(int x, int y) noexcept;
	void TrimBuffer() noexcept;

	void OnMouseLeaveWindow() noexcept;
	void OnMouseEnterWindow() noexcept;

	void OnWheelDelta(int x, int y, int delta) noexcept;

private:
	static constexpr unsigned int bufferSize = 16u;
	int x;
	int y;
	bool leftIsPressedDown = false;
	bool rightIsPressedDown = false;
	std::queue<Event> buffer;

	bool isInWindow = false;
	int wheelDeltaCarry = 0;
};