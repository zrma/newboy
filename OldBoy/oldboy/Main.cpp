
// oldboy.cpp : �����Լ��� ���� �Ǿ� �ִ� ����.


#include "RMConfig.h"
#include "RMSingletonLoop.h"

//define for memroy leak check
#ifdef _DEBUG
#define	new new(_CLIENT_BLOCK, __FILE__, __LINE__)
#endif

// �� �ڵ� ��⿡ ��� �ִ� �Լ��� ������ �����Դϴ�.

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	CRMSingletonLoop loop;

	loop.Run(hInstance, hPrevInstance, lpCmdLine, nCmdShow);

	return 0;
}
