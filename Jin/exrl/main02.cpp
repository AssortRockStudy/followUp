#include <stdio.h>
#include <iostream>
#include "linkedListT.h"
#include <crtdbg.h>
#define CRTDBG_MAP_ALLOC
#define new new(_CLIENT_BLOCK, __FILE__, __LINE__)

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(154);


	List<int> l1;
	for(int i = 0; i< 10; ++i)
		l1.pushBack(i);
	List<int> l2 = l1;
	l2 = l1;
	l1.popBack();
	int a = l1.back();
	List<int> l3 = std::move(l1);
	l3 = std::move(l2);
	a;

	return 0;
}

// 葛球 姥繕端 0

// 元滴球 軒什闘 適掘什 
// い持失切, 社瑚切 0
// いpushback, pushfront 0
// いiterator inner 適掘什 0
// いい 持失切, 社瑚切 0
// いい  begin, end 0
// いい尻至切 == != ++ -- * 0
// いい erase 0
// いい 差紫持失切, 戚疑持失切 0
// いい 企脊 差紫 尻至切 0
// いい 戚疑 差紫 尻至切 0

// 稲 陥 奴巴鹸生稽..
