#pragma once

#include <initializer_list>
#include <iostream>

namespace s21 {
template <typename T, size_t N>
class array {
  /*Array Member type*/
  using value_type = T;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = value_type *;
  using const_iterator = const value_type *;
  using size_type = size_t;

 private:
  size_type _size = N;
  value_type *_arrayPtr;

 public:
  /*Array Member functions*/
  array();
  explicit array(std::initializer_list<value_type> const &items);
  explicit array(const array<value_type, N> &a);
  explicit array(array<value_type, N> &&a);
  ~array();
  array<value_type, N> &operator=(array<value_type, N> &&a);

  /*Array Element access*/
  reference at(size_type pos);
  reference operator[](size_type pos);
  const_reference front();
  const_reference back();
  iterator data();

  /*Array Iterators*/
  iterator begin();
  iterator end();

  /*Array Capacity*/
  bool empty();
  size_type size();
  size_type max_size();

  /*Array Modifiers*/
  void swap(array<value_type, N> &other);
  void fill(const_reference value);
};
}  // namespace s21

#include "s21_array.tpp"
