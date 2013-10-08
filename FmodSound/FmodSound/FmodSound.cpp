// FmodSound.cpp : ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include "FmodSound.h"
#include <stdio.h>

// -- Fmod API�� ����ϱ� ���� ����
#include <fmod.h>
#include <fmod.hpp>
#include <fmod_errors.h>

// #pragma  comment( lib, "fmodex_vc.lib" )
// -- ������� 

#define MAX_LOADSTRING 100

// ���� ����:
HINSTANCE hInst;								// ���� �ν��Ͻ��Դϴ�.
TCHAR szTitle[MAX_LOADSTRING];					// ���� ǥ���� �ؽ�Ʈ�Դϴ�.
TCHAR szWindowClass[MAX_LOADSTRING];			// �⺻ â Ŭ���� �̸��Դϴ�.

// �� �ڵ� ��⿡ ��� �ִ� �Լ��� ������ �����Դϴ�.
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

// -- Fmod �׽�Ʈ�� �Լ�
void InitSound();
void LoadSound();
void PLAYsound();
void DeleteSound();

//-- ��ư ������ �ڵ��� ���� ���� ���� �� �ʱ�ȭ
HWND hWndButton = NULL;

//-- Fmod ����� ���� ���� ���� ���� �� �ʱ�ȭ
FMOD::System *systemS = NULL;
FMOD::Sound *sound = NULL;
FMOD::Channel *channel = NULL;

//-- ������ �̵��� �Լ� ����
void SetMoveWindow(HWND hWnd, WPARAM wParam);


int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
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
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_FMODSOUND, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// ���� ���α׷� �ʱ�ȭ�� �����մϴ�.
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_FMODSOUND));

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
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_FMODSOUND));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_FMODSOUND);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
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
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;
	hInst = hInstance; // �ν��Ͻ� �ڵ��� ���� ������ �����մϴ�.

	hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//
//  �Լ�: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ����: �� â�� �޽����� ó���մϴ�.
//
//  WM_COMMAND	- ���� ���α׷� �޴��� ó���մϴ�.
//  WM_PAINT	- �� â�� �׸��ϴ�.
//  WM_DESTROY	- ���� �޽����� �Խ��ϰ� ��ȯ�մϴ�.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;


	//-- Fmod���� ���� ������ �ϱ� ���� ����
	float	fVolume = 0;
	bool	isMute = false;
	bool	isPlaying = false;
	bool	isPaused = false;
	//-- �������

	switch (message)
	{
	
		// �߰� ����

	case WM_KEYDOWN:
		SetMoveWindow(hWnd, wParam);
	break;

		//-- �߰� �� �ڵ�
	case WM_CREATE:
		{
			// �ʱ� ���� �ÿ��� �� �� �ѷ��ִ� ��ư
			if(hWndButton == NULL)
			{
				hWndButton = CreateWindowA("button", "Play", WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,
					100,100, 80,40, hWnd, (HMENU)100, NULL, NULL );
			
				InitSound();
				LoadSound();
			}
			// �������

			CreateWindowA("button", "Stop", WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,
				200,100, 80,40, hWnd, (HMENU)101, NULL, NULL );
			CreateWindowA("button", "Change", WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,
				300,100, 80,40, hWnd, (HMENU)102, NULL, NULL );
			CreateWindowA("button", "Vol +", WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,
				100,200, 80,40, hWnd, (HMENU)200, NULL, NULL );
			CreateWindowA("button", "Vol -", WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,
				200,200, 80,40, hWnd, (HMENU)201, NULL, NULL );
			CreateWindowA("button", "Mute", WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,
				300,200, 80,40, hWnd, (HMENU)202, NULL, NULL );

			// ��ư�� �߰��ϰ� �� ���� �ٷ� ���� WM_COMMAND���� �Ľ� �� �޴� �ε����� ������.
		}
		break;
		//-- �������

	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// �޴� ������ ���� �м��մϴ�.
		switch (wmId)
		{

			//-- �ӽ÷� �߰��� ���� ��ư�� ���� �� �ε����� ��ɾ��
		case 100:
			channel->isPlaying(&isPlaying);

			if(!isPlaying)
			{
				PLAYsound();
				// ��� ����
				SetWindowTextA(hWndButton, "Pause");
			}
			else
			// ��� ��
			{
				isPaused = false;
				channel->getPaused(&isPaused);
				
				if(isPaused)
				{
					channel->setPaused(false);
					// ��� ��
					SetWindowTextA(hWndButton, "Pause");
				}
				else
				{
					channel->setPaused(true);
					// �Ͻ� ���� ����
					SetWindowTextA(hWndButton, "Play Again");
				}
			}
			break;

		case 101:
			channel->stop();
			// ���� ����
			SetWindowTextA(hWndButton, "Play");
			break;

		case 102:
			channel->stop();
			break;

		case 200:
			channel->getMute(&isMute);
			if(isMute)
			{
				channel->setVolume(0);
				channel->setMute(false);
			}

			channel->getVolume(&fVolume);
			
			if(fVolume < 1)
				channel->setVolume(fVolume + static_cast<float>(0.1));
			else
				channel->setVolume(1);
			break;

		case 201:
			channel->getVolume(&fVolume);
			if(fVolume > 0.1)
				channel->setVolume(fVolume - static_cast<float>(0.1));
			else
				channel->setVolume(0);
			break;
			
		case 202:
			channel->getMute(&isMute);
			if(isMute)
				channel->setMute(false);
			else
				channel->setMute(true);
			break;
			//-- �������

		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: ���⿡ �׸��� �ڵ带 �߰��մϴ�.

		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:

		//-- Fmod ������ ��ü ����
		DeleteSound();
		//-- �������

		PostQuitMessage(0);
		/*	���� ���μ����� �����ϴ� �Լ�
		
			���α׷� ���Ḧ �õ��ϸ�(x ��ư => �ݱ⸦ ������)
			â�� �ݰ� WM_DESTROY �޽����� ����.
		
			WM_DESTORY �޽����� ���⼭ ĳġ�ؼ� PostQuitMessage() api�� ȣ���Ͽ� ���� ���μ����� ������.
		*/

		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// ���� ��ȭ ������ �޽��� ó�����Դϴ�.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}



//-- Fmod ����� ���� �߰� �ڵ�

// ���� üũ
void ERRCHECK(FMOD_RESULT result)
{
	if (result != FMOD_OK)
	{
		char str[256] = {0,};
		sprintf_s(str, "FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
		MessageBoxA(NULL, str, "TEST", MB_OK  );
	}
}

// ���丮 ����
void InitSound()
{
	FMOD_RESULT result;

	result = FMOD::System_Create(&systemS);  // Create the main system object.
	ERRCHECK(result);
	
	result = systemS->init(2, FMOD_INIT_NORMAL, 0); // Initialize FMOD.
	ERRCHECK(result);
}

// ���ҽ� ���� - ����ϰ��� �ϴ� ���� �ε�
void LoadSound()
{
	FMOD_RESULT result;

	// ����ε�
	result = systemS->createSound("BGM.mp3", FMOD_LOOP_NORMAL, 0, &sound);  // FMOD_DEFAULT uses the defaults.  These are the same as FMOD_LOOP_OFF | FMOD_2D | FMOD_HARDWARE.
	ERRCHECK(result);
}

// ���
void PLAYsound()
{
	FMOD_RESULT result;
	result = systemS->playSound(FMOD_CHANNEL_FREE, sound, false, &channel);
	channel->setVolume(0.5);
	ERRCHECK(result);
}

// ���� ó��
void DeleteSound()
{
	if(sound)
	{
		sound->release();
		sound = NULL;
	}
	if(systemS)
	{
		systemS->release();
		systemS->close();
		systemS = NULL;
	}
}

// â �̵� ����
void SetMoveWindow( HWND hWnd, WPARAM wParam )
{
	// �������� ��ġ�� ũ��(RECT)�� �����´�.
	RECT rt;
	GetWindowRect(hWnd, &rt);

	int moveOffset = 10;

	switch (wParam)
	{
	case 'W':
		rt.top -= moveOffset;
		rt.bottom -= moveOffset;
		break;
	case 'A':
		rt.left -= moveOffset;
		rt.right -= moveOffset;
		break;
	case 'S':
		rt.top += moveOffset;
		rt.bottom += moveOffset;
		break;
	case 'D':
		rt.left += moveOffset;
		rt.right += moveOffset;
		break;
	default:
		break;
	}

	MoveWindow(hWnd, rt.left, rt.top, rt.right - rt.left, rt.bottom - rt.top, TRUE);
}
