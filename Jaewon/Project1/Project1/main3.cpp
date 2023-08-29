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
		printf("1. ȸ�����\n");
		printf("2. ȸ�� ��� ���\n");
		printf("3. ȸ�����\n");
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
		printf("���� ���� �ʰ�\n");
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
		printf("�̸� �Է�\n");
		scanf_s("%s", &a.name, 20);
		printf("���� �Է�(���ڴ� 1, ���ڴ� 2)\n");
		scanf_s("%c", &a.sex, 1);
		save(a);
		char con;
		printf("�߰��� �����Ͻðڽ��ϱ�?(y/n)\n");
		scanf_s("%c", &con, 1);
		if (con == 'n') {
			flag = false;
		}
	}
}

void printData(){
	system("cls");
	for (int i = 0; i < s.cnt; ++i) {
		printf("ȸ�� %d\n", i + 1);
		printf("�̸� : %s\n", s.u[i].name);
		if (s.u[i].sex == 1)
			printf("���� : ����");
		else
			printf("���� : ����");
	}
	char con;
	printf("���� ȭ������ �̵��Ϸ��� �ƹ� Ű�� �Է��ϼ���\n");
	scanf_s("%c", &con, 1);
}

