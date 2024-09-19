#pragma once

#include <initializer_list>
#include <iostream>
#include <limits>

namespace s21 {
template <class K, class T>  // Класс бинарного дерева
class BinaryTree {  // Класс-контейнер для хранения уникальных значений
 public:
  struct Node {
    Node *left, *right,
        *parent;  // Указатели на левый, правый и родительский узлы
    K key;        // Ключ узла
    T value;      // Значение узла
    Node(K _key, T _value,
         Node *_parent =
             nullptr);  // Создание узла дерева с ключом _key и значением _value
    ~Node();            // Деструктор
  };
  class Iterator {  // Класс итератора
   public:
    Node *ptr;   // Указатель на текущий узел
    Iterator();  // Конструктор по умолчанию
    explicit Iterator(
        Node *_ptr);  // Конструктор с параметром _ptr (указатель на узел)
    Iterator &operator++();  // Перейти к следующему узлу
    Iterator operator++(int);  // Постфиксный инкремент
    Iterator operator--(int);  // Постфиксный декремент
    Iterator &operator--();  // Перейти к предыдущему узлу
    bool operator==(Iterator other) const;  // Сравнение итераторов
    bool operator!=(Iterator other) const;  // Сравнение итераторов
    Node *operator->() const;  // Указатель на текущий узел
  };
  using key_type = K;     // Тип ключа
  using mapped_type = T;  // Тип значений
  using value_type =
      std::pair<const key_type, mapped_type>;  // Тип пары ключ-значение
  using reference = value_type &;              // Тип ссылки
  using const_reference = const value_type &;  // Тип константной ссылки
  using iterator = Iterator;                   // Тип итератора
  using const_iterator = const Iterator;  // Тип константного итератора
  using size_type = size_t;  // Тип размера

  BinaryTree();  // Конструктор по умолчанию
  explicit BinaryTree(std::initializer_list<value_type> const
                          &items);  // Конструктор с инициализацией списка items
  BinaryTree(const BinaryTree &other);  // Конструктор копирования
  BinaryTree(BinaryTree &&other);  // Конструктор перемещения
  ~BinaryTree();                   // Деструктор

  BinaryTree operator=(
      BinaryTree &&other);  // Оператор присваивания перемещением
  iterator begin() const;  // Итератор на первый узел
  iterator end() const;    // Итератор на последний узел
  size_type Size();        // Размер дерева
  size_type max_size();  // Максимальный размер дерева (в байтах)
  bool empty();  // Проверка на пустоту
  void clear();  // Очистка дерева

 protected:
  std::pair<iterator, bool> insert(
      const value_type &value);  // Вставка узла с заданным ключом и значением
                                 // в бинарное дерево
  std::pair<iterator, bool> insert(const K &key, const T &obj);
  std::pair<iterator, bool> insert_or_assign(const K &key, const T &obj);
  iterator insert(
      const K &key);  // Вставка узла с заданным ключом в бинарное дерево
  void erase(
      iterator pos);  // Удаление узла с заданным ключом из бинарного дерева
  void swap(BinaryTree &other);  // Обмен значений двух деревьев
  void merge(BinaryTree &other);  // Слияние двух деревьев
  bool contains(
      const K &key);  // Поиск узла с заданным ключом в бинарном дереве
  size_type count(const K &key);  // Подсчет количества узлов с заданным ключом
  iterator find(
      const K &key);  // Поиск узла с заданным ключом в бинарном дереве

  std::pair<iterator, iterator> equal_range(
      const K &key);  // сравнение итераторов
  iterator lower_bound(const K &key);  // должен находить первый элемент,
                                       // который больше или равен ключу
  iterator upper_bound(const K &key);  // должен находить первый элемент,
                                       // который строго больше ключа
  iterator root, iter, begin_i, end_i;  // итераторы
  T &at(const K &key);  // получение значения по ключу
  T &operator[](const K &key);  // получение значения по ключу

 private:
  size_type size;   // Размер дерева
  Node *null_node;  // Указатель на нулевой узел
  void assign(const BinaryTree &other);  // Копирование дерева
  bool contains(
      Node *root,
      const K &key);  // Поиск узла с заданным ключом в бинарном дереве
  void insert(Node *iter, Node *_node);  // Вставка узла с заданным ключом и
                                         // значением в бинарное дерево
  Node *insert(Node *iter, const K &key,
               const T &value);  // Вставка узла с заданным ключом и значением в
                                 // бинарное дерево
  iterator set_begin();          // Итератор на первый узел
  iterator set_end();  // Итератор на последний узел
  Node *find(Node *root, const K &key);  // Поиск узла с заданным ключом
};
}  // namespace s21

#include "s21_binary_tree.tpp"