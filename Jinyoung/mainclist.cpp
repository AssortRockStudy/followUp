#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "TCList.h"
#include "bst.h"
#include <crtdbg.h>
#include <map>



using std::cout;
using std::cin;
using std::endl;


/*
해야할것
1.이터레이터 구현하기
	begin end erase insert 구현하기
2.push front push back 함수 구현하기
3.전위후위 ++연산자 오버로딩
4.!= 연산자 오버로딩

*/
/*헷갈려서봤던것
1. 인수 전달안해도 알아서 디폴트로 채워주는 인자전달되는것 node에있던건지 clist에있던건지
2. tnode랑 clist중 어디가 class엿는지. 생성자는 어디에 구현되어있엇는지(둘다엿다)
3. 이터레이터 멤버확인
4. ++연산자 오버로딩 이터레이터에하는지 clist에하는지
5. cpp에 함수구현되어 있는 종류 파악
6. clist 클래스에 반환타입 iterator 주려니 빨간줄떠서 전방선언둔것
7. 후위연산자 연산과정& 반환타입
8. erase insert 구현위치
*/


/*
아직의문인것
1. 반환타입을 레퍼런스로 남발하면 안되는가? (예를들면 erase함수의 반환타입을 레퍼런스로 주면안되는가?)
2. 어디까지 인라인 함수로 할 수 있는지 기준이 모호하다고 생각함 (일단 인라인이 편해서 다그렇게 작성하는중)
2. operator == 오버로딩중 인자를 const 로 가져오는 이유(까먹음ㅎㅎ)
*/


int main() {
	enum MY_TYPE
	{
		TYPE1,
		TYPE2,
		TYPE3,
		NONE,
	};

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(170);
	TCList<int> tcl;

	for (int i = 0; i < 3; ++i)
	{
		tcl.pushback(i+1);
	}

	typename TCList<int>::iterator it;

	

	
	//////////////////////230821 0417수정///////////////////////////

	for (it = tcl.begin(); tcl.end() != it;)
	{
		it = tcl.erase(it);
	}

	for (it = tcl.begin(); tcl.end() != it; ++it)
	{
		cout << *it << endl;
	}
	//////////////////////230821 0417수정///////////////////////////


	//deepcopy 테스트
	TCList<int> c1;
	for (int i = 0; i < 3; ++i)
	{
		c1.pushback(i + 1);
	}

	
	TCList<int> c2;
	c2.CopyDeep(c1);

	//복사생성자 테스트
	TCList<int> c3 = c1;

	//이동생성자 테스트
	TCList<int> c4 = std::move(c1);

	//대입연산자 테스트
	TCList<int> c5;
	c5 = c2;

	//이동 대입 연산자 테스트
	TCList<int> c6;
	c6 = std::move(c3);

	TCList<int> c8;
	for (int i = 0; i < 3; ++i)
	{
		c8.pushback(i + 1);
	}

	//swap 테스트
	TCList<int> c7;
	for (int i = 0; i < 3; ++i)
	{
		c7.pushfront(i + 1);
	}

	c8.swap(std::move(c7));


	TCList< TCList<int>> tcl1;

	tcl1.pushback(c1);
	tcl1.pushback(c2);
	tcl1.pushback(c4);

	CBST<int, MY_TYPE> cb1;

	cb1.pushdata(Create_Pair(100, MY_TYPE::TYPE1)); //				    100
	cb1.pushdata(Create_Pair(70, MY_TYPE::TYPE1));  //			70				150	
	cb1.pushdata(Create_Pair(150, MY_TYPE::TYPE1)); //	  50		80		125		  175
	cb1.pushdata(Create_Pair(50, MY_TYPE::TYPE1)); //	25  60	  75  90   110 140   160  200
	cb1.pushdata(Create_Pair(80, MY_TYPE::TYPE1));
	cb1.pushdata(Create_Pair(25, MY_TYPE::TYPE1));
	cb1.pushdata(Create_Pair(60, MY_TYPE::TYPE1));
	cb1.pushdata(Create_Pair(75, MY_TYPE::TYPE1));
	cb1.pushdata(Create_Pair(90, MY_TYPE::TYPE1));
	cb1.pushdata(Create_Pair(125, MY_TYPE::TYPE1));
	cb1.pushdata(Create_Pair(175, MY_TYPE::TYPE1));
	cb1.pushdata(Create_Pair(110, MY_TYPE::TYPE1));
	cb1.pushdata(Create_Pair(140, MY_TYPE::TYPE1));
	cb1.pushdata(Create_Pair(160, MY_TYPE::TYPE1));
	cb1.pushdata(Create_Pair(200, MY_TYPE::TYPE1));
	cb1.pushdata(Create_Pair(400, MY_TYPE::TYPE1));
	cb1.pushdata(Create_Pair(500, MY_TYPE::TYPE1));

	CBST<int, MY_TYPE>::iterator iter = cb1.begin();

	for (; iter != cb1.end(); ++iter)
	{
		cout << iter->first << endl;
	}


	iter = cb1.begin();
	//데이터 검색
	while (iter != cb1.end())
	{
		if (400 == iter->first)
		{
			break;
		}
		++iter;
	}

	iter;

	//전위우선 탐색;
	iter = cb1.root();

	for (; iter != cb1.end(); iter.prepp())
	{
		cout << iter->first << endl;
	}

	cout << cb1.depth();

	//이진 탐색 트리는 사실 Red-Black Tree 이다. 같은개념으로는 AVL 트리가있다.
	//자가 균형 이진탐색 트리

	


	cb1.clear_r();
	//Map의 키 타입을 클래스로 지정한 경우,해당 클래스는 비교연산자들이 구현(오버로딩) 되어있어야 한다.
//해당 타입 변수 끼리 비교헀을때 우열을 나누는 기준이 마련되어있어야함.

	const char* pStr = "asdasd";
	const wchar_t* pWStr = L"asdv";

	map<const char*, int> mapStr;

	mapStr.insert(make_pair("Player", 100));
	mapStr.insert(make_pair("Monster", 200));
	mapStr.insert(make_pair("BGM", 0));

	map<const char*, int>::iterator mapiter = mapStr.find("Player");

	//Find 실패
	//저장되어 있는 키 값은 "Player"문자열의 주소값
	//strTest 배열에서도 동일 문자열값이 들어있지만,배열의 이름(주소)로 검색을 하는 것 이기 때문에
	//동일한 주소값을 나타내는 "Player"로 검색햇을때만 find 가능

	map<string, int> mapString;
	mapString.insert(make_pair("Player", 100));
	mapString.insert(make_pair("Monster", 200));
	mapString.insert(make_pair("BGM", 0));

	char strTest[50] = "Player";

	map<string, int>::iterator strIter;
	strIter = mapString.find("Player");
	strIter = mapString.find(strTest);


	return 0;
}