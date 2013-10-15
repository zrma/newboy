
// oldboy.cpp : 메인함수가 포함 되어 있는 파일.


#include "RMConfig.h"
#include "RMMainLoop.h"

//define for memroy leak check
#ifdef _DEBUG
#define	new new(_CLIENT_BLOCK, __FILE__, __LINE__)
#endif

// 이 코드 모듈에 들어 있는 함수의 정방향 선언입니다.

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	HeapSetInformation(NULL, HeapEnableTerminationOnCorruption, NULL, 0);

	if(SUCCEEDED(CoInitialize(NULL)))
	{
		if(SUCCEEDED(CRMMainLoop::GetInstance()->Initialize()))
		{
			CRMMainLoop::GetInstance()->RunMessageLoop();
			CRMMainLoop::ReleaseInstance();
		}
		CoUninitialize();
	}

	return 0;
}
