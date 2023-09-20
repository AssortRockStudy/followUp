#include <iostream>
#include <assert.h>

#include "TempleteLinkedList.h"

using std::cout;
using std::endl;

int main()
{
	TList<int> list = {};

	list.push_back(10);
	list.push_back(20);
	list.push_back(30);

	TList<int>::iterator iter = list.begin();
	
	for (; iter != list.end(); ++iter)
	{
		cout << *iter << endl;
	}

	return 0;
}