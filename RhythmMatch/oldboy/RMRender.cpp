#include "RMConfig.h"
#include "RMRender.h"
#include "RMMainLoop.h"
#include "RMTextureManager.h"

CRMRender* CRMRender::m_pInstance = nullptr;

CRMRender::CRMRender(void):
	m_pDirect2dFactory(nullptr), m_pRenderTarget(nullptr),
	// Test
	m_NowTime(0), m_PrevTime(0), m_NowScene(0)
{
	ZeroMemory(m_TestTexture,sizeof(m_TestTexture));
}


CRMRender::~CRMRender(void)
{
	SafeRelease(m_pDirect2dFactory);
	SafeRelease(m_pRenderTarget);

	// Test
	// SafeArrayDelete(m_TestTexture);
	SafeDelete(m_TestTexture[0]);
	SafeDelete(m_TestTexture[1]);
	SafeDelete(m_TestTexture[2]);
	SafeDelete(m_TestTexture[3]);
	SafeDelete(m_TestTexture[4]);
	SafeDelete(m_TestTexture[5]);
	SafeDelete(m_TestTexture[6]);
	SafeDelete(m_TestTexture[7]);

	CRMTextureManager::ReleaseInstance();
}

CRMRender* CRMRender::GetInstance()
{
	if(m_pInstance)
	{
		return m_pInstance;
	}
	else
	{
		m_pInstance = new CRMRender();
		return m_pInstance;
	}
}

void CRMRender::ReleaseInstance()
{
	if(m_pInstance)
	{
		delete m_pInstance;
		m_pInstance = NULL;
	}
}

HRESULT CRMRender::CreateFactory()
{
 	HRESULT hr = S_OK;
 
	// Create a Direct2D factory.
	if(m_pDirect2dFactory == nullptr)
		hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pDirect2dFactory);

	if ( hr != S_OK )
	{
		return false;
	}

	return hr;
}

HRESULT CRMRender::CreateRenderTarget()
{
	HRESULT hr = S_FALSE;

	if(m_pRenderTarget == nullptr)
	{
		RECT rc;
		GetClientRect(CRMMainLoop::GetInstance()->GetHWND(), &rc);

		D2D1_SIZE_U size = D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top);

		// Create a Direct2D render target.
		hr = m_pDirect2dFactory->CreateHwndRenderTarget(
			D2D1::RenderTargetProperties(),
			D2D1::HwndRenderTargetProperties(CRMMainLoop::GetInstance()->GetHWND(), size),
			&m_pRenderTarget
			);
	}

	return hr;
}

HRESULT CRMRender::Render()
{
	HRESULT hr = S_OK;

	if (SUCCEEDED(hr))
	{
		m_pRenderTarget->BeginDraw();
		m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
		m_pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));

		// 여기부터 드로잉

		if(m_TestTexture[0] == nullptr)
		{
			m_TestTexture[0] = new CRMTexture();
			m_TestTexture[0]->Create( L"Image/test1.png" );
		}
		if(m_TestTexture[1] == nullptr)
		{
			m_TestTexture[1] = new CRMTexture();
			m_TestTexture[1]->Create( L"Image/test2.png" );
		}
		if(m_TestTexture[2] == nullptr)
		{
			m_TestTexture[2] = new CRMTexture();
			m_TestTexture[2]->Create( L"Image/test3.png" );
		}
		if(m_TestTexture[3] == nullptr)
		{
			m_TestTexture[3] = new CRMTexture();
			m_TestTexture[3]->Create( L"Image/test4.png" );
		}
		if(m_TestTexture[4] == nullptr)
		{
			m_TestTexture[4] = new CRMTexture();
			m_TestTexture[4]->Create( L"Image/test5.png" );
		}
		if(m_TestTexture[5] == nullptr)
		{
			m_TestTexture[5] = new CRMTexture();
			m_TestTexture[5]->Create( L"Image/test6.png" );
		}
		if(m_TestTexture[6] == nullptr)
		{
			m_TestTexture[6] = new CRMTexture();
			m_TestTexture[6]->Create( L"Image/test7.png" );
		}
		if(m_TestTexture[7] == nullptr)
		{
			m_TestTexture[7] = new CRMTexture();
			m_TestTexture[7]->Create( L"Image/test8.png" );
		}
		// 여기까지 하드코딩 한 것 => 리팩토링 해야 됨

		int i = 0;
		
		m_NowScene = m_NowScene % 15;

		if(m_NowScene > 7)
		{
			i = 14 - m_NowScene;
		}
		else
			i = m_NowScene;
		
		float dpiX = 0, dpiY = 0;
		GetDesktopDpi(&dpiX, &dpiY);

// 		D2D1_RECT_F dxArea = D2D1::RectF( 0.f, 0.f, ceil(1152.f * dpiX / 94.f), ceil(648.f * dpiY / 94.f) );
// 		D2D1_RECT_F dxSrc = D2D1::RectF( 0.f, 0.f, ceil(1152.f * dpiX / 94.f), ceil(648.f * dpiY / 94.f) );

		D2D1_RECT_F dxArea = D2D1::RectF( 330.f, 200.f, ceil(550.f * dpiX / 94.f), ceil(450.f * dpiY / 94.f) );
		D2D1_RECT_F dxSrc = D2D1::RectF( 0.f, 0.f, ceil(600.f * dpiX / 94.f), ceil(600.f * dpiY / 94.f) );

		m_pRenderTarget->DrawBitmap(
				m_TestTexture[i]->GetD2D1Bitmap(), dxArea, 1.f, 
				D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, &dxSrc);

		dxArea = D2D1::RectF( 580.f, 200.f, ceil(800.f * dpiX / 94.f), ceil(450.f * dpiY / 94.f) );
		dxSrc = D2D1::RectF( 0.f, 0.f, ceil(600.f * dpiX / 94.f), ceil(600.f * dpiY / 94.f) );

		m_pRenderTarget->DrawBitmap(
			m_TestTexture[(7-i)]->GetD2D1Bitmap(), dxArea, 1.f, 
			D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, &dxSrc);

		// SafeDelete(m_TestTexture);

		hr = m_pRenderTarget->EndDraw();
	}

	if (hr == D2DERR_RECREATE_TARGET)
	{
		hr = S_OK;
		SafeRelease(m_pDirect2dFactory);
		SafeRelease(m_pRenderTarget);
	}

	return hr;
}

void CRMRender::GetDesktopDpi( float* dpiX, float* dpiY )
{
	m_pDirect2dFactory->GetDesktopDpi(dpiX, dpiY);
}

void CRMRender::MovePosition()
{
	m_NowTime = timeGetTime();

	if(m_NowTime - m_PrevTime > 100)
	{
		++m_NowScene;
		m_PrevTime = m_NowTime;
	}
}

