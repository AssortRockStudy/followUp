#pragma once
#include <assert.h>

#include <iostream>

using std::cout;
using std::endl;

// 노드 생성
// data, next, prev
// 생성자

// 리스트
// 헤드, 테일, 현재 개수
// push_back()
// begin, end, erase
// print
// 생성자 소멸자
// 복사 생성자, 이동 생성자
// 대입 연산자, 이동대입 연산자

// 이터레이터
// 오너, 노드
// 생성자 소멸자
// ++, --, ==, !=, *

template <typename T>
class templateList {
   private:
    struct Node {
        T data;
        Node* next;
        Node* prev;

       public:
        Node() : data(nullptr), next(nullptr), prev(nullptr){};
        Node(T _data, Node* _next = nullptr, Node* _prev = nullptr)
            : data(_data), next(_next), prev(_prev){};
        ~Node(){};
    };
    class iterator {
        friend class templateList;

       private:
        templateList* owner;
        Node* node;

       public:
        iterator() : owner(nullptr), node(nullptr){};
        iterator(templateList* _owner, Node* _node)
            : owner(_owner), node(_node){};
        ~iterator(){};

       public:
        bool operator==(const iterator& _it) {
            if (this->owner == _it.owner && this->node == _it.node) {
                return true;
            } else
                return false;
        }
        bool operator!=(const iterator& _it) { return !this->operator==(_it); }

        iterator& operator++() {
            if (this == nullptr || *this == this->owner->end()) {
                assert(nullptr);
            }
            this->node = this->node->next;
            return *this;
        }
        iterator& operator--() {
            if (this == nullptr || this->node == this->owner->head) {
                assert(nullptr);
            }
            this = this->prev;

            return *this;
        }

        iterator& operator++(int i) {
            auto post = this;
            ++(*this);
            return *post;
        }

        iterator& operator--(int i) {
            auto post = this;
            --(*this);
            return *post;
        }

        T& operator*() { return node->data; }
    };

    Node* head;
    Node* tail;
    int curCount;

   public:
    templateList() : head(nullptr), tail(nullptr), curCount(0){};
    templateList(const templateList& _other);
    templateList(templateList&& _other) noexcept;
    ~templateList(){};

   public:
    templateList& operator=(const templateList& _other);
    templateList& operator=(templateList&& _other);

   public:
    void push_back(const T& _data);
    void push_front(const T& _data);
    iterator erase(const iterator& _it);

   public:
    iterator begin();
    iterator end();

    static void printAll(templateList& tl);
};

template <typename T>
inline templateList<T>::templateList(const templateList& _other)
    : head(nullptr), tail(nullptr), curCount(0) {
    std::cout << "copy constructor call !!" << endl;
    Node* now = _other.head;
    for (int i = 0; i < _other.curCount; i++) {
        Node* next = now->next;
        this->push_back(now->data);
        now = next;
    }
}

template <typename T>
inline templateList<T>::templateList(templateList&& _other) noexcept
    : head(_other.head), tail(_other.tail), curCount(_other.curCount) {
    std::cout << "move constructor call !!" << endl;

    _other.curCount = 0;
    _other.head = nullptr;
    _other.tail = nullptr;
}

template <typename T>
inline templateList<T>& templateList<T>::operator=(const templateList& _other) {
    cout << "call = operator !! " << endl;
    if (this->head != nullptr) {
        Node* now = this->head;
        for (int i = 0; i < curCount; i++) {
            Node* next = now->next;
            delete now;
            now = next;
        }
    }
    this->curCount = 0;
    this->head = nullptr;
    this->tail = nullptr;

    Node* now = _other.head;
    for (int i = 0; i < _other.curCount; i++) {
        Node* next = now->next;
        push_back(now->data);
        now = next;
    }
    return *this;
}

template <typename T>
inline templateList<T>& templateList<T>::operator=(templateList&& _other) {
    cout << "call move = operator !! " << endl;
    if (this->head != nullptr) {
        Node* now = this->head;
        for (int i = 0; i < curCount; i++) {
            Node* next = now->next;
            delete now;
            now = next;
        }
    }

    this->curCount = _other.curCount;
    this->head = _other.head;
    this->tail = _other.tail;

    _other.curCount = 0;
    _other.head = nullptr;
    _other.tail = nullptr;

    return *this;
}

template <typename T>
inline void templateList<T>::push_back(const T& _data) {
    Node* newNode = new Node(_data, nullptr, tail);
    if (this->head == nullptr) {
        this->head = newNode;
        this->tail = newNode;
    } else {
        this->tail->next = newNode;
        this->tail = newNode;
    }
    curCount++;
}
template <typename T>
inline void templateList<T>::push_front(const T& _data) {
    Node* newNode = new Node(_data, head, nullptr);
    if (this->head == nullptr) {
        this->head = newNode;
        this->tail = newNode;
    } else {
        this->head->prev = newNode;
        this->head = newNode;
    }
    curCount++;
}

template <typename T>
inline typename templateList<T>::iterator templateList<T>::erase(
    const iterator& _it) {
    Node* deleteNode = _it.node;
    if (deleteNode->prev == nullptr) {
        this->head = deleteNode->next;
        deleteNode->next->prev = nullptr;
    } else {
        deleteNode->prev->next = deleteNode->next;
    }
    if (deleteNode->next == nullptr) {
        this->tail = deleteNode->prev;
    } else {
        deleteNode->next->prev = deleteNode->prev;
    }
    Node* returnNode = deleteNode->next;
    delete deleteNode;
    curCount--;
    return iterator(this, returnNode);
}

template <typename T>
inline typename templateList<T>::iterator templateList<T>::begin() {
    return iterator(this, head);
}
template <typename T>
inline typename templateList<T>::iterator templateList<T>::end() {
    return iterator(this, nullptr);
}

template <typename T>
inline void templateList<T>::printAll(templateList& tl) {
    for (auto it = tl.begin(); it != tl.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;
}
