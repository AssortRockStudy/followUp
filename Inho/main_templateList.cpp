#include <crtdbg.h>

#include "templateList.h"

int main() {
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    //_CrtSetBreakAlloc(163);
    templateList<int> tl;

    for (int i = 0; i < 5; i++) {
        tl.push_back(i);
    }
    for (int i = 5; i < 10; i++) {
        tl.push_front(i);
    }
    templateList<int>::printAll(tl);

    for (auto it = tl.begin(); it != tl.end();) {
        if (*it % 2 == 0) {
            it = tl.erase(it);
        } else {
            it++;
        }
    }

    templateList<int>::printAll(tl);
    cout << tl.front() << " " << tl.back() << endl;
    tl.Pop_back();
    tl.Pop_front();
    templateList<int>::printAll(tl);

    return 0;
}