#include <iostream>

#include "CList.h"

#include <list>

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


	int a = test.front();
	int b = test.back();

	test.pop_front();

	test.pop_back();




	return 0;

}