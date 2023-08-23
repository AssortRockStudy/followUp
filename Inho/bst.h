#pragma once

template <typename T1, typename T2>
class Pair {
   public:
    T1 first;
    T2 second;

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
class bst {
   private:
    enum { origin, left, right };
    class Node {
        friend class bst;
        Pair<T1, T2>* pair;
        Node* direction[3];

       public:
        Node(){};
        Node(const Pair<T1, T2>& _pair, Node* _origin = nullptr,
             Node* _left = nullptr, Node* _right = nullptr) {
            pair = new Pair<T1, T2>(_pair.first, _pair.second);
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

        Node* next = curNode;
        T1 newKey = newNode->pair->first;
        int direction;
        while (next) {
            curNode = next;
            T1 curKey = curNode->pair->first;
            if (newKey < curKey) {
                next = curNode->direction[left];
                direction = left;
            } else if (newKey > curKey) {
                next = curNode->direction[right];
                direction = right;
            } else {
                delete newNode;
                return;
            }
        }
        if (direction == left) {
            curNode->direction[left] = newNode;

        } else if (direction == right) {
            curNode->direction[right] = newNode;
        }
        newNode->direction[origin] = curNode;
    }

    curCount++;
}
