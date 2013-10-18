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

public:
	void	MovePosition();

private:
	int		m_TempPositionX;
	int		m_TempPositionY;
	int		m_NowTime;
	int		m_PrevTime;
};

