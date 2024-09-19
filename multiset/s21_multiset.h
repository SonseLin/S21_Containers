#pragma once

#include "../binary_tree/s21_binary_tree.h"
#include "../vector/s21_vector.h"

namespace s21 {

template <class Key>
class multiset : public BinaryTree<Key, Key> {
 public:
  using key_type = Key;  // первый параметр шаблона (Ключ)
  using value_type = Key;  // тип значения (само значение является ключом)
  using reference = value_type &;  // определяет тип ссылки на элемент
  using const_reference =
      const value_type &;  // определяет тип константной ссылки
  using iterator =
      typename BinaryTree<Key, Key>::iterator;  //  определяет тип для итерации
                                                //  по контейнеру
  using const_iterator = typename BinaryTree<Key, Key>::
      const_iterator;  // определяет константный тип для итерации по контейнеру
  using size_type =
      size_t;  // определяет тип размера контейнера (стандартный тип — size_t)
  multiset();  // конструктор по умолчанию, создает пустой набор
  explicit multiset(
      std::initializer_list<value_type> const
          &items);  // онструктор списка инициализаторов, создает набор,
                    // инициализированный с помощью std::initializer_list
  multiset(const multiset &ms);  // конструктор копий
  multiset(multiset &&ms);  // конструктор перемещения
  ~multiset();              // деструктор
  multiset operator=(multiset &&ms);  // Перегрузка оператора присваивания для
                                      // перемещения объекта
  iterator begin() const;  // возвращает итератор на начало
  iterator end() const;  // возвращает итератор на конец
  bool empty();          // проверяет, пуст ли контейнер
  size_type size();  // возвращает количество элементов
  size_type
  max_size();  // возвращает максимально возможное количество элементов
  size_type count(
      const Key &key);  // Подсчет количества узлов с заданным ключом
  void clear();         // очищает содержимое
  iterator insert(const value_type &value);  // вставляет элемент в контейнер
  template <typename... Args>  // вставляет несколько элементов в контейнер
  s21::vector<std::pair<iterator, bool>> insert_many(
      Args &&...args);  // вставляет несколько элементов в контейнер
  void erase(iterator pos);  // удаляет элемент с заданным ключом
  void swap(multiset &other);  // Обмен значений двух наборов
  void merge(multiset &other);  // Слияние двух наборов
  bool contains(const Key &key);  // Проверка наличия узла с заданным ключом
  iterator find(const Key &key);  // Поиск узла с заданным ключом
  std::pair<iterator, iterator> equal_range(
      const Key &key);  // проверка наличия узла с заданным ключом
  iterator lower_bound(const Key &key);  // должен находить первый элемент,
                                         // который больше или равен ключу
  iterator upper_bound(const Key &key);  // должен находить первый элемент,
                                         // который строго больше ключа
};
}  // namespace s21

#include "s21_multiset.tpp"
