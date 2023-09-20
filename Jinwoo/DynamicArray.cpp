#include <iostream>

using std::cout;
using std::endl;

class MyClass
{
private:
	int			Count;
	int			MaxCount;
	char*		Data;

public:
	MyClass(const MyClass& _Other) : Count(_Other.Count), MaxCount(_Other.MaxCount), Data(nullptr)
	{
		cout << "복사 생성자 호출!" << endl;

		Data = new char[MaxCount];

		for (int i = 0; i < Count; ++i)
		{
			Data[i] = _Other.Data[i];
		}
	}

	// 이동생성자는 r-value값을 참조하여 다른 객체의 데이터를 그대로 가져오고 가져올 때 사용한 객체는 해제한다
	MyClass(MyClass&& _Other) noexcept : Count(_Other.Count), MaxCount(_Other.MaxCount), Data(_Other.Data)
	{
		cout << "이동 생성자 호출!" << endl;

		_Other.Count = 0;
		_Other.MaxCount = 0;
		_Other.Data = nullptr;
	}

	MyClass& operator = (const MyClass& _Other)
	{
		cout << "대입 연산자 호출!" << endl;

		if (nullptr != Data)
		{
			delete[] Data;
		}

		// _Other의 데이터 복사
		Count = _Other.Count;
		MaxCount = _Other.MaxCount;

		// _Other와 동일한 크기의 메모리 할당
		Data = new char[MaxCount];

		// _Other의 값 옮겨오기
		for (int i = 0; i < Count; ++i)
		{
			Data[i] = _Other.Data[i];
		}

		return *this;
	}

	MyClass& operator = (MyClass&& _Other)
	{
		cout << "이동대입 연산자 호출!" << endl;

		if (nullptr != Data)
		{
			delete[] Data;
		}

		Count = _Other.Count;
		MaxCount = _Other.MaxCount;
		Data = _Other.Data;

		// 이동대입이므로 _Other 데이터 삭제
		_Other.Count = 0;
		MaxCount = 0;
		Data = nullptr;

		return *this;
	}

	void print()
	{
		cout << "Count : " << Count << endl;
	}

public:
	MyClass() : Count(0), MaxCount(2)
	{
		Data = new char[MaxCount];
	}

	MyClass(int _Count, int _MaxCount, char* _Data) : Count(_Count), MaxCount(_MaxCount), Data(_Data)
	{
		cout << "생성자 호출" << endl;
	}

	~MyClass()
	{
		cout << "소멸자 호출" << endl;
		delete[] Data;
	}
};

int main()
{
	MyClass myclass;

	// 얕은 복사
	// MyClass ShallowCopy = myclass;

	// 깊은 복사
	MyClass DeepCopy(myclass);

	return 0;
}