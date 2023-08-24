#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "CList.h"
#include "TCList.h"
#include "bst.h"

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

	CList cl;

	

	for (int i = 0; i < 3; ++i)
	{
		cl.pushback(i+1);
	}

	CList::iterator it;

	


	//////////////////////230821 0417����///////////////////////////

	for (it = cl.begin(); cl.end() != it;)
	{
		it = cl.erase(it);
	}

	for (it = cl.begin(); cl.end() != it; ++it)
	{
		cout << *it << endl;
	}
	//////////////////////230821 0417����///////////////////////////


	//deepcopy �׽�Ʈ
	CList c1;
	for (int i = 0; i < 3; ++i)
	{
		c1.pushback(i + 1);
	}

	
	CList c2;
	c2.CopyDeep(c1);

	//��������� �׽�Ʈ
	CList c3 = c1;

	//�̵������� �׽�Ʈ
	CList c4 = std::move(c1);

	//���Կ����� �׽�Ʈ
	CList c5;
	c5 = c2;

	//�̵� ���� ������ �׽�Ʈ
	CList c6;
	c6 = std::move(c3);


	//swap �׽�Ʈ
	CList c7;
	for (int i = 0; i < 3; ++i)
	{
		c7.pushfront(i + 1);
	}

	c6.swap(std::move(c7));


	TCList<CList> tcl1;

	tcl1.pushback(c1);
	tcl1.pushback(c2);
	tcl1.pushback(c3);


	Pair<int, float> p1(1, 1.1f);
	Pair<int, float> p2(2, 2.2f);
	Pair<int, float> p3(3, 3.3f);
	Pair<int, float> p4(4, 4.4f);
	CBST<int, float> cb1;

	cb1.pushdata(p1);

	cb1.pushdata(p2);

	return 0;
}