#include <stdio.h>
#include <stdlib.h>

#include "tarray.h"
#include "struct.h"

void additionalInfo();

void InputUserInfo()
{
	system("cls");

	User user = {};

	printf("���� ���� �Է�\n");
	printf("�̸��� �Է��ϼ���\n");
	scanf_s("%s", user.name, 10);

	printf("������ �Է��ϼ���( ���� : 1, ���� 2)\n");
	scanf_s("%d", &user.Sex);

	printf("���̸� �Է��ϼ���\n");
	scanf_s("%d", &user.Age);

	pushData<User>(&g_user, user);
	additionalInfo();
}

void additionalInfo()
{

	int Input = 0;

	system("cls");

	printf("�߰��� ������ �Է� �Ͻðڽ��ϱ�?  \n");
	printf("1.�߰��Է�\n");
	printf("2.����ȭ��\n");
	scanf_s("%d", &Input);
	if (1 == Input) { InputUserInfo(); }
	else { return; }

}

