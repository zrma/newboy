#include "D2DUtils.h"

HRESULT D2DInit(HWND hWnd, int width, int height,
	ID2D1Factory **factory, ID2D1HwndRenderTarget **Rt)
{
	HRESULT hr;

	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, factory);
	if(FAILED(hr))
		return hr;

	return (*factory)->CreateHwndRenderTarget(D2D1::RenderTargetProperties(), D2D1::HwndRenderTargetProperties(hWnd, D2D1::SizeU(width, height)), Rt);
}