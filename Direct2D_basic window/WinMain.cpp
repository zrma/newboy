#include "D2DUtils.h"

LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);

ID2D1Factory			*factory	= 0;
ID2D1HwndRenderTarget	*Rt			= 0;

void Display(DWORD timeDelta)
{
}
bool Setup()
{
	return true;
}
void Clean()
{
	SafeRelease(Rt);
	SafeRelease(factory);
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG msg = {0};
	WNDCLASS wc = {0};

	wc.hInstance = hInstance;
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = TEXT("Direct2D");
	wc.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&wc);
 
	hWnd = CreateWindow(TEXT("Direct2D"),TEXT("Direct2D"),
		WS_SYSMENU | WS_BORDER | WS_CAPTION | WS_MINIMIZEBOX,			//style
		CW_USEDEFAULT,CW_USEDEFAULT,									//x,y
		800, 600,														//width,height
		NULL,(HMENU)NULL,hInstance,NULL);

	if(FAILED(D2DInit(hWnd, 800, 600, &factory, &Rt)))
	{
		MessageBox(hWnd, TEXT("Direct2D 초기화 실패"), TEXT("에러"), MB_ICONERROR);
		Clean();
		return 0;
	}
	
	if(!Setup())
	{
		MessageBox(hWnd, TEXT("Setup 실패"), TEXT("에러"), MB_ICONERROR);
		Clean();
		return 0;
	}

	ShowWindow(hWnd,nCmdShow);
 
	DWORD last = 0L;
	while(msg.message != WM_QUIT)
	{
		if(PeekMessage(&msg,NULL,0,0,PM_REMOVE)) 
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			DWORD curr = timeGetTime();
			Display(curr - last);
			last = curr;
		}
	}
	Clean();
	return (int)msg.wParam;
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch(iMessage) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return (DefWindowProc(hWnd,iMessage,wParam,lParam));
}