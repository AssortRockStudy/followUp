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
		cout << "���� ������ ȣ��!" << endl;

		Data = new char[MaxCount];

		for (int i = 0; i < Count; ++i)
		{
			Data[i] = _Other.Data[i];
		}
	}

	// �̵������ڴ� r-value���� �����Ͽ� �ٸ� ��ü�� �����͸� �״�� �������� ������ �� ����� ��ü�� �����Ѵ�
	MyClass(MyClass&& _Other) noexcept : Count(_Other.Count), MaxCount(_Other.MaxCount), Data(_Other.Data)
	{
		cout << "�̵� ������ ȣ��!" << endl;

		_Other.Count = 0;
		_Other.MaxCount = 0;
		_Other.Data = nullptr;
	}

	MyClass& operator = (const MyClass& _Other)
	{
		cout << "���� ������ ȣ��!" << endl;

		if (nullptr != Data)
		{
			delete[] Data;
		}

		// _Other�� ������ ����
		Count = _Other.Count;
		MaxCount = _Other.MaxCount;

		// _Other�� ������ ũ���� �޸� �Ҵ�
		Data = new char[MaxCount];

		// _Other�� �� �Űܿ���
		for (int i = 0; i < Count; ++i)
		{
			Data[i] = _Other.Data[i];
		}

		return *this;
	}

	MyClass& operator = (MyClass&& _Other)
	{
		cout << "�̵����� ������ ȣ��!" << endl;

		if (nullptr != Data)
		{
			delete[] Data;
		}

		Count = _Other.Count;
		MaxCount = _Other.MaxCount;
		Data = _Other.Data;

		// �̵������̹Ƿ� _Other ������ ����
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
		cout << "������ ȣ��" << endl;
	}

	~MyClass()
	{
		cout << "�Ҹ��� ȣ��" << endl;
		delete[] Data;
	}
};

int main()
{
	MyClass myclass;

	// ���� ����
	// MyClass ShallowCopy = myclass;

	// ���� ����
	MyClass DeepCopy(myclass);

	return 0;
}