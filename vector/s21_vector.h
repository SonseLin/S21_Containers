#pragma once

#include <initializer_list>
#include <iostream>

namespace s21 {

template <typename T>
class vector {
 public:
  class VectorIterator;
  class VectorConstIterator;

  /*Vector Member type*/
  using value_type = T;
  using size_type = size_t;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = vector<T>::VectorIterator;
  using const_iterator = vector<T>::VectorConstIterator;

 private:
  size_type _size;
  size_type _capacity;
  value_type *_vectorPtr;

 public:
  /*Vector Member functions*/
  vector();
  explicit vector(const size_type size);
  explicit vector(std::initializer_list<value_type> const &items);
  explicit vector(const vector<value_type> &v);
  explicit vector(vector<value_type> &&v);
  ~vector();
  vector &operator=(vector<value_type> &&v);

  /*Vector Element access*/
  reference at(size_type pos);
  reference operator[](size_type pos);
  const_reference front();
  const_reference back();
  value_type *data();

  /*Vector Iterators*/
  iterator begin();
  iterator end();
  const_iterator cbegin();
  const_iterator cend();

  /*Vector Capacity*/
  bool empty();
  size_type size();
  size_type max_size();
  void reserve(size_type size);
  size_type capacity();
  void shrink_to_fit();

  /*Vector Modifiers*/
  void clear();
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void swap(vector &other);

  /*insert_many Method*/
  template <typename... Args>
  iterator insert_many(const_iterator c_pos, Args &&...args);
  template <typename... Args>
  void insert_many_back(Args &&...args);
};

template <typename T>
class vector<T>::VectorIterator {
 private:
  T *_ptr;

 public:
  VectorIterator() : _ptr(nullptr) {}
  explicit VectorIterator(T *ptr) : _ptr(ptr) {}
  ~VectorIterator() = default;

  VectorIterator &operator++();
  VectorIterator &operator--();
  VectorIterator operator+(int n) const;
  VectorIterator operator-(int n) const;
  ptrdiff_t operator-(const VectorIterator &vi) const;
  bool operator>(const VectorIterator &vi) const;
  bool operator<(const VectorIterator &vi) const;
  bool operator<=(const VectorIterator &vi) const;
  bool operator>=(const VectorIterator &vi) const;
  bool operator==(const VectorIterator &vi);
  bool operator!=(const VectorIterator &vi);
  reference operator*();
};

template <typename T>
class vector<T>::VectorConstIterator : public VectorIterator {
 private:
  const T *_constPtr;

 public:
  VectorConstIterator() : _constPtr(nullptr) {}
  explicit VectorConstIterator(const T *ptr) : _constPtr(ptr) {}
  ~VectorConstIterator() = default;

  VectorConstIterator &operator++();
  VectorConstIterator &operator--();
  VectorConstIterator operator-(int n) const;
  VectorConstIterator operator+(int n) const;

  ptrdiff_t operator-(const VectorConstIterator &c_vi) const;
  bool operator==(const VectorConstIterator &vi);
  bool operator!=(const VectorConstIterator &vi);
  const_reference operator*() const;
};

}  // namespace s21

#include "s21_vector.tpp"