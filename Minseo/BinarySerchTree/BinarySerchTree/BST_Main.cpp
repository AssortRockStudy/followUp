#include "BST.h"
#include <iostream>

int main()
{

	BST<int, float> bst;
	Pair<int, float> p;
	p.first = 100;
	p.second = 123.456f;
	bst.insert(p);
	p.first = 50;
	bst.insert(p);
	p.first = 70;
	bst.insert(p);
	p.first = 30;
	bst.insert(p);

	bst.clear();

	bst.insert(p.Create_Pair(100, 123.f));
	bst.insert(p.Create_Pair(50, 123.f));
	bst.insert(p.Create_Pair(150, 123.f));
	bst.insert(p.Create_Pair(125, 123.f));
	bst.insert(p.Create_Pair(175, 123.f));
	bst.insert(p.Create_Pair(25, 123.f));
	bst.insert(p.Create_Pair(75, 123.f));

	BST<int, float>::iterator iter = bst.begin();

	for (; iter != bst.end(); ++iter)
	{
		std::cout << iter->second << std::endl;
	}



	return 0;
}