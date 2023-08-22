/*

CopyShallow함수와 CopyDeep 함수구현(CopyShallow 사용시 오류 나는거 확인 후 주석처리) / 
리스트 말고 다른 간단한 객체로 실험 - int하나와 new로 생성되는 데이터 하나를 변수로 갖는 객체


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