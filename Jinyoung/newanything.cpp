#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string>

#include "tarray.h"
#include "struct.h"

// User 동적 배열
tArray<User> g_user = {};


// 동적 할당
// 런타임 중에 메모리 할당
// 힙 영역
// 사용자(프로그래머) 가 직접 메모리를 관리해야함

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

		// 콘솔창 클리어
		system("cls");

		// 기능 설명
		printf("1. 회원 등록\n");
		printf("2. 회원 전부 출력\n");
		//printf("3. 저장\n");
		//printf("4. 불러오기\n");
		printf("3. 프로그램 종료\n");

		scanf_s("%d", &Input);

		// 3번 입력 시 프로그램 종료
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

