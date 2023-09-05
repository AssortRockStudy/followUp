#include "CList.h"



void CList::pushfront(int _data)
{
	tNode* newnode = new tNode(_data);


	if (0 == iCount)
	{
		//데이터가 하나도 없을경우
		pHead = pTail = newnode;
	}
	else
	{
		newnode->pNext = pHead;
		pHead->pPrev = newnode;
		pHead = newnode;
	}
	++iCount;
}



void CList::pushback(int _data)
{
	tNode* newnode =new tNode(_data);

	
	if (0 == iCount)
	{
		//데이터가 하나도 없을경우
		pHead = pTail = newnode;
	}
	else
	{
		pTail->pNext = newnode;
		newnode->pPrev = pTail;
		pTail = newnode;
	}
	
	++iCount;
}





CList::~CList() {
	tNode* curnode = pHead;

	while (curnode) {
		tNode* tmpnode = curnode->pNext;
		delete curnode;
		curnode = tmpnode;
	}

	pHead = nullptr;
	pTail = nullptr;
	iCount = 0;
}