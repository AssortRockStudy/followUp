#include <stdio.h>
#include <iostream>
#include "linkedListT.h"

int main()
{
	List<int> l1;
	for(int i = 0; i< 10; ++i)
		l1.pushBack(i);
	List<int> l2 = l1;
	l2 = l1;
	List<int> l3 = std::move(l1);
	l3 = l1;
	return 0;
}

// ��� ����ü 0

// ��ũ�� ����Ʈ Ŭ���� 
// ��������, �Ҹ��� 0
// ��pushback, pushfront 0
// ��iterator inner Ŭ���� 0
// ���� ������, �Ҹ��� 0
// ����  begin, end 0
// ���������� == != ++ -- * 0
// ���� erase 0
// ���� ���������, �̵������� 0
// ���� ���� ���� ������ 0
// ���� �̵� ���� ������ 0

// �� �� ���ø�����..
