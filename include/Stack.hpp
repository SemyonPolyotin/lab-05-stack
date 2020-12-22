// Copyright 2020 Your Name <your_email>

#ifndef INCLUDE_STACK_HPP_
#define INCLUDE_STACK_HPP_

#include "header.hpp"

template <typename T>
class Stack : public BaseStack<T> {
  using BS = BaseStack<T>;

 public:
  void push(const T &value);
  void pop();
};

template <typename T>
void Stack<T>::push(const T &value) {
  auto *newElement = new Element<T>{value, BS::pHead};
  BS::pHead = newElement;
}

template <typename T>
void Stack<T>::pop() {
  if (BS::pHead) {
    auto *current = BS::pHead;
    BS::pHead = BS::pHead->pNext;
    delete current;
  } else {
    throw std::out_of_range("Empty Stack!!!");
  }
}

#endif  // INCLUDE_STACK_HPP_
