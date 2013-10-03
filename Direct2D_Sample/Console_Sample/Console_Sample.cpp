// Console_Sample.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{
	// 1. 프로그램 초기화
	char szInput;

	// 2. 게임 시작(초기화)
	printf("게임을 시작하지.. 크크크.. \n");

	// 3. 게임 진행
	printf("빨간색과 파란색 하나를 골라라. (R/B) \n");

	// 4. 유저 입력 대기
	scanf_s("%c", &szInput, 1);
	getchar();

	// 5. 유저 입력 처리
	if(szInput == 'R')
	{
		printf("넌 파란색을 소중히 하지 않았지..\n");
	}
	else if(szInput == 'B')
	{
		printf("넌 빨간색을 소중하 하지 않았지.. \n");
	}

	// 6. 게임 진행
	printf("너의 성별을 입력하라.. (M/F) \n");

	// 7. 유저 입력 대기
	scanf_s("%c", &szInput, 1);
	getchar();

	// 8. 유저 입력 처리
	if(szInput == 'M')
	{
		printf("남자 따위... \n");
	}
	else if(szInput == 'F')
	{
		printf("여자.....일리가 없잖아! 거짓말을 하다니.. \n");
	}

	// 9. 게임 종료 처리
	printf("== 당신은 사망하였습니다... == \n");
	printf("== GAME OVER == \n");
	getchar();
	


	return 0;
}

