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

// 노드 구조체 0

// 링크드 리스트 클래스 
// ㄴ생성자, 소멸자 0
// ㄴpushback, pushfront 0
// ㄴiterator inner 클래스 0
// ㄴㄴ 생성자, 소멸자 0
// ㄴㄴ  begin, end 0
// ㄴㄴ연산자 == != ++ -- * 0
// ㄴㄴ erase 0
// ㄴㄴ 복사생성자, 이동생성자 0
// ㄴㄴ 대입 복사 연산자 0
// ㄴㄴ 이동 복사 연산자 0

// 곧 다 템플릿으로..
