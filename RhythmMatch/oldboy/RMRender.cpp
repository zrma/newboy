#include "RMConfig.h"
#include "RMRender.h"
#include "RMMainLoop.h"

CRMRender* CRMRender::m_pInstance = nullptr;

CRMRender::CRMRender(void):
	m_pDirect2dFactory(nullptr), m_pRenderTarget(nullptr)
{

}


CRMRender::~CRMRender(void)
{
	SafeRelease(m_pDirect2dFactory);
	SafeRelease(m_pRenderTarget);

	// Test
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
		
		float dpiX = 0, dpiY = 0;
		GetDesktopDpi(&dpiX, &dpiY);

// 		D2D1_RECT_F dxArea = D2D1::RectF( 0.f, 0.f, ceil(1152.f * dpiX / 94.f), ceil(648.f * dpiY / 94.f) );
// 		D2D1_RECT_F dxSrc = D2D1::RectF( 0.f, 0.f, ceil(1152.f * dpiX / 94.f), ceil(648.f * dpiY / 94.f) );

// 		for(UINT i = 0; i < CRMTextureManager::GetInstance()->GetTextureVector().size(); ++i)
// 		{
// 			CRMTexture* thisTexture = CRMTextureManager::GetInstance()->GetTextureVector().at(i);
// 
// 			D2D1_RECT_F dxSrc = D2D1::RectF( 0.f, 0.f, 
// 				ceil(thisTexture->m_Width * dpiX / 94.f), 
// 				ceil(thisTexture->m_Height * dpiY / 94.f) );
// 
// 			D2D1_RECT_F dxArea = D2D1::RectF( thisTexture->m_PositionX, thisTexture->m_PositionY, 
// 				ceil((thisTexture->m_PositionX + thisTexture->m_Width) * dpiX / 94.f),
// 				ceil((thisTexture->m_PositionY + thisTexture->m_Height) * dpiY / 94.f) );
// 
// 			m_pRenderTarget->DrawBitmap(
// 				CRMTextureManager::GetInstance()->GetTextureVector().at(i)->GetD2D1Bitmap(), dxArea, 1.f, 
// 				D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, &dxSrc);
// 		}

	}
	// SafeDelete(m_TestTexture);

	hr = m_pRenderTarget->EndDraw();

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
