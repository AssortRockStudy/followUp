#include <iostream>
#include "TList.h"

using namespace std;

int main() 
{
	TList<int> list;
	list.push_back(10);
	list.push_back(20);
	list.push_back(30);
	list.push_front(10);
	list.push_front(20);
	list.push_front(30);

	TList<int>::iterator iter = list.begin();
	TList<int>::iterator iter2 = list.begin();
	bool isSame = iter == iter2;
	bool isnotSame = iter != iter2;
	++iter2;
	isSame = iter == iter2;
	isnotSame = iter != iter2;
	iter = list.erase(iter);
	iter = list.erase(iter);

	++iter;
	cout << *iter << endl;
	*iter = 123;
	cout << *iter << endl;

  	return 0;
}