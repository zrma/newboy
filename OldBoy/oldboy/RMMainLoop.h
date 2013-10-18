#pragma once
#include "RMRender.h"

class CRMMainLoop
{
public:
	CRMMainLoop(void);
	~CRMMainLoop(void);

	HRESULT Initialize();		// 초기화
	void	RunMessageLoop();	// 메시지 처리

public:
	static CRMMainLoop*	GetInstance();
	static void			ReleaseInstance();

private:
	static CRMMainLoop* m_pInstance;
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	
private:
	HWND m_HWnd;

private:
	CRMRender*	m_Render;

private:
	int		m_Fps;
	int		m_ElapsedTime;
	
	int		m_PrevTime;
	int		m_NowTime;

public:
	inline HWND GetHWND() const { return m_HWnd; }
};