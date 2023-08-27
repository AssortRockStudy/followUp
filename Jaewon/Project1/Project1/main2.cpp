#include "bst.h"

int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	Pair<int, int> insert;
	insert.first = 30;
	insert.second = 30;
	BST<int, int> myTree;
	myTree.push(insert);
	myTree.push(Pair<int, int>(20, 20));
	myTree.push(Pair<int, int>(40, 40));
	myTree.push(Pair<int, int>(10, 10));
	myTree.push(Pair<int, int>(25, 25));
	myTree.push(Pair<int, int>(35, 35));
	myTree.push(Pair<int, int>(45, 45));
	myTree.push(Pair<int, int>(31, 31));
	myTree.push(Pair<int, int>(5, 5));
	myTree.push(Pair<int, int>(15, 15));
	myTree.push(Pair<int, int>(23, 23));
	myTree.push(Pair<int, int>(28, 28));
	myTree.push(Pair<int, int>(32, 32));
	myTree.push(Pair<int, int>(38, 38));
	myTree.push(Pair<int, int>(43, 43));
	myTree.push(Pair<int, int>(50, 50));
	

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

	// Å×½ºÆ®

	BST<int, int>::iterator treeIter = myTree.begin();
	++treeIter;
	--treeIter;
	treeIter++;
	treeIter--;
	for (; treeIter != myTree.end(); ++treeIter) {
		cout << treeIter->first << endl;
	}

	return 0;
}