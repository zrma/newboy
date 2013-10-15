#include "RMConfig.h"
#include "RMMainLoop.h"

CRMMainLoop* CRMMainLoop::m_pInstance = nullptr;

CRMMainLoop::CRMMainLoop(void):
	m_hWnd(nullptr)
{
}


CRMMainLoop::~CRMMainLoop(void)
{
// 	SafeRelease(&m_pDirect2dFactory);
// 	SafeRelease(&m_pRenderTarget);
// 	SafeRelease(&m_pLightSlateGrayBrush);
// 	SafeRelease(&m_pCornflowerBlueBrush);
	
	// ���� ������ ��� ������ �������� ��� �ְ�, ���⼭ �������� ���� �ϵ��� �Ѵ�
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
	// hr = CreateDeviceIndependentResources(); // �� �κ� ����
	hr = S_OK; // ������ ������ �� �Ǿ� �����Ƿ� �ӽ÷� OK ������ ����

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
		m_hWnd = CreateWindow(
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

		hr = m_hWnd ? S_OK : E_FAIL;
		if (SUCCEEDED(hr))
		{
			ShowWindow(m_hWnd, SW_SHOWNORMAL);
			UpdateWindow(m_hWnd);
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

// HRESULT CRMMainLoop::CreateDeviceIndependentResources()
// {
// 	HRESULT hr = S_OK;
// 
// 	// Create a Direct2D factory.
// 	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pDirect2dFactory);
// 
// 	return hr;
// }

// HRESULT CRMMainLoop::CreateDeviceResources()
// {
// 	HRESULT hr = S_OK;
// 
// 	if (!m_pRenderTarget)
// 	{
// 		RECT rc;
// 		GetClientRect(m_hWnd, &rc);
// 
// 		D2D1_SIZE_U size = D2D1::SizeU(
// 			rc.right - rc.left,
// 			rc.bottom - rc.top
// 			);
// 
// 		// Create a Direct2D render target.
// 		hr = m_pDirect2dFactory->CreateHwndRenderTarget(
// 			D2D1::RenderTargetProperties(),
// 			D2D1::HwndRenderTargetProperties(m_hWnd, size),
// 			&m_pRenderTarget
// 			);
// 
// 
// 		if (SUCCEEDED(hr))
// 		{
// 			// Create a gray brush.
// 			hr = m_pRenderTarget->CreateSolidColorBrush(
// 				D2D1::ColorF(D2D1::ColorF::LightSlateGray),
// 				&m_pLightSlateGrayBrush
// 				);
// 		}
// 		if (SUCCEEDED(hr))
// 		{
// 			// Create a blue brush.
// 			hr = m_pRenderTarget->CreateSolidColorBrush(
// 				D2D1::ColorF(D2D1::ColorF::CornflowerBlue),
// 				&m_pCornflowerBlueBrush
// 				);
// 		}
// 	}
// 
// 	return hr;
// }

// void CRMMainLoop::DiscardDeviceResources()
// {
// 	SafeRelease(&m_pRenderTarget);
// 	SafeRelease(&m_pLightSlateGrayBrush);
// 	SafeRelease(&m_pCornflowerBlueBrush);
// }

// ���� �ּ� ó�� �� �� �κ��� ������ Ŭ������ �Űܾ� ��
// ���丮 ���� + ���ҽ� ���� + �ڿ� �ݳ�
// �������� Initialize �޼ҵ�


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
					// pRMMainLoop->OnRender();
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

// HRESULT CRMMainLoop::OnRender()
// {
// 	HRESULT hr = S_OK;
// 
// 	hr = CreateDeviceResources();
// 
// 	if (SUCCEEDED(hr))
// 	{
// 		m_pRenderTarget->BeginDraw();
// 
// 		m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
// 
// 		m_pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));
// 
// 		D2D1_SIZE_F rtSize = m_pRenderTarget->GetSize();
// 
// 		// Draw a grid background.
// 		int width = static_cast<int>(rtSize.width);
// 		int height = static_cast<int>(rtSize.height);
// 
// 		for (int x = 0; x < width; x += 10)
// 		{
// 			m_pRenderTarget->DrawLine(
// 				D2D1::Point2F(static_cast<FLOAT>(x), 0.0f),
// 				D2D1::Point2F(static_cast<FLOAT>(x), rtSize.height),
// 				m_pLightSlateGrayBrush,
// 				0.5f
// 				);
// 		}
// 
// 		for (int y = 0; y < height; y += 10)
// 		{
// 			m_pRenderTarget->DrawLine(
// 				D2D1::Point2F(0.0f, static_cast<FLOAT>(y)),
// 				D2D1::Point2F(rtSize.width, static_cast<FLOAT>(y)),
// 				m_pLightSlateGrayBrush,
// 				0.5f
// 				);
// 		}
// 
// 		// Draw two rectangles.
// 		D2D1_RECT_F rectangle1 = D2D1::RectF(
// 			rtSize.width/2 - 50.0f,
// 			rtSize.height/2 - 50.0f,
// 			rtSize.width/2 + 50.0f,
// 			rtSize.height/2 + 50.0f
// 			);
// 
// 		D2D1_RECT_F rectangle2 = D2D1::RectF(
// 			rtSize.width/2 - 100.0f,
// 			rtSize.height/2 - 100.0f,
// 			rtSize.width/2 + 100.0f,
// 			rtSize.height/2 + 100.0f
// 			);
// 
// 		// Draw a filled rectangle.
// 		m_pRenderTarget->FillRectangle(&rectangle1, m_pLightSlateGrayBrush);
// 
// 		// Draw the outline of a rectangle.
// 		m_pRenderTarget->DrawRectangle(&rectangle2, m_pCornflowerBlueBrush);
// 
// 		hr = m_pRenderTarget->EndDraw();
// 	}
// 
// 	if (hr == D2DERR_RECREATE_TARGET)
// 	{
// 		hr = S_OK;
// 		DiscardDeviceResources();
// 	}
// 
// 	return hr;
// }

// �̰��� ���������� �������� ���� �޼ҵ�