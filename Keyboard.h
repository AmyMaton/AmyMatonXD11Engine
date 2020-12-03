#pragma once
#include <bitset>
#include <queue>

class Keyboard
{
	friend class Window;
public:
	class Event
	{
	public:
		enum class Type
		{
			Pressed,
			Released,
			Invalid,
		};
	private:
		Type type;
		unsigned char code;
	public:
		Event() noexcept
			:
			type(Type::Invalid),
			code (0u)
		{}
		Event(Type type, unsigned char code) noexcept
			:
			type(type),
			code(code)
		{}
		bool IsPressed() const noexcept
		{
			return type == Type::Pressed;
		}
		bool IsReleased() const noexcept
		{
			return type == Type::Released;
		}
		bool Isvaild() const noexcept
		{
			return type == Type::Invalid;
		}
		unsigned char GetCode() const noexcept
		{
			return code;
		}
		
	};

public:
	Keyboard() = default;
	Keyboard(const Keyboard&) = delete;
	Keyboard& operator=(const Keyboard&) = delete;

	//Key Event Handling
	bool IsKeyPressed(unsigned char keycode) const noexcept;
	Event ReadKey() noexcept;
	bool KeyIsEmpty() const noexcept;
	void FlushKey() noexcept;

	//Character Event Handling
	char ReadCharacter() noexcept;
	bool CharacterIsEmpty() const noexcept;
	void FlushCharacter() noexcept;
	void Flush() noexcept;

	//Autorepeat Controller
	void EnableAutoRepeat() noexcept;
	void DisableAutoRepeat() noexcept;
	bool IsAutoRepeatEnabled() const noexcept;

private:
	void OnKeyPressed(unsigned char keycode) noexcept;
	void OnKeyReleased(unsigned char keycode) noexcept;
	void OnCharater(char character) noexcept;
	void ClearState() noexcept;
	template<typename T>
	static void TrimTheBuffer(std::queue <T >&buffer) noexcept;
private:
	static constexpr unsigned int nKeys = 256u;
	static constexpr unsigned int BufferSize = 16u;
	bool isautorepeatenabled = false;
	std::bitset<nKeys> keystates;
	std::queue<Event> keybuffer;
	std::queue<char> characterbuffer;

};