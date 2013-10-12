#include "RMInclude.h"
#include "RMSingletonLoop.h"

#define MAX_LOADSTRING 100


CRMSingletonLoop::CRMSingletonLoop(void)
{
}


CRMSingletonLoop::~CRMSingletonLoop(void)
{
}

static ATOM				MyRegisterClass(HINSTANCE hInstance);
static BOOL				InitInstance(HINSTANCE, int);
static LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);

// ���� ����:
HINSTANCE hInst;								// ���� �ν��Ͻ��Դϴ�.
// TCHAR szTitle[MAX_LOADSTRING];				// ���� ǥ���� �ؽ�Ʈ�Դϴ�.
TCHAR szWindowClass[MAX_LOADSTRING];			// �⺻ â Ŭ���� �̸��Դϴ�.

int CRMSingletonLoop::Main(_In_ HINSTANCE hInstance,
						_In_opt_ HINSTANCE hPrevInstance,
						_In_ LPTSTR    lpCmdLine,
						_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: ���⿡ �ڵ带 �Է��մϴ�.
	MSG msg;
	HACCEL hAccelTable;


	// ���� ���ڿ��� �ʱ�ȭ�մϴ�.
	// LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_OLDBOY, szWindowClass, MAX_LOADSTRING);
	
	MyRegisterClass(hInstance);
	// �� �Լ� + �ؿ� ���� InitInstance�� ���� CreateWindow() + ShowWindow() �Լ��� �̾� ���
	// WindowInitialize �Լ��� �����.

	/*
		�ű� �ڵ�
	*/
	// ���� ���α׷� �ʱ�ȭ�� �����մϴ�.
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_OLDBOY));

	// �⺻ �޽��� �����Դϴ�.
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}

//
//  �Լ�: MyRegisterClass()
//
//  ����: â Ŭ������ ����մϴ�.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_OLDBOY));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= NULL;
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
	/*
		ATOM RegisterClass(CONST WNDCLASS *lpWndClass);

		MSDN������ ���
		ATOM WINAPI RegisterClass(_In_  const WNDCLASS *lpWndClass);

		�Լ��� �μ��δ� WNDCLASS ����ü�� ����(�ּ�)�� �����Ѵ�.
		������ ���� ���� Ư���� ���� �����츦 ����ϰڴٰ� ����ϴ� �����̴�.
		�ü���� �� ������ Ŭ������ Ư���� �� ����� ���´�.
		������ Ŭ������ ����� ���α׷��� WNDCLASS ����ü�� hInstance ��������� ���޵� �ν��Ͻ��� 
		���� ���α׷� �̸� ���޵Ǵ� �޼����� ���������� WNDCLASS ����ü�� lpfnWndProc ��������� 
		���޵� �Լ��� ó���ϵ��� �Ǿ��ִ�.

		MSDN ���
		ATOM WINAPI RegisterClassEx(_In_  const WNDCLASSEX *lpwcx);

		RegisterClass �Լ��� ���̰� ���� ���ٺ��� �����ϳ� WNDCLASSEX ����ü�� �����ϱ� ���� �Լ��̴�.
		WNDCLASSEX ����ü�� ��������� 2���� �� �þ���� ���ؼ�(cbSize, hIconSm)�׿� ���߱� ������ ���ϴ�.
		WNDCALSSEX ����ü�� ����� ������ �ּҸ� ���������� �ü���� �Ѱ��ִ� ������ �Ѵ�.

		���� �� ��ó

		RegisterClass �Լ��� ����Ʈ ��ũ
		http://blog.daum.net/ledda123/27

		RegisterClassEx �Լ��� ����Ʈ ��ũ
		http://blog.daum.net/ledda123/28

		WNDCLASS ���� ����Ʈ ��ũ
		http://blog.daum.net/ledda123/11

		WNDCLASSEX ����ü�� ����Ʈ ��ũ
		http://blog.daum.net/ledda123/12

	*/
}

//
//   �Լ�: InitInstance(HINSTANCE, int)
//
//   ����: �ν��Ͻ� �ڵ��� �����ϰ� �� â�� ����ϴ�.
//
//   ����:
//
//        �� �Լ��� ���� �ν��Ͻ� �ڵ��� ���� ������ �����ϰ�
//        �� ���α׷� â�� ���� ���� ǥ���մϴ�.
//

//	���� ������ ���� �Լ�
//	Loop �̱��� ������ ����־�� �� - ������ �ȿ� ������ �� �Ǵ� ����?
//
//	������ �ȿ��� if�� ���� ������ ������ �������� �ʴ´�!

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;

	hInst = hInstance; // �ν��Ͻ� �ڵ��� ���� ������ �����մϴ�.

	hWnd = CreateWindow(szWindowClass, L"Rhythm Match v1.0", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//  �Լ�: WndProc(HWND, UINT, WPARAM, LPARAM)
//  ����: �� â�� �޽����� ó���մϴ�.
//
//	1. WndProc �Լ��� Main.c ���Ͽ��� ������
//	2. ���̾�α� ó�� �κ��� ����(WM_COMMAND)
//
//	�� ��� �̷��� ������ �ڵ尡 ����

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	
	return 0;
}