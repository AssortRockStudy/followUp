#include <iostream>
#include "TList.h"

int main() 
{
	TList<int> list;
	list.push_back(10);
	list.push_back(20);
	list.push_back(30);
	list.push_front(10);
	list.push_front(20);
	list.push_front(30);

	TList<int>::iterator iter = list.begin();

	list.erase(iter);

	return 0;
}