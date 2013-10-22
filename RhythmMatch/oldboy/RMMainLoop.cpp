#include "RMConfig.h"
#include "RMMainLoop.h"
#include "RMTextureManager.h"

CRMMainLoop* CRMMainLoop::m_pInstance = nullptr;

CRMMainLoop::CRMMainLoop(void):
	m_HWnd(nullptr),
	m_Fps(0), m_ElapsedTime(0), m_PrevTime(0), m_NowTime(0)
{
	m_Fps		= 1000/60;
}


CRMMainLoop::~CRMMainLoop(void)
{
	CRMRender::ReleaseInstance();
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
	HRESULT hr = S_OK;

	// 랜더링 객체 추가
	hr = CRMRender::GetInstance()->CreateFactory();

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
	CRMRender::GetInstance()->GetDesktopDpi(&dpiX, &dpiY);

	// Create the window.
	m_HWnd = CreateWindow(
			L"RhythmMatch",
			L"Rhythm Match v1.0",
			// WS_OVERLAPPEDWINDOW, 
			// WS_OVERLAPPEDWINDOW & WS_THICKFRAME
			WS_OVERLAPPEDWINDOW & WS_MAXIMIZEBOX & WS_MINIMIZEBOX,
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

		// 랜더 타겟 추가
		hr = CRMRender::GetInstance()->CreateRenderTarget();
	}

	if(CRMTextureManager::GetInstance()->GetTextureMap().size() == 0)
	{
		CRMTextureManager::GetInstance()->InitTexture();
	}
	// 이미지 파일들 불러오기
	
	return hr;
}

void CRMMainLoop::RunMessageLoop()
{
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	while(true)
	{
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if ( msg.message == WM_QUIT )
			{
				return;
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			// 처리 해야 할 내부 로직들을 처리함
			// CRMRender::GetInstance()->MovePosition();
			// 임시로 추가함

			m_NowTime = timeGetTime();

			if ( m_PrevTime == 0.f )
			{
				m_PrevTime = m_NowTime;
			}

			m_ElapsedTime = m_NowTime - m_PrevTime;
			
			if(m_ElapsedTime % m_Fps == 0)
			{
				CRMRender::GetInstance()->Render();
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

	if(message == WM_DESTROY)
	{
		// DestroyWindow(hWnd);
		PostQuitMessage(0);				
		result = 1;
	}
	else
		result = DefWindowProc(hWnd, message, wParam, lParam);

	return result;
}
