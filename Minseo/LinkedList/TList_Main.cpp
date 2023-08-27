#include <iostream>
#include <crtdbg.h> // 메모리 누수를 체크하는 헤더 파일

#include "TList.h"
#include "list"

using namespace std;

int main() 
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetBreakAlloc(18); // 18번 째 메모리 할당이 발생할 때, 바로 중단

	TList<int> tlist;
	TList<int> tlist2;

	tlist.push_back(10);
	tlist.push_back(20);
	tlist.push_back(30);
	tlist.push_front(10);
	tlist.push_front(20);
	tlist.push_front(30);

	//new int;

	TList<int>::iterator iter = tlist.begin();
	TList<int>::iterator iter2 = tlist.begin();
	bool isSame = iter == iter2;
	bool isnotSame = iter != iter2;
	++iter2;
	isSame = iter == iter2;
	isnotSame = iter != iter2;
	iter = tlist.erase(iter);
	iter = tlist.erase(iter);

	++iter;
	cout << *iter << endl;
	*iter = 123;
	cout << *iter << endl;
	cout << tlist.front() << "   " << tlist.back() << endl;

	tlist2.swap(tlist);
	tlist2.pop_back();
	tlist2.pop_front();

  	return 0;
}