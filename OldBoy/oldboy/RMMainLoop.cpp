#include "RMConfig.h"
#include "RMMainLoop.h"

CRMMainLoop* CRMMainLoop::m_pInstance = nullptr;

CRMMainLoop::CRMMainLoop(void):
	m_HWnd(nullptr),
	m_Render(nullptr)
{
	m_Render = new CRMRender();
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

	// ������ ��ü �߰�
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

		// ������ ��� �ϱ� ���� �κ�
		// m_pDirect2dFactory->GetDesktopDpi(&dpiX, &dpiY);

		// Create the window.
		m_HWnd = CreateWindow(
			L"RhythmMatch",
			L"Rhythm Match v1.0",
			// WS_OVERLAPPEDWINDOW, & WS_THICKFRAME 
			WS_OVERLAPPEDWINDOW & WS_MAXIMIZEBOX & WS_MINIMIZEBOX,
			// WS_THICKFRAME�� ������¡�� �����ϴ� �÷����̴�. ��Ʈ������ &�� WS_OVERLAPPEDWINDOW�� �Բ� ����
			// CW_USEDEFAULT, CW_USEDEFAULT,
			50, 50, 900, 600,
			// static_cast<UINT>(ceil(960.f * dpiX / 96.f)),
			// static_cast<UINT>(ceil(600.f * dpiY / 96.f)), // �� �������� ȭ�� dpi ��� ���� ����� ���� �� ����
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

	// �⺻ �޽��� �����Դϴ�.
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

LRESULT CALLBACK CRMMainLoop::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	LRESULT result = 0;

	if (message == WM_CREATE)
	{
		LPCREATESTRUCT pcs = (LPCREATESTRUCT)lParam;
		CRMMainLoop *pRMMainLoop = (CRMMainLoop *)pcs->lpCreateParams;

		::SetWindowLongPtrW(hWnd, GWLP_USERDATA, PtrToUlong(pRMMainLoop));

		ShowWindow(hWnd, SW_SHOWNOACTIVATE);
		ShowWindow(hWnd, SW_SHOWMINNOACTIVE);
		ShowWindow(hWnd, SHOW_OPENNOACTIVATE);

		result = 1;
	}
	else
	{
		CRMMainLoop *pRMMainLoop = reinterpret_cast<CRMMainLoop *>(static_cast<LONG_PTR>(::GetWindowLongPtrW(hWnd, GWLP_USERDATA)));

		bool wasHandled = false;

		if (pRMMainLoop)
		{
			switch (message)
			{
			case WM_DISPLAYCHANGE:
				{
					InvalidateRect(hWnd, NULL, FALSE);
				}
				result = 0;
				wasHandled = true;
				break;

			case WM_PAINT:
				{
					pRMMainLoop->m_Render->Render();
					ValidateRect(hWnd, NULL);
				}
				result = 0;
				wasHandled = true;
				break;

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
