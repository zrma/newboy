#include "RMConfig.h"
#include "RMMainLoop.h"

CRMMainLoop* CRMMainLoop::m_pInstance = nullptr;

CRMMainLoop::CRMMainLoop(void):
	m_HWnd(nullptr),
	m_Fps(0), m_ElapsedTime(0), m_PrevTime(0), m_NowTime(0)
{
	m_Render	= new CRMRender();
	m_Fps		= 1000/60;
}


CRMMainLoop::~CRMMainLoop(void)
{
	SafeRelease(&m_Render);
}

CRMMainLoop* CRMMainLoop::GetInstance()
{
	if(m_pInstance)
	{
		return m_pInstance;
	}
	else
	{
		m_pInstance = new CRMMainLoop();
		return m_pInstance;
	}
}

void CRMMainLoop::ReleaseInstance()
{
	if(m_pInstance)
	{
		delete m_pInstance;
		m_pInstance = NULL;
	}
}

HRESULT CRMMainLoop::Initialize()
{
	HRESULT hr;

	// 렌더링 객체 추가
	hr = m_Render->CreateFactory();

	if (SUCCEEDED(hr))
	{
		// Register the window class.
		WNDCLASSEX wcex = { sizeof(WNDCLASSEX) };
		wcex.style         = CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc   = CRMMainLoop::WndProc;
		wcex.cbClsExtra    = 0;
		wcex.cbWndExtra    = sizeof(LONG_PTR);
		wcex.hInstance     = HINST_THISCOMPONENT;
		wcex.hbrBackground = NULL;
		wcex.lpszMenuName  = NULL;
		wcex.hCursor       = LoadCursor(NULL, IDI_APPLICATION);
		wcex.lpszClassName = L"RhythmMatch";

		RegisterClassEx(&wcex);

		// 사이즈 계산 하기 위한 부분

		float dpiX = 0, dpiY = 0;
		m_Render->GetDesktopDpi(&dpiX, &dpiY);
		// m_pDirect2dFactory->GetDesktopDpi(&dpiX, &dpiY);

		// Create the window.
		m_HWnd = CreateWindow(
			L"RhythmMatch",
			L"Rhythm Match v1.0",
			// WS_OVERLAPPEDWINDOW, & WS_THICKFRAME 
			WS_OVERLAPPEDWINDOW & WS_MAXIMIZEBOX & WS_MINIMIZEBOX,
			// WS_THICKFRAME은 리사이징을 금지하는 플래그이다. 비트연산자 &로 WS_OVERLAPPEDWINDOW와 함께 적용
			// CW_USEDEFAULT, CW_USEDEFAULT,
			50, 50, 
			static_cast<UINT>(ceil(1152.f * dpiX / 94.f)),
			static_cast<UINT>(ceil(648.f * dpiY / 94.f)), // 이 수식으로 화면 dpi 대비 일정 사이즈를 얻을 수 있음
			NULL,
			NULL,
			HINST_THISCOMPONENT,
			this
			);

		hr = m_HWnd ? S_OK : E_FAIL;
		if (SUCCEEDED(hr))
		{
			ShowWindow(m_HWnd, SW_SHOWNORMAL);
			UpdateWindow(m_HWnd);
		}
	}

	return hr;
}

void CRMMainLoop::RunMessageLoop()
{
	MSG msg;

	while(true)
	{
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			CRMMainLoop::GetInstance()->m_Render->MovePosition();

			m_NowTime = timeGetTime();

			if ( m_PrevTime == 0.f )
			{
				m_PrevTime = m_NowTime;
			}

			m_ElapsedTime = m_NowTime - m_PrevTime;
			
			if(m_ElapsedTime % m_Fps == 0)
			{
				CRMMainLoop::GetInstance()->m_Render->Render();
				ValidateRect(m_HWnd, NULL);

				m_PrevTime = m_NowTime;
			}
			
			if(m_ElapsedTime > m_Fps)
				m_PrevTime = m_NowTime;
		}
	}
}

LRESULT CALLBACK CRMMainLoop::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	LRESULT result = 0;

	if (message == WM_CREATE)
	{
 		ShowWindow(hWnd, SW_SHOWNOACTIVATE);
 		ShowWindow(hWnd, SW_SHOWMINNOACTIVE);
 		ShowWindow(hWnd, SHOW_OPENNOACTIVATE);

		result = 1;
	}
	else
	{
		bool wasHandled = false;

		if (CRMMainLoop::GetInstance()->m_Render)
		{
			switch (message)
			{
			case WM_DESTROY:
				{
					PostQuitMessage(0);
				}
				result = 1;
				wasHandled = true;
				break;
			}
		}

		if (!wasHandled)
		{
			result = DefWindowProc(hWnd, message, wParam, lParam);
		}
	}

	return result;
}
