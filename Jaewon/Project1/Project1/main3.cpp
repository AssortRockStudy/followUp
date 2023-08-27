#include <iostream>
#include <Windows.h>

struct User {
	char name[20];
	char sex;
};

struct Storage {
	User u[200];
	int cnt;
	Storage() : cnt(0) {
		for (int i = 0; i < 200; ++i)
			u[i] = User();
	}
};

void save(User);
void saveUser();
void printData();

Storage s = {};

int main() {
	bool flag = true;
	while (flag) {
		int input;
		system("cls");
		printf("1. 회원등록\n");
		printf("2. 회원 모두 출력\n");
		printf("3. 회원등록\n");
		scanf_s("%d", &input);

		switch (input)
		{
		case 1:
			saveUser();
			break;
		case 2:
			printData();
			break;
		case 3:
			flag = false;
			break;
		default:
			break;
		}
	}
	return 0;
}

void save(const User u) {
	if (s.cnt > 200) {
		printf("저장 공간 초과\n");
	}
	else {
		s.u[s.cnt++] = u;
	}
}

void saveUser(){
	bool flag = true;
	while (flag) {
		system("cls");
		User a;
		printf("이름 입력\n");
		scanf_s("%s", &a.name, 20);
		printf("성별 입력(남자는 1, 여자는 2)\n");
		scanf_s("%c", &a.sex, 1);
		save(a);
		char con;
		printf("추가로 저장하시겠습니까?(y/n)\n");
		scanf_s("%c", &con, 1);
		if (con == 'n') {
			flag = false;
		}
	}
}

void printData(){
	system("cls");
	for (int i = 0; i < s.cnt; ++i) {
		printf("회원 %d\n", i + 1);
		printf("이름 : %s\n", s.u[i].name);
		if (s.u[i].sex == 1)
			printf("성별 : 남자");
		else
			printf("성별 : 여자");
	}
	char con;
	printf("메인 화면으로 이돌하려면 아무 키나 입력하세요\n");
	scanf_s("%c", &con, 1);
}

