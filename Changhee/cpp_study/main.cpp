#include <iostream>

#include "BST.h"
#include "CList.h"


using std::cout;
using std::endl;

#define TEST 1234567

int main()
{
	BST<int, int> test;

	test.insert(make_Pair(100, 1));
	test.insert(make_Pair(70, 1));
	test.insert(make_Pair(150, 1));
	test.insert(make_Pair(50, 1));
	test.insert(make_Pair(80, 1));
	test.insert(make_Pair(25, 1));
	test.insert(make_Pair(60, 1));
	test.insert(make_Pair(75, 1));
	test.insert(make_Pair(90, 1));
	test.insert(make_Pair(125, 1));
	test.insert(make_Pair(175, 1));
	test.insert(make_Pair(110, 1));
	test.insert(make_Pair(140, 1));
	test.insert(make_Pair(160, 1));
	test.insert(make_Pair(200, 1));


	CList<int> test2;
	test2.push_back(1);


	return 0;

}