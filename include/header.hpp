// Copyright 2020 Your Name <your_email>

#ifndef INCLUDE_HEADER_HPP_
#define INCLUDE_HEADER_HPP_

#include <stdexcept>
#include <utility>

template <class T>
struct Element {
  T value;
  Element<T> *pNext = nullptr;
};
template <typename T>
class BaseStack {
 public:
  BaseStack() = default;
  BaseStack(BaseStack &&st) noexcept = default;
  auto operator=(BaseStack &&st) noexcept -> BaseStack & = default;
  BaseStack(const BaseStack &st) = delete;
  auto operator=(const BaseStack &st) -> BaseStack & = delete;
  void push(T &&value);
  const T &head() const;
  ~BaseStack();

 protected:
  Element<T> *pHead = nullptr;
};

template <typename T>
void BaseStack<T>::push(T &&value) {
  auto *newElement = new Element<T>{std::forward<T>(value), pHead};
  pHead = newElement;
}

template <typename T>
const T &BaseStack<T>::head() const {
  if (!pHead) {
    throw std::out_of_range("Empty Stack!!!");
  }
  return pHead->value;
}

template <typename T>
BaseStack<T>::~BaseStack() {
  while (pHead) {
    auto *current = pHead;
    pHead = pHead->pNext;
    delete current;
  }
}

#endif  // INCLUDE_HEADER_HPP_
