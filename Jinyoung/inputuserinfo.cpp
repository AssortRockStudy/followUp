#include <stdio.h>
#include <stdlib.h>

#include "tarray.h"
#include "struct.h"

void additionalInfo();

void InputUserInfo()
{
	system("cls");

	User user = {};

	printf("유저 정보 입력\n");
	printf("이름을 입력하세요\n");
	scanf_s("%s", user.name, 10);

	printf("성별을 입력하세요( 남자 : 1, 여자 2)\n");
	scanf_s("%d", &user.Sex);

	printf("나이를 입력하세요\n");
	scanf_s("%d", &user.Age);

	pushData<User>(&g_user, user);
	additionalInfo();
}

void additionalInfo()
{

	int Input = 0;

	system("cls");

	printf("추가로 정보를 입력 하시겠습니까?  \n");
	printf("1.추가입력\n");
	printf("2.메인화면\n");
	scanf_s("%d", &Input);
	if (1 == Input) { InputUserInfo(); }
	else { return; }

}

