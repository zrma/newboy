#pragma once
class CRMSingletonLoop
{
public:
	CRMSingletonLoop(void);
	~CRMSingletonLoop(void);

	int Main(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPTSTR lpCmdLine, _In_ int nCmdShow);
};

static LRESULT CALLBACK WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam );