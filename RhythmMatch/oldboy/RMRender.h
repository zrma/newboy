#pragma once
#include "RMTexture.h"

class CRMRender
{
private:
	CRMRender(void);
	~CRMRender(void);
	// ½Ì±ÛÅæÀÌ¹Ç·Î »ý¼ºÀÚ¸¦ private·Î ¸·¾ÆµÒ

public:
	HRESULT		CreateFactory();
	HRESULT		CreateRenderTarget();

	HRESULT		Render();
	void		GetDesktopDpi(float* dpiX, float* dpiY);

public:
	static CRMRender*	GetInstance();
	static void			ReleaseInstance();

private:
	static CRMRender*	m_pInstance;

private:
	ID2D1Factory*			m_pDirect2dFactory;
	ID2D1HwndRenderTarget*	m_pRenderTarget;

public:
	ID2D1Factory*			GetD2DFactory() const { return m_pDirect2dFactory; }
	ID2D1HwndRenderTarget*	GetRenderTarget() const { return m_pRenderTarget; }
};

