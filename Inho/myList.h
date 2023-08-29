#pragma once
#include <assert.h>

#include <iostream>

using std::cout;
using std::endl;

struct Node {
    int data;
    Node* next;
    Node* prev;

    Node() : data(0), next(nullptr), prev(nullptr){};
    Node(int _data, Node* _next = nullptr, Node* _prev = nullptr)
        : data(_data), next(_next), prev(_prev){};
};

class myList {
    class iterator;

   private:
    Node* head;
    Node* tail;
    int curCount;

   public:
    // constructor destroyer
    myList() : head(nullptr), tail(nullptr), curCount(0) {
        cout << "default constructor call!" << endl;
    };
    myList(const myList& _other) : head(nullptr), tail(nullptr), curCount(0) {
        cout << "copy constructor call!" << endl;

        Node* n = _other.head;
        for (int i = 0; i < _other.curCount; i++) {
            this->push_back(n->data);
            n = n->next;
        }
    };
    myList(myList&& _other) noexcept
        : head(_other.head), tail(_other.tail), curCount(_other.curCount) {
        cout << "move constructor call!" << endl;
        _other.head = nullptr;
        _other.tail = nullptr;
        _other.curCount = 0;
    };
    ~myList();

    // push_back, push_front
    void push_back(int _data);
    void push_front(int _data);
    iterator erase(const iterator& _it);

    // begin, end
    iterator begin();
    iterator end();

    // operator
    inline myList& operator=(const myList& _other) {
        cout << "= operator call !!!" << endl;

        if (this->head != nullptr) {
            Node* n = this->head;
            for (int i = 0; i < this->curCount; i++) {
                Node* next = n->next;
                delete n;
                n = next;
            }
        }

        this->curCount = 0;

        Node* n = _other.head;
        for (int i = 0; i < _other.curCount; i++) {
            this->push_back(n->data);
            n = n->next;
        }
        return *this;
    }

    inline myList& operator=(myList&& _other) {
        cout << "= move operator call !!!" << endl;

        if (this->head != nullptr) {
            Node* n = this->head;
            for (int i = 0; i < this->curCount; i++) {
                Node* next = n->next;
                delete n;
                n = next;
            }
        }

        this->head = _other.head;
        this->tail = _other.tail;
        this->curCount = _other.curCount;

        _other.head = nullptr;
        _other.tail = nullptr;
        _other.curCount = 0;

        return *this;
    }

    // iterator
    class iterator {
       private:
        // friend myList
        // owner, node
        friend myList;
        myList* owner;
        Node* node;
        int idx;

        // constructor destroyer
       public:
        iterator() : owner(nullptr), node(nullptr), idx(-1){};
        iterator(myList* _owner, int _idx) : owner(_owner), idx(_idx) {
            Node* n = owner->head;
            node = nullptr;
            for (int i = 0; i < idx + 1; i++) {
                Node* next = n->next;
                node = n;
                n = next;
            }
        };
        ~iterator(){};

       public:
        // operator == != ++ --(pre, post)
        inline bool operator==(const iterator& _it) {
            if (this->owner != _it.owner || this->idx != _it.idx ||
                this->node != _it.node) {
                return false;
            }
            return true;
        };
        inline bool operator!=(const iterator& _it) { return !(*this == _it); };
        inline iterator& operator++() {
            if (this->idx < 0 || this->idx > this->owner->curCount) {
                cout << (this->idx) << " "
                     << (this->idx >= this->owner->curCount) << endl;
                assert(nullptr);
            }
            idx++;
            node = node->next;
            if (this->idx >= owner->curCount) {
                idx = -2;
                node = nullptr;
            }
            return *this;
        };
        inline iterator& operator++(int) {
            iterator before = *this;
            ++(*this);
            return before;
        };
        inline iterator& operator--() {
            if (this->idx < 0) {
                assert(nullptr);
            }
            idx--;
            node = node->prev;

            return *this;
        };
        inline iterator& operator--(int) {
            iterator before = *this;
            --(*this);
            return before;
        };
        inline int& operator*() { return node->data; }
    };

    // print
    void printAll();
    static void printNode(iterator& _it);
};
