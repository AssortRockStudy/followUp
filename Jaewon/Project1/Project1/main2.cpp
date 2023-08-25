#include "bst.h"

int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	Pair<int, int> insert;
	insert.first = 30;
	insert.second = 30;
	BST<int, int> myTree;
	myTree.push(insert);

	for (int i = 20; i <= 40; ++i) {
		if (i == 30) 
			continue;
		insert.first = i;
		insert.second = i;
		myTree.push(insert);
	}

	myTree.PrintTree(1);
	cout << endl;
	myTree.PrintTree(2);
	cout << endl;
	myTree.PrintTree(3);
	cout << endl;
	myTree.PrintTree(4);
	insert.first = 20;
	insert.second = 20;
	cout << endl;
	cout << myTree.search(insert) << endl;
	insert.first = 50;
	insert.second = 50;
	cout << myTree.search(insert) << endl;


	return 0;
}