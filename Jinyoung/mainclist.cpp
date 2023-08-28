#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "TCList.h"
#include "bst.h"
#include <crtdbg.h>



using std::cout;
using std::cin;
using std::endl;


/*
�ؾ��Ұ�
1.���ͷ����� �����ϱ�
	begin end erase insert �����ϱ�
2.push front push back �Լ� �����ϱ�
3.�������� ++������ �����ε�
4.!= ������ �����ε�

*/
/*�򰥷����ô���
1. �μ� ���޾��ص� �˾Ƽ� ����Ʈ�� ä���ִ� �������޵Ǵ°� node���ִ����� clist���ִ�����
2. tnode�� clist�� ��� class������. �����ڴ� ��� �����Ǿ��־�����(�Ѵٿ���)
3. ���ͷ����� ���Ȯ��
4. ++������ �����ε� ���ͷ����Ϳ��ϴ��� clist���ϴ���
5. cpp�� �Լ������Ǿ� �ִ� ���� �ľ�
6. clist Ŭ������ ��ȯŸ�� iterator �ַ��� �����ٶ��� ���漱��а�
7. ���������� �������& ��ȯŸ��
8. erase insert ������ġ
*/


/*
�����ǹ��ΰ�
1. ��ȯŸ���� ���۷����� �����ϸ� �ȵǴ°�? (������� erase�Լ��� ��ȯŸ���� ���۷����� �ָ�ȵǴ°�?)
2. ������ �ζ��� �Լ��� �� �� �ִ��� ������ ��ȣ�ϴٰ� ������ (�ϴ� �ζ����� ���ؼ� �ٱ׷��� �ۼ��ϴ���)
2. operator == �����ε��� ���ڸ� const �� �������� ����(���������)
*/


int main() {
	enum MY_TYPE
	{
		TYPE1,
		TYPE2,
		TYPE3,
		NONE,
	};

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(170);
	TCList<int> tcl;

	for (int i = 0; i < 3; ++i)
	{
		tcl.pushback(i+1);
	}

	typename TCList<int>::iterator it;

	

	
	//////////////////////230821 0417����///////////////////////////

	for (it = tcl.begin(); tcl.end() != it;)
	{
		it = tcl.erase(it);
	}

	for (it = tcl.begin(); tcl.end() != it; ++it)
	{
		cout << *it << endl;
	}
	//////////////////////230821 0417����///////////////////////////


	//deepcopy �׽�Ʈ
	TCList<int> c1;
	for (int i = 0; i < 3; ++i)
	{
		c1.pushback(i + 1);
	}

	
	TCList<int> c2;
	c2.CopyDeep(c1);

	//��������� �׽�Ʈ
	TCList<int> c3 = c1;

	//�̵������� �׽�Ʈ
	TCList<int> c4 = std::move(c1);

	//���Կ����� �׽�Ʈ
	TCList<int> c5;
	c5 = c2;

	//�̵� ���� ������ �׽�Ʈ
	TCList<int> c6;
	c6 = std::move(c3);

	TCList<int> c8;
	for (int i = 0; i < 3; ++i)
	{
		c8.pushback(i + 1);
	}

	//swap �׽�Ʈ
	TCList<int> c7;
	for (int i = 0; i < 3; ++i)
	{
		c7.pushfront(i + 1);
	}

	c8.swap(std::move(c7));


	TCList< TCList<int>> tcl1;

	tcl1.pushback(c1);
	tcl1.pushback(c2);
	tcl1.pushback(c4);

	CBST<int, MY_TYPE> cb1;

	cb1.pushdata(Create_Pair(100, MY_TYPE::TYPE1)); //				    100
	cb1.pushdata(Create_Pair(70, MY_TYPE::TYPE1));  //			70				150	
	cb1.pushdata(Create_Pair(150, MY_TYPE::TYPE1)); //	  50		80		125		  175
	cb1.pushdata(Create_Pair(50, MY_TYPE::TYPE1)); //	25  60	  75  90   110 140   160  200
	cb1.pushdata(Create_Pair(80, MY_TYPE::TYPE1));
	cb1.pushdata(Create_Pair(25, MY_TYPE::TYPE1));
	cb1.pushdata(Create_Pair(60, MY_TYPE::TYPE1));
	cb1.pushdata(Create_Pair(75, MY_TYPE::TYPE1));
	cb1.pushdata(Create_Pair(90, MY_TYPE::TYPE1));
	cb1.pushdata(Create_Pair(125, MY_TYPE::TYPE1));
	cb1.pushdata(Create_Pair(175, MY_TYPE::TYPE1));
	cb1.pushdata(Create_Pair(110, MY_TYPE::TYPE1));
	cb1.pushdata(Create_Pair(140, MY_TYPE::TYPE1));
	cb1.pushdata(Create_Pair(160, MY_TYPE::TYPE1));
	cb1.pushdata(Create_Pair(200, MY_TYPE::TYPE1));
	cb1.pushdata(Create_Pair(400, MY_TYPE::TYPE1));
	cb1.pushdata(Create_Pair(500, MY_TYPE::TYPE1));

	CBST<int, MY_TYPE>::iterator iter = cb1.begin();

	for (; iter != cb1.end(); ++iter)
	{
		cout << iter->first << endl;
	}


	iter = cb1.begin();
	//������ �˻�
	while (iter != cb1.end())
	{
		if (400 == iter->first)
		{
			break;
		}
		++iter;
	}

	iter;

	//�����켱 Ž��;
	iter = cb1.root();

	for (; iter != cb1.end(); iter.prepp())
	{
		cout << iter->first << endl;
	}

	cout << cb1.depth();

	//���� Ž�� Ʈ���� ��� Red-Black Tree �̴�. �����������δ� AVL Ʈ�����ִ�.
	//�ڰ� ���� ����Ž�� Ʈ��

	


	cb1.clear_r();



	return 0;
}