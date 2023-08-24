#include <iostream>

#include "CList.h"

using std::cout;
using std::endl;

int main()
{

	CList<int> test;

	test.push_back(1);
	test.push_back(2);
	test.push_back(3);
	test.push_front(1);
	test.push_front(2);
	test.push_front(3);

	CList<int>::iterator iter = test.begin();

	CList<int>::iterator iter2 = test.erase(iter);

	return 0;

}