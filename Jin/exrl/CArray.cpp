#include "CArray.h"
#include <iostream>
using std::cout;
using std::endl;

// ������ �Ҹ���
// ũ�� �缳�� �Լ�
// ����, �̵� ������
// ����, �̵� ���� ������
// deep, shallow copy �Լ�

CArray::CArray()
	: maxCnt(10), curCnt(0), data(nullptr) 
{
	data = new int[maxCnt];
}

CArray::~CArray()
{
	delete[] data;
}

// ����
CArray::CArray(const CArray& _other)
	: maxCnt(_other.maxCnt), curCnt(_other.curCnt), data(nullptr)
{
	cout << "���� ������ ȣ��!" << endl;
	data = new int[maxCnt];
	for (int i = 0; i < maxCnt; ++i)
	{
		data[i] = _other.data[i];
	}
}

// �̵�
CArray::CArray(CArray&& _other)
	: maxCnt(_other.maxCnt), curCnt(_other.curCnt), data(_other.data)
{
	cout << "�̵� ������ ȣ��!" << endl;
	_other.maxCnt = 10; // 0�ΰ�?
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

// ���� ����
CArray& CArray :: operator =(const CArray& _other)
{
	cout << "���� ���� ������ ȣ��!" << endl;
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

// ���� �̵�
CArray& CArray::operator=(CArray&& _other)
{
	cout << "���� �̵� ������ ȣ��!" << endl;
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


