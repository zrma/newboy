#pragma once
class CRMSingletonLoop
{
public:
	CRMSingletonLoop(void);
	~CRMSingletonLoop(void);

	HRESULT Initialize();		// 초기화
	void	RunMessageLoop();	// 메시지 처리

	// 이곳에서 렌더러를 생성하고, 그려주고, 해제 하는 일련의 처리들을 함

public:
	int Run(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPTSTR lpCmdLine, _In_ int nCmdShow);


public:
	CRMSingletonLoop*	GetInstance();
	void				ReleaseInstance();

private:
	static CRMSingletonLoop* m_pInstance;
};

static ATOM				MyRegisterClass(HINSTANCE hInstance);
static BOOL				InitInstance(HINSTANCE hInstance, int nCmdShow);
static LRESULT CALLBACK WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam );