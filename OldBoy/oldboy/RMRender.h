#pragma once
class CRMRender
{
public:
	CRMRender(void);
	~CRMRender(void);

public:
	HRESULT		CreateFactory();
	HRESULT		CreateResource();
	HRESULT		Render();
	void		Release();
	void		GetDesktopDpi(float* dpiX, float* dpiY);

private:
	ID2D1Factory*			m_pDirect2dFactory;
	ID2D1HwndRenderTarget*	m_pRenderTarget;
	ID2D1SolidColorBrush*	m_pLightSlateGrayBrush;
	ID2D1SolidColorBrush*	m_pCornflowerBlueBrush;
	
	ID2D1RadialGradientBrush* m_pRadialGradientBrush;
	ID2D1GradientStopCollection* m_pGradientStops;
	D2D1_GRADIENT_STOP m_gradientStops[2];
	D2D1_ELLIPSE m_ellipse;

public:
	void	MovePosition();

private:
	int		m_TempPositionX;
	int		m_TempPositionY;
	int		m_NowTime;
	int		m_PrevTime;
};

