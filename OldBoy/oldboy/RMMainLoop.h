#pragma once
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
	// 여기부터
// 	HRESULT		CreateDeviceIndependentResources();
// 	HRESULT		CreateDeviceResources();
// 	void		DiscardDeviceResources();
// 	HRESULT		OnRender();
	// 여기까지는 랜더링 클래스로 새로 뽑아내야 됨

private:
	HWND m_hWnd;
// 	ID2D1Factory* m_pDirect2dFactory;
// 	ID2D1HwndRenderTarget* m_pRenderTarget;
// 	ID2D1SolidColorBrush* m_pLightSlateGrayBrush;
// 	ID2D1SolidColorBrush* m_pCornflowerBlueBrush;
	// 여기도 랜더링 클래스로 새로 뽑을 곳
};