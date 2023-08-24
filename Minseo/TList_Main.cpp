#include <iostream>
#include "TList.h"
#include "list"

using namespace std;

int main() 
{
	TList<int> tlist;
	TList<int> tlist2;

	tlist.push_back(10);
	tlist.push_back(20);
	tlist.push_back(30);
	tlist.push_front(10);
	tlist.push_front(20);
	tlist.push_front(30);

	

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

	tlist2.swap(tlist);


  	return 0;
}