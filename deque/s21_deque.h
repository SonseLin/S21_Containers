#pragma once

#include <initializer_list>
#include <iostream>

namespace s21 {

template <class T>
class deque {  // класс дек (контейнер)
 public:
  using value_type = T;  // параметр шаблона T
  using reference = T &;  // определяет тип ссылки на элемент
  using const_reference = const T &;  // определяет тип константной ссылки
  using size_type = std::size_t;  // определяет тип размера контейнера
                                  // (стандартный тип — size_t)

  deque();  // конструктор по умолчанию, создает пустый дек
  ~deque();  // деструктор
  explicit deque(
      std::initializer_list<value_type> const
          &items);  // Конструктор списка инициализаторов, создает дек,
                    // инициализированный с помощью std::initializer_list
  deque(const deque &other);  // конструктор копирования
  deque(deque &&other);       // конструктор перемещения

  void push_front(const_reference data);  // добавляет элемент в заголовок
  void pop_front();  // удаляет первый элемент
  void push_back(const_reference data);  // добавляет элемент в конец
  void pop_back();  // удаляет последний элемент

  const_reference front() const;  // получает первый элемент
  const_reference back() const;  // получает последний элемент

  bool empty() const;  // проверяет, пуст ли контейнер
  size_type size() const;  // возвращает количество элементов в деке

  void swap(deque &other) noexcept;  // меняет местами содержимое двух дек
  void clear();  // очищает содержимое дека

  deque &operator=(const deque &other);  // оператор присваивания
  deque &operator=(
      deque &&other) noexcept;  // Перегрузка оператора присваивания
                                // для перемещения объекта

  T &operator[](const int index);  // Оператор доступа по индексу

 protected:
  struct Node {  // Структура, описывающая узел дека
    value_type value;
    Node *next = nullptr;
    Node *prev = nullptr;
    Node(value_type val = value_type(),
         Node *next_node = nullptr,  // Конструктор узла
         Node *prev_node = nullptr)
        : value(val), next(next_node), prev(prev_node) {}
  };

  struct nodeList {  //  Структура, описывающая список дека
    size_type size = 0;
    Node *head = nullptr;
    Node *tail = nullptr;
  };

  nodeList nList;
};
}  // namespace s21

#include "s21_deque.tpp"