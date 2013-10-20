#pragma once
#include "RMRender.h"

class CRMMainLoop
{
private:
	CRMMainLoop(void);
	~CRMMainLoop(void);
	// �̱����̹Ƿ� �����ڸ� private�� ���Ƶ�

public:
	HRESULT Initialize();		// �ʱ�ȭ
	void	RunMessageLoop();	// �޽��� ó��

public:
	static CRMMainLoop*	GetInstance();
	static void			ReleaseInstance();

private:
	static CRMMainLoop* m_pInstance;
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	
private:
	HWND m_HWnd;

private:
	int		m_Fps;
	int		m_ElapsedTime;
	
	int		m_PrevTime;
	int		m_NowTime;

public:
	inline HWND GetHWND() const { return m_HWnd; }
};