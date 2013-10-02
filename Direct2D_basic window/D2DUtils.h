
#include <d2d1.h>
#include <d2d1helper.h>

#define SafeRelease(T)	if(T){T->Release(); T = 0; }
#define SafeDelete(T)	if(T){delete T; T = 0; }

HRESULT D2DInit(HWND hWnd, int width, int height,
				ID2D1Factory **factory, ID2D1HwndRenderTarget **Rt);