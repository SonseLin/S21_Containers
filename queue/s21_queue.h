#pragma once

#include "../deque/s21_deque.h"
#include "../vector/s21_vector.h"

namespace s21 {
template <class T, class Container = deque<T>>
class queue {
 public:
  using value_type = T;  // Тип данных в контейнере (параметр шаблона T)
  using reference = T &;  // определяет тип ссылки на элемент в контейнере
  using const_reference =
      const T &;  // определяет тип ссылки на константный элемент
  using size_type = std::size_t;  // определяет тип размера контейнера
                                  // (стандартный тип — size_t)

  queue();  // конструктор по умолчанию, создает пустую очередь
  explicit queue(
      std::initializer_list<value_type> const
          &items);  // Конструктор списка инициализаторов, создает очередь,
                    // инициализированную с помощью std::initializer_list
  queue(const queue &other);  // конструктор копий
  queue(queue &&other);       // конструктор перемещения
  ~queue() = default;         // деструктор

  queue &operator=(const queue &other);  // Перегрузка оператора присваивания
                                         // для перемещения объекта
  queue &operator=(
      queue &&other) noexcept;  // Перегрузка оператора присваивания
                                // для перемещения объекта

  const_reference front()
      const;  // Возвращает ссылку на первый элемент в очереди
  const_reference back()
      const;  // Возвращает ссылку на последний элемент в очереди
  bool empty() const;  // проверяет, пуст ли контейнер
  size_type size() const;  // возвращает количество элементов в очереди
  void push(const_reference value);  // вставляет элемент в конец очереди
  void pop();  // удаляет первый элемент из очереди

  void swap(queue &other) noexcept;  // меняет местами содержимое двух очередей

  template <class... Args>
  void insert_many_back(Args &&...args);  // добавляет элементы в конец очереди
                                          // по одному (перегруженная версия)

  T &operator[](const int index);  // возвращает ссылку на элемент по индексу

 private:
  Container container;
};
}  // namespace s21

#include "s21_queue.tpp"
