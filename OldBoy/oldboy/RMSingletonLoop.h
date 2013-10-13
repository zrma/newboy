#pragma once
class CRMSingletonLoop
{
public:
	CRMSingletonLoop(void);
	~CRMSingletonLoop(void);

	HRESULT Initialize();		// �ʱ�ȭ
	void	RunMessageLoop();	// �޽��� ó��

	// �̰����� �������� �����ϰ�, �׷��ְ�, ���� �ϴ� �Ϸ��� ó������ ��

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