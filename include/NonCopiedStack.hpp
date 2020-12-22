// Copyright 2020 Your Name <your_email>

#ifndef INCLUDE_NONCOPIEDSTACK_HPP_
#define INCLUDE_NONCOPIEDSTACK_HPP_

#include <iostream>
#include <type_traits>

#include "header.hpp"

template <typename T>
class NonCopiedStack : public BaseStack<T> {
  using BS = BaseStack<T>;

 public:
  void push(T &&value);
  T pop();
  template <typename... Args>
  void push_emplace(Args &&... value);
};

template <typename T>
void NonCopiedStack<T>::push(T &&value) {
  if (std::is_copy_constructible<T>::value ||
      std::is_copy_assignable<T>::value) {
    throw std::bad_typeid();
  }
  auto *newElement = new Element<T>{std::forward<T>(value), BS::pHead};
  BS::pHead = newElement;
}

template <typename T>
T NonCopiedStack<T>::pop() {
  if (!BS::pHead) {
    throw std::out_of_range("Empty Stack!!!");
  }
  auto *current = BS::pHead;
  BS::pHead = BS::pHead->pNext;
  T value = std::move(current->value);
  delete current;
  return value;
}

template <typename T>
template <typename... Args>
void NonCopiedStack<T>::push_emplace(Args &&... value) {
  if (std::is_copy_constructible<T>::value ||
      std::is_copy_assignable<T>::value) {
    throw std::bad_typeid();
  }
  auto *newElement = new Element<T>{{std::forward<Args>(value)...}, BS::pHead};
  BS::pHead = newElement;
}
#endif  // INCLUDE_NONCOPIEDSTACK_HPP_
