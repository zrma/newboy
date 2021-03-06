#include "RMConfig.h"
#include "RMRender.h"
#include "RMMainLoop.h"


CRMRender::CRMRender(void) :
	m_TempPositionX(0),
	m_TempPositionY(0),
	m_NowTime(0),
	m_PrevTime(0)
{
}


CRMRender::~CRMRender(void)
{
	SafeRelease(&m_pDirect2dFactory);
	SafeRelease(&m_pRenderTarget);
	SafeRelease(&m_pLightSlateGrayBrush);
	SafeRelease(&m_pCornflowerBlueBrush);
}

HRESULT CRMRender::CreateFactory()
{
 	HRESULT hr = S_OK;
 
	// Create a Direct2D factory.
	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pDirect2dFactory);

	return hr;
}

HRESULT CRMRender::CreateResource()
{
	HRESULT hr = S_OK;

	if (!m_pRenderTarget)
	{
		RECT rc;
		GetClientRect(CRMMainLoop::GetInstance()->GetHWND(), &rc);

		D2D1_SIZE_U size = D2D1::SizeU(
			rc.right - rc.left,
			rc.bottom - rc.top
			);

		// Create a Direct2D render target.
		hr = m_pDirect2dFactory->CreateHwndRenderTarget(
			D2D1::RenderTargetProperties(),
			D2D1::HwndRenderTargetProperties(CRMMainLoop::GetInstance()->GetHWND(), size),
			&m_pRenderTarget
			);


		if (SUCCEEDED(hr))
		{
			// Create a gray brush.
			hr = m_pRenderTarget->CreateSolidColorBrush(
				D2D1::ColorF(D2D1::ColorF::LightSlateGray),
				&m_pLightSlateGrayBrush
				);
		}
		if (SUCCEEDED(hr))
		{
			// Create a blue brush.
			hr = m_pRenderTarget->CreateSolidColorBrush(
				D2D1::ColorF(D2D1::ColorF::CornflowerBlue),
				&m_pCornflowerBlueBrush
				);
		}


		// Create gradient Guide line
		m_gradientStops[0].color = D2D1::ColorF(D2D1::ColorF::ForestGreen,1);
		m_gradientStops[0].position = 0.0f;
		m_gradientStops[1].color = D2D1::ColorF(D2D1::ColorF::DeepPink,1);
		m_gradientStops[1].position = 1.0f;

		if (SUCCEEDED(hr))
		{
			
			hr = m_pRenderTarget->CreateGradientStopCollection(m_gradientStops,2,D2D1_GAMMA_2_2, D2D1_EXTEND_MODE_CLAMP, &m_pGradientStops);
		}

		if (SUCCEEDED(hr))
		{
			//Create radial gradient brush
			hr = m_pRenderTarget->CreateRadialGradientBrush(
				D2D1::RadialGradientBrushProperties(D2D1::Point2F(400,400),D2D1::Point2F(0,0),150,150),
				m_pGradientStops, 
				&m_pRadialGradientBrush
				);
		}


	}

	return hr;
}

void CRMRender::Release()
{
	SafeRelease(&m_pRenderTarget);
	SafeRelease(&m_pLightSlateGrayBrush);
	SafeRelease(&m_pCornflowerBlueBrush);
}

HRESULT CRMRender::Render()
{
	HRESULT hr = S_OK;

	hr = CreateResource();

	if (SUCCEEDED(hr))
	{
		m_pRenderTarget->BeginDraw();

		m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

		//fill the whole background
		m_pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::Yellow));

		D2D1_SIZE_F rtSize = m_pRenderTarget->GetSize();

		// temp Position Setting
		m_TempPositionX = (m_TempPositionX) % (int)(rtSize.width);
		m_TempPositionY = (m_TempPositionY) % (int)(rtSize.height);

		m_pRenderTarget->DrawLine(
				D2D1::Point2F(static_cast<FLOAT>(m_TempPositionX), 0.0f),
				D2D1::Point2F(static_cast<FLOAT>(m_TempPositionX), rtSize.height),
				m_pCornflowerBlueBrush,
				0.5f
				);

		m_pRenderTarget->DrawLine(
				D2D1::Point2F(0.0f, static_cast<FLOAT>(m_TempPositionY)),
				D2D1::Point2F(rtSize.width, static_cast<FLOAT>(m_TempPositionY)),
				m_pLightSlateGrayBrush,
				0.5f
				);

		//radial Gradient brush test
		m_pRenderTarget->DrawLine(
			D2D1::Point2F(0, 0),
			D2D1::Point2F(500.0f, 500.0f),
			m_pRadialGradientBrush,
			10.f
			);

		//radial ellipse
		m_ellipse.point = D2D1::Point2F(400,400);
		m_ellipse.radiusX = 75;
		m_ellipse.radiusY = 75;

		m_pRenderTarget->FillEllipse(m_ellipse,m_pRadialGradientBrush);


		hr = m_pRenderTarget->EndDraw();
	}

	if (hr == D2DERR_RECREATE_TARGET)
	{
		hr = S_OK;
		Release();
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

	if(m_NowTime - m_PrevTime > 50)
	{
		++m_TempPositionX;
		++m_TempPositionY;

		m_PrevTime = m_NowTime;
	}
}
