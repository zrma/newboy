
#include "NNApplication.h"
#include "NNInputSystem.h"
#include "NNAudioSystem.h"
#include "NNResourceManager.h"

NNApplication* NNApplication::m_pInstance = nullptr;

NNApplication::NNApplication()
	: m_Hwnd(nullptr), m_hInstance(nullptr),
	  m_ScreenHeight(0), m_ScreenWidth(0),
	  m_Fps(0.f), m_ElapsedTime(0.f), m_DeltaTime(0.f),
	  m_PrevTime(0), m_NowTime(0),
	  m_Renderer(nullptr), m_pSceneDirector(nullptr),
	  m_RendererStatus(UNKNOWN)
	  // 초기화 리스트
{

}
NNApplication::~NNApplication()
{

}

NNApplication* NNApplication::GetInstance()
{
	if ( m_pInstance == nullptr )
	{
		m_pInstance = new NNApplication();
	}

	return m_pInstance;
}
void NNApplication::ReleaseInstance()
{
	if ( m_pInstance != nullptr )
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}
}

bool NNApplication::Init( wchar_t* const title, int width, int height, RendererStatus renderStatus )
{
	m_hInstance = GetModuleHandle(0);

	m_Title = title;
	m_ScreenWidth = width;
	m_ScreenHeight = height;
	m_RendererStatus = renderStatus;

	_CreateWindow( m_Title, m_ScreenWidth, m_ScreenHeight );
	_CreateRenderer( renderStatus );
	
	m_pSceneDirector = NNSceneDirector::GetInstance();

	m_Renderer->Init();
	m_pSceneDirector->Init();

	return true;
}
// 어플리케이션 초기화 => 렌더러 초기화, 씬디렉터(싱글톤 패턴으로 생성) 초기화

bool NNApplication::Release()
{
	SafeDelete( m_Renderer );
	m_pSceneDirector->Release();
	// 싱글톤 삭제

	NNSceneDirector::ReleaseInstance();
	NNResourceManager::ReleaseInstance();
	NNInputSystem::ReleaseInstance();
	NNAudioSystem::ReleaseInstance();

	ReleaseInstance();

	return true;
}

bool NNApplication::Run()
{
	MSG msg;
	ZeroMemory( &msg, sizeof(msg) );

	while (true)
	{
		if ( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )
		{
			if ( msg.message == WM_QUIT )
			{
				return true;
			}
			TranslateMessage( &msg );
			DispatchMessage( &msg );
		}
		else
		{
			m_NowTime = timeGetTime();
			if ( m_PrevTime == 0.f )
			{
				m_PrevTime = m_NowTime;
			}
			m_DeltaTime = static_cast<float>(m_NowTime - m_PrevTime) / 1.f;
			m_PrevTime = m_NowTime;
			m_Fps = 1.f / m_DeltaTime;

			m_ElapsedTime += m_DeltaTime;

			NNInputSystem::GetInstance()->UpdateKeyState();

			m_pSceneDirector->UpdateScene( m_DeltaTime );

			m_Renderer->Begin();
			m_Renderer->Clear();
			m_pSceneDirector->RenderScene();
			m_Renderer->End();

			if ( NNInputSystem::GetInstance()->GetKeyState( VK_ESCAPE ) == KEY_DOWN )
			{
				PostQuitMessage(0);
			}
			// ESC 키가 눌렸을 경우 프로그램 종료를 처리한다.
			// 여기서는 생성 된 윈도우에 필요한 자원 반환을 순차적으로 하는 것으로 추측 됨 - 1
		}
	}

	return true;
}

bool NNApplication::_CreateWindow( wchar_t* title, int width, int height )
{
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = NULL;
	wcex.cbWndExtra = NULL;
	wcex.hInstance = m_hInstance;
	wcex.hIcon = NULL;
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = L"NNApplication";
	wcex.hIconSm = NULL;
	wcex.hIcon = NULL;

	RegisterClassEx( &wcex );

	DWORD style = WS_OVERLAPPEDWINDOW;

	m_Hwnd = CreateWindow( L"NNApplication", title, style, CW_USEDEFAULT, CW_USEDEFAULT,
		width, height, NULL, NULL, m_hInstance, NULL);

	ShowWindow( m_Hwnd, SW_SHOWNORMAL );

	return true;
}
bool NNApplication::_CreateRenderer( RendererStatus renderStatus )
{
	switch( renderStatus )
	{
	case D2D:
		m_Renderer = new NND2DRenderer();
		break;
	default:
		return false;
	}

	return true;
}

LRESULT CALLBACK WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	switch( message )
	{
	case WM_DESTROY:

		// 추가 한 부분
		DestroyWindow(hWnd);
		// 여기서는 윈도우가 그냥 파괴 되었을 경우 하단의 종료를 처리하는데
		// 윈도우에 묶여 있는 여러 자원들이 순차적으로 반환 또는 해제 되지 않는 상태에서
		// 순서에 맞지 않게 반환 되면서 권한이 없는 메모리 공간을 억세스 하려고 해서
		// 충돌이 난 것으로 생각 됨.
		//
		// 그래서 DestroyWindow() 함수를 호출하여 윈도우에 연관 된 리소스들을 먼저 제거 함
		//
		// 결과! 종료 후 에러가 사라짐.

		PostQuitMessage(0);
		return 0;
	case WM_PAINT:
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint( hWnd, &ps );
		EndPaint( hWnd, &ps );
	}

	return(DefWindowProc(hWnd,message,wParam,lParam));
}

