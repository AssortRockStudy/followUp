#pragma once
#include <iostream>

#include "templateList.h"
using namespace std;

template <typename T1, typename T2>
class Pair {
   public:
    T1 first;
    T2 second;

    Pair() : first(0), second(0){};
    Pair(const Pair& _other) : first(_other.first), second(_other.second){};
    Pair(const T1& _first, const T2& _second)
        : first(_first), second(_second){};

    Pair& operator=(const Pair& _other) {
        first = _other.first;
        second = _other.second;
        return *this;
    }
    Pair& operator=(Pair&& _other) {
        first = _other.first;
        second = _other.second;
        _other.first = 0;
        _other.second = 0;
        return *this;
    }
    bool operator==(const Pair& _other) {
        if (first == _other.first && second == _other.second) {
            return true;
        } else {
            return false;
        }
    }
    bool operator!=(const Pair<T1, T2>& _other) {
        return !(*this->operator==(_other));
    }
    friend ostream& operator<<(ostream& os, const Pair<T1, T2>& pair) {
        os << "first is: " << pair.first << ", second is: " << pair.second;
        return os;
    }
};

template <typename T1, typename T2>
Pair<T1, T2> Create_Pair(const T1& _first, const T2& _second) {
    Pair<T1, T2> data;
    data.first = _first;
    data.second = _second;
    return data;
}

template <typename T1, typename T2>
class bst {
   private:
    enum { origin, left, right };
    class Node {
        friend class bst;
        Pair<T1, T2> pair;
        Node* direction[3];

       public:
        Node(){};
        Node(const Pair<T1, T2>& _pair, Node* _origin = nullptr,
             Node* _left = nullptr, Node* _right = nullptr) {
            pair = _pair;
            direction[origin] = _origin;
            direction[left] = _left;
            direction[right] = _right;
        }

       public:
        // 부울 리턴하는 간단 함수
        bool hasLChild() { return direction[left]; }
        bool hasRChild() { return direction[right]; }
        bool isRoot() { return !direction[origin]; }

        bool isLChild() { return direction[origin]->direction[left] == this; }
        bool isRChild() { return direction[origin]->direction[right] == this; }
    };

    Node* root;
    int curCount;

   public:
    bst() : root(nullptr), curCount(0){};
    ~bst(){};

    void insert(const Pair<T1, T2>& _data);
    void insert(const T1& _first, const T2& _second);
    void Clear();
    void Clear_recursive(Node* _node);

   public:
    class iterator;
    iterator begin() {
        Node* target = root;
        Node* next = target;
        if (!target) {
            return end();
        }

        while (next) {
            target = next;
            next = target->direction[left];
        }
        return iterator(this, target);
    };
    iterator end() { return iterator(this, nullptr); };

    void printPrev();
    void printIn();
    void printPost();

   public:
    class iterator {
       private:
        bst* owner;
        Node* target;

       public:
        iterator() : owner(nullptr), target(nullptr){};
        iterator(bst* _owner, Node* _target) : owner(_owner), target(_target){};
        ~iterator(){};

       public:
        // operator overloading
        bool operator==(const iterator& _it) {
            return owner == _it.owner && target == _it.target;
        }
        bool operator!=(const iterator& _it) { return !((*this) == _it); }
        Pair<T1, T2> operator*() { return target->pair; }
        Pair<T1, T2>* operator->() { return &(target->pair); }

        iterator& operator++() {
            // 중위 순회로
            // 중위 선행자를 찾아야 함 (successor)

            Node* successor = target;
            assert(successor);

            // 오른쪽 자식이 있을 때
            if (successor->hasRChild()) {
                successor = successor->direction[right];
                while (successor->direction[left]) {
                    successor = successor->direction[left];
                }
            }
            // 오른쪽 자식이 없을 때
            // 왼쪽 자식이 될 때 까지 올라감
            else {
                while (true) {
                    if (successor->isRoot()) {
                        successor = nullptr;
                        break;
                    }

                    if (successor->isLChild()) {
                        successor = successor->direction[origin];
                        break;
                    }
                    successor = successor->direction[origin];
                }
            }
            target = successor;
            return *this;
        }
        iterator& operator--() {
            // 중위 후행자를 찾아야 함
            // 선행자와 전혀 반대
            // 왼쪽 자식이 있다면, 왼쪽 자식이 후행자
            // 왼쪽자식이 없다면 오른쪽 자식이 될 때 까지

            Node* predecessor = target;

            if (*this == owner->end()) {
                predecessor = owner->root;
                while (predecessor->direction[right]) {
                    predecessor = predecessor->direction[right];
                }
                target = predecessor;
                return *this;
            }

            assert(predecessor);
            if (predecessor->hasLChild()) {
                predecessor = predecessor->direction[left];

            } else {
                while (true) {
                    if (predecessor->isRoot()) {
                        predecessor = nullptr;
                        break;
                    }

                    if (predecessor->isRChild()) {
                        predecessor = predecessor->direction[origin];
                        break;
                    }
                    predecessor = predecessor->direction[origin];
                }
            }
            target = predecessor;
            return *this;
        }
        iterator& operator++(int) {
            iterator copy(this);
            ++this;
            return copy;
        }
        iterator& operator--(int) {
            iterator copy(this);
            --this;
            return copy;
        }
    };
};

template <typename T1, typename T2>
inline void bst<T1, T2>::insert(const Pair<T1, T2>& _data) {
    Node* newNode = new Node(_data);

    if (root == nullptr) {
        root = newNode;
    } else {
        Node* curNode = root;
        T1 newKey = newNode->pair.first;

        while (curNode) {
            T1 curKey = curNode->pair.first;

            if (newKey < curKey) {
                if (curNode->direction[left]) {
                    curNode = curNode->direction[left];
                } else {
                    curNode->direction[left] = newNode;
                    newNode->direction[origin] = curNode;
                    break;
                }
            } else if (newKey > curKey) {
                if (curNode->direction[right]) {
                    curNode = curNode->direction[right];
                } else {
                    curNode->direction[right] = newNode;
                    newNode->direction[origin] = curNode;
                    break;
                }
            } else {
                curNode->pair.second = newNode->pair.second;
                return;
            }
        }
    }

    curCount++;
}

template <typename T1, typename T2>
inline void bst<T1, T2>::insert(const T1& _first, const T2& _second) {
    insert({_first, _second});
}

template <typename T1, typename T2>
inline void bst<T1, T2>::Clear() {
    Node* curNode = root;
    if (!curNode) return;

    templateList<Node*> deq;
    deq.push_back(curNode);

    while (!deq.empty()) {
        curNode = deq.front();
        deq.Pop_front();

        if (curNode->direction[left]) {
            deq.push_back(curNode->direction[left]);
        }
        if (curNode->direction[right]) {
            deq.push_back(curNode->direction[right]);
        }

        delete curNode;
        curCount--;
    }
}

template <typename T1, typename T2>
inline void bst<T1, T2>::Clear_recursive(Node* _node) {
    if (_node == nullptr) {
        return;
    }
    // 리프노드라면 삭제
    // 왼쪽, 오른쪽 모두 nullptr
    // 왼쪽부터 nullptr 아니면 재귀
    if (_node->direction[left]) {
        Clear_recursive(_node->direction[left]);
    }
    if (_node->direction[right]) {
        Clear_recursive(_node->direction[right]);
    }

    delete _node;
    curCount--;
}