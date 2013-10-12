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

// 전역 변수:
HINSTANCE hInst;								// 현재 인스턴스입니다.
// TCHAR szTitle[MAX_LOADSTRING];				// 제목 표시줄 텍스트입니다.
TCHAR szWindowClass[MAX_LOADSTRING];			// 기본 창 클래스 이름입니다.

int CRMSingletonLoop::Main(_In_ HINSTANCE hInstance,
						_In_opt_ HINSTANCE hPrevInstance,
						_In_ LPTSTR    lpCmdLine,
						_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: 여기에 코드를 입력합니다.
	MSG msg;
	HACCEL hAccelTable;


	// 전역 문자열을 초기화합니다.
	// LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_OLDBOY, szWindowClass, MAX_LOADSTRING);
	
	MyRegisterClass(hInstance);
	// 이 함수 + 밑에 나올 InitInstance의 내부 CreateWindow() + ShowWindow() 함수를 뽑아 묶어서
	// WindowInitialize 함수를 만든다.

	/*
		옮길 코드
	*/
	// 응용 프로그램 초기화를 수행합니다.
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_OLDBOY));

	// 기본 메시지 루프입니다.
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
//  함수: MyRegisterClass()
//
//  목적: 창 클래스를 등록합니다.
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

		MSDN에서의 명시
		ATOM WINAPI RegisterClass(_In_  const WNDCLASS *lpWndClass);

		함수의 인수로는 WNDCLASS 구조체의 번지(주소)를 전달한다.
		앞으로 위와 같은 특성을 가진 윈도우를 사용하겠다고 등록하는 절차이다.
		운영체제는 이 윈도우 클래스의 특성을 잘 기억해 놓는다.
		윈도우 클래스를 등록한 프로그램은 WNDCLASS 구조체의 hInstance 멤버변수에 전달된 인스턴스를 
		가진 프로그램 이며 전달되는 메세지는 마찬가지로 WNDCLASS 구조체의 lpfnWndProc 멤버변수에 
		전달된 함수가 처리하도록 되어있다.

		MSDN 명시
		ATOM WINAPI RegisterClassEx(_In_  const WNDCLASSEX *lpwcx);

		RegisterClass 함수와 차이가 거의 없다봐도 무방하나 WNDCLASSEX 구조체에 대응하기 위한 함수이다.
		WNDCLASSEX 구조체의 멤버변수가 2개가 더 늘어남으로 인해서(cbSize, hIconSm)그에 맞추기 위함인 듯하다.
		WNDCALSSEX 구조체로 선언된 변수의 주소를 마찬가지로 운영체제에 넘겨주는 역할을 한다.

		참고 및 출처

		RegisterClass 함수의 포스트 링크
		http://blog.daum.net/ledda123/27

		RegisterClassEx 함수의 포스트 링크
		http://blog.daum.net/ledda123/28

		WNDCLASS 관련 포스트 링크
		http://blog.daum.net/ledda123/11

		WNDCLASSEX 구조체의 포스트 링크
		http://blog.daum.net/ledda123/12

	*/
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   목적: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   설명:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//

//	메인 윈도우 생성 함수
//	Loop 싱글톤 안으로 집어넣어야 됨 - 생성자 안에 넣으면 안 되는 이유?
//
//	생성자 안에는 if문 등의 복잡한 구문을 구현하지 않는다!

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;

	hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

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

//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//  목적: 주 창의 메시지를 처리합니다.
//
//	1. WndProc 함수를 Main.c 파일에서 꺼내옴
//	2. 다이얼로그 처리 부분을 제거(WM_COMMAND)
//
//	그 결과 이렇게 간결한 코드가 나옴

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