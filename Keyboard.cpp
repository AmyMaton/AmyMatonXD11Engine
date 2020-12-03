#include "Keyboard.h"

bool Keyboard::IsKeyPressed(unsigned char keycode) const noexcept
{
	return keystates[keycode];
}

Keyboard::Event Keyboard::ReadKey() noexcept
{
	if (keybuffer.size() > 0u)
	{
		Keyboard::Event e = keybuffer.front();
		keybuffer.pop();
		return e;
	}
	else
	{
		return Keyboard::Event();
	}
}  

bool Keyboard::KeyIsEmpty() const noexcept
{
	return keybuffer.empty();
}

char Keyboard::ReadCharacter() noexcept
{
	if (characterbuffer.size() > 0u)
	{
		unsigned char charactercode = characterbuffer.front();
		characterbuffer.pop();
		return charactercode;
	}
	else
	{
		return 0;
	}
}

bool Keyboard::CharacterIsEmpty() const noexcept
{
	return characterbuffer.empty();
}

void Keyboard::FlushKey() noexcept
{
	keybuffer = std::queue<Event>();
}

void Keyboard::FlushCharacter() noexcept
{
	characterbuffer = std::queue<char>();
}

void Keyboard::Flush() noexcept
{
	FlushKey();
	FlushCharacter();
}

void Keyboard::EnableAutoRepeat() noexcept
{
	isautorepeatenabled = true;
}

void Keyboard::DisableAutoRepeat() noexcept
{
	isautorepeatenabled = false;
}

bool Keyboard::IsAutoRepeatEnabled() const noexcept
{
	return isautorepeatenabled;
}

void Keyboard::OnKeyPressed(unsigned char keycode) noexcept
{
	keystates[keycode] = true;
	keybuffer.push(Keyboard::Event(Keyboard::Event::Type::Pressed, keycode));
	TrimTheBuffer(keybuffer);
}

void Keyboard::OnKeyReleased(unsigned char keycode) noexcept
{
	keystates[keycode] = false;
	keybuffer.push(Keyboard::Event(Keyboard::Event::Type::Released, keycode));
	TrimTheBuffer(keybuffer);
}

void Keyboard::OnCharater(char character) noexcept
{
	characterbuffer.push(character);
	TrimTheBuffer(characterbuffer);
}

void Keyboard::ClearState() noexcept
{
	keystates.reset();
}

template<typename T>
void Keyboard::TrimTheBuffer(std::queue<T>& buffer) noexcept
{
	while (buffer.size() > BufferSize)
	{
		buffer.pop();
	}
}