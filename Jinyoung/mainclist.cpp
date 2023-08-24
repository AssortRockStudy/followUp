#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "CList.h"
#include "TCList.h"
#include "bst.h"

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

	CList cl;

	

	for (int i = 0; i < 3; ++i)
	{
		cl.pushback(i+1);
	}

	CList::iterator it;

	


	//////////////////////230821 0417수정///////////////////////////

	for (it = cl.begin(); cl.end() != it;)
	{
		it = cl.erase(it);
	}

	for (it = cl.begin(); cl.end() != it; ++it)
	{
		cout << *it << endl;
	}
	//////////////////////230821 0417수정///////////////////////////


	//deepcopy 테스트
	CList c1;
	for (int i = 0; i < 3; ++i)
	{
		c1.pushback(i + 1);
	}

	
	CList c2;
	c2.CopyDeep(c1);

	//복사생성자 테스트
	CList c3 = c1;

	//이동생성자 테스트
	CList c4 = std::move(c1);

	//대입연산자 테스트
	CList c5;
	c5 = c2;

	//이동 대입 연산자 테스트
	CList c6;
	c6 = std::move(c3);


	//swap 테스트
	CList c7;
	for (int i = 0; i < 3; ++i)
	{
		c7.pushfront(i + 1);
	}

	c6.swap(std::move(c7));


	TCList<CList> tcl1;

	tcl1.pushback(c1);
	tcl1.pushback(c2);
	tcl1.pushback(c3);


	Pair<int, float> p1(1, 1.1f);
	Pair<int, float> p2(2, 2.2f);
	Pair<int, float> p3(3, 3.3f);
	Pair<int, float> p4(4, 4.4f);
	CBST<int, float> cb1;

	cb1.pushdata(p1);

	cb1.pushdata(p2);

	return 0;
}