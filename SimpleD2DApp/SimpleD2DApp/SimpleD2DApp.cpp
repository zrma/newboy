// SimpleD2DApp.cpp : ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include "SimpleD2DApp.h"
#include "DemoApp.h"

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	HeapSetInformation(NULL, HeapEnableTerminationOnCorruption, NULL, 0);

	if (SUCCEEDED(CoInitialize(NULL)))
	{
		if(SUCCEEDED(CDemoApp::GetInstance()->Initialize()))
		{
			CDemoApp::GetInstance()->RunMessageLoop();
			CDemoApp::ReleaseInstance();
		}
		CoUninitialize();
	}

	return 0;
}
