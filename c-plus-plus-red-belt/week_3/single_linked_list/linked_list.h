#pragma once

#include <vector>

template <typename T>
class LinkedList {
public:
    struct Node {
        T value;
        Node* next = nullptr;
    };
    ~LinkedList();
    void PushFront(const T& value);
    void InsertAfter(Node* node, const T& value);
    void RemoveAfter(Node* node);
    void PopFront();
    Node* GetHead() { return head; }
    const Node* GetHead() const { return head; }
private:
    Node* head = nullptr;
};

template <typename T>
LinkedList<T>::~LinkedList() {
    while (head != nullptr) {
        Node* curr = head;
        head = head->next;
        delete curr;;
    }
}

template<typename T>
void LinkedList<T>::PushFront(const T& value) {
    Node* new_head = new Node;
    new_head->value = value;
    new_head->next = head;
    head = new_head;
}

template<typename T>
void LinkedList<T>::InsertAfter(Node* node, const T& value) {
    if (head == nullptr) {
        PushFront(value);
    }
    else if (node != nullptr) {
        Node* new_node = new Node;
        new_node->value = value;
        new_node->next = node->next;
        node->next = new_node;
    }
}

template<typename T>
void LinkedList<T>::RemoveAfter(Node* node) {
    if (head == nullptr) { return; }
    if (node == nullptr) {
        PopFront();
    }
    else {
        if (node->next == nullptr) { return; }
        Node* next_node = node->next;
        node->next = next_node->next;
        delete next_node;
    }
}

template<typename T>
void LinkedList<T>::PopFront() {
    if (head == nullptr) { return; }
    if (head->next == nullptr) {
        delete head;
        head = nullptr;
    }
    else {
        Node* front = head;
        head = head->next;
        delete front;
    }
}

template <typename T>
std::vector<T> ToVector(const LinkedList<T>& list) {
    std::vector<T> result;
    for (auto node = list.GetHead(); node; node = node->next) {
        result.push_back(node->value);
    }
    return result;
}
