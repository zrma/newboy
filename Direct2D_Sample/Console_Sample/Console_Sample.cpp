// Console_Sample.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{
	// 1. ���α׷� �ʱ�ȭ
	char szInput;

	// 2. ���� ����(�ʱ�ȭ)
	printf("������ ��������.. ũũũ.. \n");

	// 3. ���� ����
	printf("�������� �Ķ��� �ϳ��� ����. (R/B) \n");

	// 4. ���� �Է� ���
	scanf_s("%c", &szInput, 1);
	getchar();

	// 5. ���� �Է� ó��
	if(szInput == 'R')
	{
		printf("�� �Ķ����� ������ ���� �ʾ���..\n");
	}
	else if(szInput == 'B')
	{
		printf("�� �������� ������ ���� �ʾ���.. \n");
	}

	// 6. ���� ����
	printf("���� ������ �Է��϶�.. (M/F) \n");

	// 7. ���� �Է� ���
	scanf_s("%c", &szInput, 1);
	getchar();

	// 8. ���� �Է� ó��
	if(szInput == 'M')
	{
		printf("���� ����... \n");
	}
	else if(szInput == 'F')
	{
		printf("����.....�ϸ��� ���ݾ�! �������� �ϴٴ�.. \n");
	}

	// 9. ���� ���� ó��
	printf("== ����� ����Ͽ����ϴ�... == \n");
	printf("== GAME OVER == \n");
	getchar();
	


	return 0;
}

