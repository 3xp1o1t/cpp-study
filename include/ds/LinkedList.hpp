#pragma once
#include <iostream>

namespace ds {
  template <typename T>
  class LinkedList {
    private:
      struct Node {
        T data;
        Node* next;
        Node(const T& value) : data(value), next(nullptr) {}
      };

      Node* head;
      Node* tail;
      size_t ssize_t;

    public:
      LinkedList() : head(nullptr), tail(nullptr), ssize_t(0) {}
      ~LinkedList() {
        clear();
      }

      void push_back(const T& value) {
        Node* newNode = new Node(value);
        if(!head) {
          head = tail = newNode;
        }else {
          tail->next = newNode;
          tail = newNode;
        }
        ++ssize_t;
      }

      void push_front(const T& value) {
        Node* node = new Node(value);
        node->next = head;
        head = node;
        if(!tail) tail = node;
        ++ssize_t;
      }

      bool empty() const { return head == nullptr; }

      size_t size() const { return ssize_t;}

      void clear() {
        Node * cur = head;
        while(cur) {
          Node* next = cur->next;
          delete cur;
          cur = next;
        }
        head = tail = nullptr;
        ssize_t = 0;
      }

      void print() const {
        Node* cur = head;
        std::cout << "[";
        while(cur) {
          std::cout << cur->data;
          if (cur->next) std::cout << " -> ";
          cur = cur->next;
        }
        std::cout << "]\n";
      }
  };
}