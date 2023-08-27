#include <stdio.h>
#include <stdlib.h>

#include <string>
#include "struct.h"


// 특정 인덱스에 해당하는 유저정보 출력
void OutputUserInfo(int _Idx);

void CheckUserInfo()
{
	system("cls");
	printf("1. 전체 유저 정보 확인\n");
	printf("2. 유저 이름 검색\n");

	/*int input = 0;
	scanf_s("%d", &input);

	if (1 == input)
	{*/
		// 입력된 유저 수 만큼 반복한다.
	for (int i = 0; i < g_user.iCurCount; ++i)
	{
		OutputUserInfo(i);
	}

	//	int input = 0;
	//	scanf_s("%d", &input);
	//}
	//else if (2 == input)
	//{
	//	// 검색할 이름을 입력받는다.
	//	printf("찾을 이름을 입력하세요\n");
	//	char inputname[10] = {};
	//	scanf_s("%s", inputname, 10);

	//	// 전체 유저중에 검색 입력받은 이름에 해당하는 유저의 인덱스를 찾는다.	
	//	int i = 0;
	//	for (; i < g_user.iCurCount; ++i)
	//	{
	//		// 전체 유저의 이름을 확인한다.
	//		// 입력된 이름과 유저의 이름이 같으면 이때 i 가 찾은 인덱스이다.
	//		if (!strcmp(inputname, g_user.pData[i].name))
	//		{
	//			break;
	//		}
	//	}

	//	// 입력된 이름과 같은 유저의 인덱스로, 정보를 출력한다.
	//	OutputUserInfo(i);

	//	// 대기
		int input = 0;
		scanf_s("%d", &input);
	//}
}

void OutputUserInfo(int _Idx)
{
	User user = g_user.pData[_Idx];

	printf("이름 : %s\n", user.name);
	printf("나이 : %d\n", user.Age);

	if (1 == user.Sex)
	{
		printf("성별 : 남자\n");
	}
	else
	{
		printf("성별 : 여자\n");
	}

	printf("\n");
}