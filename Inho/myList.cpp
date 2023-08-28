#include "myList.h"

#include <iostream>

using std::cout;
using std::endl;

myList::~myList() {
    Node* now = this->head;
    for (int i = 0; i < curCount; i++) {
        Node* next = now->next;
        delete now;
        now = next;
    }
}

void myList::push_back(int data) {
    // data를 바로 집어넣는 생성자 호출로 생성
    Node* newNode = new Node(data);
    // 첫 노드인지 구분
    // 노드 연결
    if (curCount == 0) {
        this->head = newNode;
        this->tail = newNode;
    } else {
        this->tail->next = newNode;
        newNode->prev = this->tail;
        this->tail = newNode;
    }

    // 카운트 증가
    curCount++;
}

void myList::push_front(int data) {
    // data를 바로 집어넣는 생성자 호출로 생성
    Node* newNode = new Node(data);
    // 첫 노드인지 구분
    // 노드 연결
    if (curCount == 0) {
        this->head = newNode;
        this->tail = newNode;
    } else {
        newNode->next = this->head;
        this->head->prev = newNode;
        this->head = newNode;
    }

    // 카운트 증가
    curCount++;
}

myList::iterator myList::erase(const iterator& _it) {
    if (this == _it.owner && _it.idx >= 0) {
        Node* deleteNode = _it.node;
        if (this->begin() == _it) {
            head = deleteNode->next;
            deleteNode->next->prev = head;

        } else if (_it.idx == this->curCount - 1) {
            tail = deleteNode->prev;
            deleteNode->prev->next = tail;
        } else {
            deleteNode->prev->next = deleteNode->next;
            deleteNode->next->prev = deleteNode->prev;
        }

        delete deleteNode;
        curCount--;
        return iterator(_it.owner, _it.idx);
    } else {
        assert(nullptr);
    }
}

myList::iterator myList::begin() { return iterator(this, 0); }

myList::iterator myList::end() { return iterator(this, -2); }

void myList::printAll() {
    Node* node = head;
    for (int i = 0; i < curCount; i++) {
        Node* next = node->next;
        cout << node->data << " ";
        node = next;
    }
    cout << endl;
}

void myList::printNode(iterator& _it) {
    if (_it.idx < 0) {
        return;
    }
    cout << _it.node->data << endl;
}
