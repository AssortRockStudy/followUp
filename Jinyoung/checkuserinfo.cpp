#include <stdio.h>
#include <stdlib.h>

#include <string>
#include "struct.h"


// Ư�� �ε����� �ش��ϴ� �������� ���
void OutputUserInfo(int _Idx);

void CheckUserInfo()
{
	system("cls");
	printf("1. ��ü ���� ���� Ȯ��\n");
	printf("2. ���� �̸� �˻�\n");

	/*int input = 0;
	scanf_s("%d", &input);

	if (1 == input)
	{*/
		// �Էµ� ���� �� ��ŭ �ݺ��Ѵ�.
	for (int i = 0; i < g_user.iCurCount; ++i)
	{
		OutputUserInfo(i);
	}

	//	int input = 0;
	//	scanf_s("%d", &input);
	//}
	//else if (2 == input)
	//{
	//	// �˻��� �̸��� �Է¹޴´�.
	//	printf("ã�� �̸��� �Է��ϼ���\n");
	//	char inputname[10] = {};
	//	scanf_s("%s", inputname, 10);

	//	// ��ü �����߿� �˻� �Է¹��� �̸��� �ش��ϴ� ������ �ε����� ã�´�.	
	//	int i = 0;
	//	for (; i < g_user.iCurCount; ++i)
	//	{
	//		// ��ü ������ �̸��� Ȯ���Ѵ�.
	//		// �Էµ� �̸��� ������ �̸��� ������ �̶� i �� ã�� �ε����̴�.
	//		if (!strcmp(inputname, g_user.pData[i].name))
	//		{
	//			break;
	//		}
	//	}

	//	// �Էµ� �̸��� ���� ������ �ε�����, ������ ����Ѵ�.
	//	OutputUserInfo(i);

	//	// ���
		int input = 0;
		scanf_s("%d", &input);
	//}
}

void OutputUserInfo(int _Idx)
{
	User user = g_user.pData[_Idx];

	printf("�̸� : %s\n", user.name);
	printf("���� : %d\n", user.Age);

	if (1 == user.Sex)
	{
		printf("���� : ����\n");
	}
	else
	{
		printf("���� : ����\n");
	}

	printf("\n");
}