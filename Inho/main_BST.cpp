#include "bst.h"
#include <crtdbg.h>
#include <iostream>

using std::cout;
using std::endl;

int main() {
    bst<int, int> tree;
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    tree.insert(Create_Pair(100, 3));  //				    100
    tree.insert(Create_Pair(70, 3));  //			70				150
    tree.insert(Create_Pair(150, 3));  //	  50		80		125		  175
    tree.insert(Create_Pair(50, 3));  //	25  60	  75  90   110 140   160  200
    tree.insert(Create_Pair(80, 3));
    tree.insert(Create_Pair(25, 3));
    tree.insert(Create_Pair(60, 3));
    tree.insert(Create_Pair(75, 3));
    tree.insert(Create_Pair(90, 3));
    tree.insert(Create_Pair(125, 3));
    tree.insert(Create_Pair(175, 3));
    tree.insert(Create_Pair(110, 3));
    tree.insert(Create_Pair(140, 3));
    tree.insert(Create_Pair(160, 3));
    tree.insert(Create_Pair(200, 3));

    auto iter = tree.begin();
    for (iter = tree.begin(); iter != tree.end(); ++iter) {
        cout << (*iter).first << " ";
    }
    cout << endl;
    for (iter = --(tree.end()); iter != tree.begin(); --iter) {
        cout << (*iter).first << " ";
    }
    cout << endl;


    tree.Clear();
    //tree.Clear_recursive(tree.begin());

    return 0;
}