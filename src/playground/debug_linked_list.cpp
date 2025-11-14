#include <iostream>
#include "ds/LinkedList.hpp"

int main() {
  std::cout << "=== Linked List Data Structure - Playground ===\n\n";
  ds::LinkedList<int> list;

  list.push_back(10);
  list.push_back(20);
  list.push_front(5);

  std::cout << "Linked List contents: ";
  list.print();

  std::cout << "Size: " << list.size() << "\n";
  return 0;
}