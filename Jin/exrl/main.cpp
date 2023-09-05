/*

CopyShallow�Լ��� CopyDeep �Լ�����(CopyShallow ���� ���� ���°� Ȯ�� �� �ּ�ó��) / 
����Ʈ ���� �ٸ� ������ ��ü�� ���� - int�ϳ��� new�� �����Ǵ� ������ �ϳ��� ������ ���� ��ü


*/

#include "CArray.h"
#include <stdio.h>
#include <iostream>

void CopyShallow(CArray _arr1, CArray _arr2)
{
	CArray tmp = _arr1;
	_arr1 = _arr2;
	_arr2 = tmp;
}

void CopyDeep(CArray& _arr1, CArray& _arr2)
{
	CArray tmp = std::move(_arr1);
	_arr1 = std::move(_arr2);
	_arr2 = std::move(tmp);
}

int main()
{
	CArray arr1;
	for (int i = 0; i < 20; ++i)
	{
		arr1.pushData(i);
	}

	CArray arr2;
	for (int i = 0; i < 100; ++i)
	{
		arr2.pushData(i);
	}
	CopyShallow(arr1, arr2);
}