#pragma once

#include "../binary_tree/s21_binary_tree.h"
#include "../vector/s21_vector.h"

namespace s21 {

template <class Key>
class set : public BinaryTree<Key, Key> {  // Класс-контейнер для хранения
                                           // уникальных значений
 public:
  using key_type = Key;            // Тип ключа
  using value_type = Key;          // Тип значений
  using reference = value_type &;  // Тип ссылки на значение
  using const_reference =
      const value_type &;  // Тип ссылки на константное значение
  using iterator = typename BinaryTree<Key, Key>::iterator;  // Тип итератора
  using const_iterator =
      typename BinaryTree<Key,
                          Key>::const_iterator;  // Тип константного итератора
  using size_type = size_t;  // Тип размера
  set();  // Конструктор по умолчанию, пустой контейнер (пустое дерево)
  explicit set(std::initializer_list<value_type> const
                   &items);  // Конструктор с инициализацией (список)
  set(const set &s);  // Конструктор копирования
  set(set &&s);       // Конструктор перемещения
  ~set() = default;   // Деструктор
  set operator=(set &&s);  // Оператор присваивания перемещением
  iterator begin() const;  // Возвращение итератора begin_i (начало дерева)
  iterator end() const;  // Возвращение итератора end_i (конец дерева)
  bool empty();          // Проверка на пустоту
  size_type Size();      // Возвращение размера
  size_type max_size();  // Возвращение максимального размера (в байтах)
  void clear();          // Очистка дерева
  std::pair<iterator, bool> insert(
      const value_type &value);  // Вставка уникального значения
  template <typename... Args>  // Вставка нескольких значений
  s21::vector<std::pair<iterator, bool>> insert_many(
      Args &&...args);  // Вставка нескольких значений (вектор)
  void erase(iterator pos);  // Удаление узла по итератору
  void swap(set &other);     // Обмен значений
  void merge(set &other);    // Слияние двух деревьев
  bool contains(const Key &key);  // Поиск уникального значения (по ключу)
  iterator find(const Key &key);  // Поиск уникального значения
};
}  // namespace s21

#include "s21_set.tpp"