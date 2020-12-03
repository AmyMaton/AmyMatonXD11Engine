#pragma once
#include "FakeWindows.h"
#include "Exception.h"
#include "Keyboard.h"

class Window
{
public:
	class Exception : public MyException
	{
	public:
		Exception(int line, const char* file, HRESULT hr) noexcept;
		const char* what() const noexcept override;
		virtual const char* GetType() const noexcept override;
		static std::string TranslateErrorCode(HRESULT hr) noexcept;
		HRESULT GetErrorCode() const noexcept;
		std::string GetErrorString() const noexcept;

	private:
		HRESULT hr;
	};

	class WindowClass
	{
	private:
		WindowClass() noexcept;
		~WindowClass();
		WindowClass(const WindowClass&) = delete;
		WindowClass& operator= (const WindowClass&) = delete;
		static constexpr const char* WindowsClassName = "DirectX11 Engine";
		static WindowClass wndClass;
		HINSTANCE hInst;
	public:
		static const char* GetName()noexcept;
		static HINSTANCE GetInstance() noexcept;
	};
public:
	Window(int width, int height, const char* name) ;
	~Window();
	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;
private: 
	int width;
	int height;
	HWND hWnd;
public:
	Keyboard keyboard;
private:
	static LRESULT CALLBACK HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	static LRESULT CALLBACK HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	LRESULT HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
};

// macro used to help with error exception
#define WND_EXCEPT(hr) Window::Exception(__LINE__,__FILE__, hr)
#define WND_LAST_EXCEPT() Window::Exception(__LINE__,__FILE__,GetLastError() )