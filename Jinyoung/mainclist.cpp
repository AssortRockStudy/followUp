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

	Pair<int, float> p1(1, 1.1f);
	Pair<int, float> p2(2, 2.2f);
	Pair<int, float> p3(3, 3.3f);
	Pair<int, float> p4(4, 4.4f);
	CBST<int, float> cb1;


	//���� Ž�� Ʈ���� ��� Red-Black Tree �̴�. �����������δ� AVL Ʈ�����ִ�.
	//�ڰ� ���� ����Ž�� Ʈ��
	//
	cb1.pushdata(p1);

	cb1.pushdata(p2);

	cb1.clear_r();

	return 0;
}