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

private:
	ID2D1Factory*			m_pDirect2dFactory;
	ID2D1HwndRenderTarget*	m_pRenderTarget;
	ID2D1SolidColorBrush*	m_pLightSlateGrayBrush;
	ID2D1SolidColorBrush*	m_pCornflowerBlueBrush;
};

