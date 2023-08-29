#include "CArray.h"
#include <iostream>
using std::cout;
using std::endl;

// 생성자 소멸자
// 크기 재설정 함수
// 복사, 이동 생성자
// 복사, 이동 대입 연산자
// deep, shallow copy 함수

CArray::CArray()
	: maxCnt(10), curCnt(0), data(nullptr) 
{
	data = new int[maxCnt];
}

CArray::~CArray()
{
	delete[] data;
}

// 복사
CArray::CArray(const CArray& _other)
	: maxCnt(_other.maxCnt), curCnt(_other.curCnt), data(nullptr)
{
	cout << "복사 생성자 호출!" << endl;
	data = new int[maxCnt];
	for (int i = 0; i < maxCnt; ++i)
	{
		data[i] = _other.data[i];
	}
}

// 이동
CArray::CArray(CArray&& _other)
	: maxCnt(_other.maxCnt), curCnt(_other.curCnt), data(_other.data)
{
	cout << "이동 생성자 호출!" << endl;
	_other.maxCnt = 10; // 0인가?
	_other.curCnt = 0;
	_other.data = nullptr;
}

void CArray::pushData(int _data)
{
	if (curCnt >= maxCnt)
	{
		resize();
	}
	data[curCnt++] = _data;
}

void CArray::resize()
{
	int* newData = new int[maxCnt * 2];
	for (int i = 0; i < curCnt; ++i)
	{
		newData[i] = data[i];
	}
	delete[] data;
	data = newData;
	maxCnt *= 2;
}

// 대입 복사
CArray& CArray :: operator =(const CArray& _other)
{
	cout << "대입 복사 연산자 호출!" << endl;
	if (nullptr != data)
	{
		delete[] data;
	}
	else
	{
		data = new int[maxCnt];
		curCnt = _other.curCnt;
		maxCnt = _other.maxCnt;
		for (int i = 0; i < curCnt; ++i)
		{
			data[i] = _other.data[i];
		}
	}
	return *this;
}

// 대입 이동
CArray& CArray::operator=(CArray&& _other)
{
	cout << "대입 이동 연산자 호출!" << endl;
	if (nullptr != data)
	{
		delete[] data;
	}
	else
	{
		curCnt = _other.curCnt;
		maxCnt = _other.maxCnt;
		data = _other.data;
		
		_other.curCnt = 0;
		_other.maxCnt = 10;
		_other.data = nullptr;
	}
	return *this;
}


