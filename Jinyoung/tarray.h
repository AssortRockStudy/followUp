#pragma once
#pragma once

//int Ÿ�� �����͸� �����ϴ� �����迭
template <typename T>
struct tArray
{
	T* pData;   //�����͸� �����ϴ� �� �޸� �ּ�
	int iCurCount;//���� ������ ����
	int imaxCount; //�ִ� ���� 
};

template <typename T>
void initArray(tArray<T>* pArr) {

	pArr->pData = (T*)malloc(sizeof(T) * 5);
	pArr->iCurCount = 0;
	pArr->imaxCount = 5;
}

template <typename T>
void pushData(tArray<T>* pArr, T data) {
	if ((pArr->iCurCount) >= (pArr->imaxCount)) {
		//1. ��ū ������ �� ������ �Ҵ�
		T* ntypep = (T*)malloc((sizeof(T) * (pArr->imaxCount * 2)));
		//2. ������ ������ �ִ� �����͸� �ű��.
		for (int i = 0; i < pArr->imaxCount; ++i)
		{
			ntypep[i] = pArr->pData[i];
		}
		pArr->imaxCount *= 2;
		//3. ���������� ������Ų��
		free(pArr->pData);
		//4. ���� ���� �ּҸ� ���ο� ���� �ּҷ� �ٲ۴�.
		pArr->pData = ntypep;
	}
	pArr->pData[(pArr->iCurCount)++] = data;
}

template <typename T>
void delArray(tArray<T>* pArr) {
	pArr->iCurCount = 0;
	pArr->imaxCount = 0;

	free(pArr->pData);
	pArr->pData = nullptr;

}

template <typename T>
void initArray(tArray<T>* pArr);

template <typename T>
void pushData(tArray<T>* pArr, T data);

template <typename T>
void delArray(tArray<T>* pArr);