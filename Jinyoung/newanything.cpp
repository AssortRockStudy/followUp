#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string>

#include "tarray.h"
#include "struct.h"

// User ���� �迭
tArray<User> g_user = {};


// ���� �Ҵ�
// ��Ÿ�� �߿� �޸� �Ҵ�
// �� ����
// �����(���α׷���) �� ���� �޸𸮸� �����ؾ���

void InputUserInfo();
void CheckUserInfo();
void SaveUserInfo();
void LoadUserInfo();

int main()
{
	int i = 0;
	int* pInt = nullptr;
	int** ppInt = nullptr;
	int*** pppInt = nullptr;


	initArray<User>(&g_user);

	while (1)
	{
		int Input = 0;

		// �ܼ�â Ŭ����
		system("cls");

		// ��� ����
		printf("1. ȸ�� ���\n");
		printf("2. ȸ�� ���� ���\n");
		//printf("3. ����\n");
		//printf("4. �ҷ�����\n");
		printf("3. ���α׷� ����\n");

		scanf_s("%d", &Input);

		// 3�� �Է� �� ���α׷� ����
		if (3 == Input)
		{
			break;
		}
		else if (1 == Input)
		{
			InputUserInfo();
		}
		else if (2 == Input)
		{
			CheckUserInfo();
		}
		/*else if (3 == Input)
		{
			SaveUserInfo();
		}
		else if (4 == Input)
		{
			LoadUserInfo();
		}*/
	}



	delArray<User>(&g_user);

	return 0;
}

