#include "BST.h"

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


	return 0;
}