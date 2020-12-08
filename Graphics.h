#pragma once
#include "FakeWindows.h"
#include <d3d11.h>

class Graphics
{
public:
	Graphics(HWND hWnd);
	Graphics(const Graphics&) = delete;
	Graphics& operator=(const Graphics&) = delete;
	~Graphics();
	
	void EndFrame();
	void ClearBuffer(float red, float green, float blue) noexcept
	{
		const float colour[] = { red,green,blue,1.0f };
		PointerContext->ClearRenderTargetView(PointerTarget,colour);
	}
private:
	ID3D11Device* PointerDevice = nullptr;
	IDXGISwapChain* PointerSwap = nullptr;
	ID3D11DeviceContext* PointerContext = nullptr;
	ID3D11RenderTargetView* PointerTarget = nullptr;
};