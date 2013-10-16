#pragma once
#include "RMRender.h"

class CRMMainLoop
{
public:
	CRMMainLoop(void);
	~CRMMainLoop(void);

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
	CRMRender* m_Render;

public:
	inline HWND GetHWND() const { return m_HWnd; }
};