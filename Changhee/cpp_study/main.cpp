#include <iostream>

#include "myList.h"
#include "CList.h"

#include <list>

using std::cout;
using std::endl;

#define TEST 1234567

int main()
{
	int b = 1;

	if ( b == TEST)
	{
		b = 2;
	}

	myList<int> test;
	test.push_back(1);
	test.push_back(2);
	test.push_back(3);


	test.erase(test.begin());


	return 0;

}