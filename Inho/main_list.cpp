#include "myList.h"

class swapClass {
   private:
    int idx;
    int* arr;
    int curCnt;

   public:
    swapClass(int _idx) : idx(_idx), arr(nullptr), curCnt(0) {
        arr = new int[3];
    };
    ~swapClass() { delete[] arr; }

    void push_data(int _data) { arr[curCnt++] = _data; }

    static void swapShallow(swapClass& s1, swapClass& s2) {
        swapClass temp = s1;
        s1 = s2;
        s2 = temp;
    };

    static void swapDeep(swapClass& s1, swapClass& s2) {
        swapClass temp = s2;
        s2.curCnt = s1.curCnt;
        s2.arr = s1.arr;
        s2.idx = s1.idx;

        s1 = temp;
        s1.arr = new int[3];
        for (int i = 0; i < s1.curCnt; i++) {
            s1.arr[i] = temp.arr[i];
        }
        // delete[] temp.arr;
    }
};

int main() {
    myList ml;

    for (int i = 0; i < 5; i++) {
        ml.push_back(i);
    }
    ml.printAll();

    for (int i = 5; i < 10; i++) {
        ml.push_front(i);
    }
    ml.printAll();

    for (auto it = ml.begin(); it != ml.end();) {
        if (*it > 3) {
            it = ml.erase(it);
        } else {
            it++;
        }
        if (it == ml.end()) {
            break;
        }
    }

    ml.printAll();

    // ??? ???? ?????? ???
    // ??? ?????? ?????? ??????? ???????? ??©£???? ???????? move??? ???
    // myList ml2 = std::move(ml);

    myList ml2;
    myList ml3;

    ml2 = ml;
    myList ml4 = ml;

    myList ml5 = std::move(ml);
    ml3 = std::move(ml);

    //{
    //    swapClass s1(3), s2(5);
    //    s1.push_data(1);
    //    s1.push_data(2);
    //    s1.push_data(3);

    //    s2.push_data(4);
    //    s2.push_data(5);
    //    s2.push_data(6);

    //    // swapClass::swapShallow(s1, s2);
    //    swapClass::swapDeep(s1, s2);
    //}

    return 0;
}