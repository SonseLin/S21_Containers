#pragma once

#include "../binary_tree/s21_binary_tree.h"
#include "../vector/s21_vector.h"

namespace s21 {

template <class Key, class T>
class map : public BinaryTree<Key, T> {
 public:
  using key_type = Key;  // первый параметр шаблона (Ключ)
  using mapped_type = T;  // второй параметр шаблона (Значение)
  using value_type =
      std::pair<const key_type, mapped_type>;  // пара (ключ, значение)
  using reference = value_type &;  // ссылка на пару (ключ, значение)
  using const_reference =
      const value_type &;  // константная ссылка на пару (ключ, значение)
  using iterator =
      typename BinaryTree<Key, T>::iterator;  // итератор, определяет тип для
                                              // итерации по контейнеру
  using const_iterator =
      typename BinaryTree<Key,
                          T>::const_iterator;  // константный итератор,
                                               // определяет константный тип
                                               // для итерации по контейнеру
  using size_type =
      size_t;  // определяет тип размера контейнера (стандартный тип — size_t)
  map();  // конструктор по умолчанию, создает пустой map
  explicit map(
      std::initializer_list<value_type> const
          &items);  // конструктор с инициализацией, Конструктор списка
                    // инициализаторов, создает карту, инициализированную
                    // с помощью std::initializer_list
  map(const map &m);  // конструктор копирования
  map(map &&m);       // конструктор перемещения
  ~map();             // деструктор
  map operator=(
      map &&m);  // Перегрузка оператора присваивания для перемещения объекта
  T &at(const Key &key);  // доступ к указанному элементу с проверкой границ
  T &operator[](const Key &key);  // доступ или вставка указанного элемента
  iterator begin() const;  // возвращает итератор на начало
  iterator end() const;  // возвращает итератор на конец
  bool empty();          // проверяет, пуст ли контейнер
  size_type Size();  // возвращает количество элементов
  size_type
  max_size();  // возвращает максимально возможное количество элементов
  void clear();  // очищает содержимое
  std::pair<iterator, bool> insert(
      const value_type
          &value);  // вставляет узел и возвращает итератор, указывающий, где
                    // находится элемент в контейнере, и логическое значение,
                    // указывающее, произошла ли вставка
  std::pair<iterator, bool> insert(
      const Key &key,
      const T &obj);  // вставляет значение по ключу и возвращает итератор,
                      // указывающий, где находится элемент в контейнере, и
                      // логическое значение, указывающее, произошла ли вставка
  std::pair<iterator, bool> insert_or_assign(
      const Key &key,
      const T &obj);  // вставляет элемент или назначает текущему
                      // элементу, если ключ уже существует
  template <typename... Args>
  s21::vector<std::pair<iterator, bool>> insert_many(Args &&...args);
  void erase(iterator pos);  // стирает элемент в позиции pos
  void swap(map &other);     // меняет местами содержимое
  void merge(map &other);  // ращивает узлы из другого контейнера
  bool contains(const Key &key);  //проверяет, есть ли элемент с ключом,
                                  //эквивалентным ключу в контейнере
};
}  // namespace s21

#include "s21_map.tpp"
