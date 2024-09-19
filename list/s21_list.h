#pragma once

#include <initializer_list>
#include <iostream>
namespace s21 {

template <typename T>
class list {
 public:
  class ListIterator;
  class ListConstIterator;
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = std::size_t;
  using iterator = ListIterator;
  using const_iterator = ListConstIterator;

 private:
  struct Node {
    value_type value;
    Node *prev;
    Node *next;
    explicit Node(const value_type &v)
        : value(v), prev(nullptr), next(nullptr) {}
  };

  Node *head_;
  Node *tail_;
  Node *last_;
  size_type size_;

 public:
  // Constructors
  list();
  explicit list(size_type n);
  explicit list(std::initializer_list<value_type> const &items);
  list(const list &other);
  list(list &&l) noexcept;
  ~list();

  list &operator=(list &&l) noexcept;
  bool operator==(list &other);

  // Pop functions
  void pop_front();
  void pop_back();
  void push_front(const_reference value);
  void push_back(const_reference value);

  // Capacity functions
  bool empty() const;
  size_type size() const;
  size_type max_size() const;

  // list access
  const_reference front() const;
  const_reference back() const;
  iterator begin();
  const_iterator cbegin() const;
  iterator last();
  const_iterator clast() const;
  iterator end();
  const_iterator cend() const;

  iterator insert(iterator pos, const_reference value);

  void erase(iterator pos);

  // Utility functions
  void clear();
  void swap(list &other);
  bool compare(const list &other) const;
  void merge(list &other);
  void splice(const_iterator pos, list &other);
  void unique();
  void sort();
  void reverse();

  template <class... Args>
  iterator insert_many(const_iterator pos, Args &&...args);
  template <class... Args>
  void insert_many_back(Args &&...args);
  template <class... Args>
  void insert_many_front(Args &&...args);

 private:
  void link_list();
};

template <typename T>
class list<T>::ListIterator {
 public:
  ListIterator(Node *p = nullptr) : ptr(p) {}

  reference operator*() const;
  ListIterator &operator++();
  ListIterator operator++(int);
  ListIterator &operator--();
  ListIterator operator--(int);
  ListIterator operator+(const size_type value);
  ListIterator operator-(const size_type value);
  bool operator==(const ListIterator &other) const;

  bool operator!=(const ListIterator &other) const;

 private:
  Node *ptr;
  friend class list<T>;
};

template <typename T>
class list<T>::ListConstIterator : public ListIterator {
 public:
  ListConstIterator(Node *p = nullptr) : ListIterator(p) {}
  explicit ListConstIterator(const ListIterator &it);
  const_reference operator*() const;
};

}  // namespace s21

#include "s21_list.tpp"
