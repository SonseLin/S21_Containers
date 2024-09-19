#pragma once

#include "../deque/s21_deque.h"

namespace s21 {
template <class T,
          class Container = deque<T>>  // шаблон класса stack (контейнер)
class stack {
 public:
  using value_type = T;  // параметр шаблона T (тип данных)
  using reference = T &;  // определяет тип ссылки на элемент
  using const_reference =
      const T &;  // определяет тип ссылки на константный элемент
  using size_type =
      std::size_t;  // определяет тип размера контейнера (кол-во элементов)

  stack();  // конструктор по умолчанию, создает пустой стек
  explicit stack(
      std::initializer_list<value_type> const
          &items);  // Конструктор списка инициализаторов, создает стек,
                    // инициализированный с помощью std::initializer_list
  stack(const stack &other);  // конструктор копий
  stack(stack &&other);       // конструктор перемещения
  ~stack() = default;         // деструктор

  stack &operator=(const stack &other);  // Перегрузка оператора присваивания
                                         // для перемещения объекта
  stack &operator=(
      stack &&other) noexcept;  // Перегрузка оператора присваивания
                                // для перемещения объекта

  const_reference top() const;  // получает доступ к верхнему элементу
  bool empty() const;  // проверяет, пуст ли контейнер
  size_type size() const;  // возвращает количество элементов
  void push(const_reference value);  // вставляет элемент вверху
  void pop();  // удаляет верхний элемент
  void swap(stack &other) noexcept;  // меняет местами содержимое

  template <class... Args>
  void insert_many_back(Args &&...args);

  T &operator[](const int index);  // возвращает ссылку на элемент по индексу

 private:
  Container container;
};
}  // namespace s21

#include "s21_stack.tpp"