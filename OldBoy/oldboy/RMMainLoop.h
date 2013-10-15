#pragma once
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
	// �������
// 	HRESULT		CreateDeviceIndependentResources();
// 	HRESULT		CreateDeviceResources();
// 	void		DiscardDeviceResources();
// 	HRESULT		OnRender();
	// ��������� ������ Ŭ������ ���� �̾Ƴ��� ��

private:
	HWND m_hWnd;
// 	ID2D1Factory* m_pDirect2dFactory;
// 	ID2D1HwndRenderTarget* m_pRenderTarget;
// 	ID2D1SolidColorBrush* m_pLightSlateGrayBrush;
// 	ID2D1SolidColorBrush* m_pCornflowerBlueBrush;
	// ���⵵ ������ Ŭ������ ���� ���� ��
};