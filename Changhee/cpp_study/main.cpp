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
	test.insert(make_Pair(70, 2));
	test.insert(make_Pair(150, 3));
	test.insert(make_Pair(50, 4));
	test.insert(make_Pair(80, 5));
	test.insert(make_Pair(25, 6));
	test.insert(make_Pair(60, 7));
	test.insert(make_Pair(75, 8));
	test.insert(make_Pair(90, 9));
	test.insert(make_Pair(125, 10));
	test.insert(make_Pair(175, 11));
	test.insert(make_Pair(110, 12));
	test.insert(make_Pair(140, 13));
	test.insert(make_Pair(160, 14));
	test.insert(make_Pair(200, 15));


	BST<int, int>::iterator iter = test.end();
	--iter;


	for (; iter != test.begin(); --iter)
	{
		cout << *iter << endl;
	}


	//test.preOrder(test.m_pRoot);

	//test.inOrder(test.m_pRoot);

	//test.postOrder(test.m_pRoot);
	//test.DFS(test.m_pRoot);
	//test.BFS(test.m_pRoot);

	//int depth = test.get_depth();

	//BSTNode<int,int>* retVal1 = test.find(100);
	//BSTNode<int,int>* retVal2 = test.find(25);
	//BSTNode<int,int>* retVal3 = test.find(175);
	//BSTNode<int,int>* retVal4 = test.find(200);

	return 0;

}