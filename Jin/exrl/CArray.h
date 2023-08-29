#pragma once
class CArray
{
public:
	int		maxCnt;
	int		curCnt;
	int* data;

	void resize();

	CArray();
	~CArray();
	CArray(const CArray& _other);
	CArray(CArray&& _other);
	CArray& operator=(const CArray& _other);
	CArray& operator=(CArray&& _other);
	void pushData(int _data);
};

