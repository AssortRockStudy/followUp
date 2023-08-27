#pragma once
#pragma once

//int 타입 데이터를 저장하는 가변배열
template <typename T>
struct tArray
{
	T* pData;   //데이터를 저장하는 힙 메모리 주소
	int iCurCount;//현재 데이터 개수
	int imaxCount; //최대 갯수 
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
		//1. 더큰 공간을 힙 영역에 할당
		T* ntypep = (T*)malloc((sizeof(T) * (pArr->imaxCount * 2)));
		//2. 기존에 가지고 있던 데이터를 옮긴다.
		for (int i = 0; i < pArr->imaxCount; ++i)
		{
			ntypep[i] = pArr->pData[i];
		}
		pArr->imaxCount *= 2;
		//3. 기존공간을 해제시킨다
		free(pArr->pData);
		//4. 기존 공간 주소를 새로운 공간 주소로 바꾼다.
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