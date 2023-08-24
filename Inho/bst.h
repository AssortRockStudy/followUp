#pragma once
#include "templateList.h"

template <typename T1, typename T2>
class Pair {
   public:
    T1 first;
    T2 second;

    Pair(){};
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
    };

    Node* root;
    int curCount;

   public:
    bst() : root(nullptr), curCount(0){};
    ~bst(){};

    void insert(const Pair<T1, T2>& _data);
    void insert(const T1& _first, const T2& _second);
    void Clear();

    void printPrev();
    void printIn();
    void printPost();
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
    }
}
