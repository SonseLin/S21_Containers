#include <queue>

#include "test_s21_containers.h"
// Тесты для конструктора по умолчанию и методов empty и size
TEST(Queue_Constructor, Default) {
  s21::queue<int> q;
  EXPECT_EQ(q.size(), 0);  // Проверка, что размер очереди 0
  EXPECT_TRUE(q.empty());  // Проверка, что очередь пустая
}

// Тесты для конструктора со списком инициализации
TEST(Queue_Constructor, Initializer_List) {
  s21::queue<int> q{1, 2, 3};
  EXPECT_EQ(q.size(), 3);  // Проверка, что размер очереди 3
  EXPECT_FALSE(q.empty());  // Проверка, что очередь не пустая
  EXPECT_EQ(q.front(), 1);  // Проверка первого элемента
  EXPECT_EQ(q.back(), 3);  // Проверка последнего элемента
}

// Тесты для конструктора копирования
TEST(Queue_Constructor, Copy) {
  s21::queue<int> q1{1, 2, 3};
  s21::queue<int> q2(q1);
  EXPECT_EQ(q2.size(), 3);  // Проверка, что размер очереди 3
  EXPECT_EQ(q2.front(), 1);  // Проверка первого элемента
  EXPECT_EQ(q2.back(), 3);  // Проверка последнего элемента
}

// Тесты для конструктора перемещения
TEST(Queue_Constructor, Move) {
  s21::queue<int> q1{1, 2, 3};
  s21::queue<int> q2(std::move(q1));
  EXPECT_EQ(q2.size(), 3);  // Проверка, что размер очереди 3
  EXPECT_EQ(q2.front(), 1);  // Проверка первого элемента
  EXPECT_EQ(q2.back(), 3);  // Проверка последнего элемента
  EXPECT_TRUE(q1.empty());  // Проверка, что оригинальная очередь пустая
}

// Тесты для оператора присваивания
TEST(Queue_Constructor, Operator_eq) {
  s21::queue<int> q1{1, 2, 3};
  s21::queue<int> q2;
  q2 = q1;
  EXPECT_EQ(q2.size(), 3);  // Проверка, что размер очереди 3
  EXPECT_EQ(q2.front(), 1);  // Проверка первого элемента
  EXPECT_EQ(q2.back(), 3);  // Проверка последнего элемента
}

// Тесты для метода front
TEST(Queue_Element_Access, Front) {
  s21::queue<int> q{1, 2, 3};
  EXPECT_EQ(q.front(), 1);  // Проверка первого элемента
}

// Тесты для метода back
TEST(Queue_Element_Access, Back) {
  s21::queue<int> q{1, 2, 3};
  EXPECT_EQ(q.back(), 3);  // Проверка последнего элемента
}

// Тесты для метода push
TEST(Queue_Modifiers, Push) {
  s21::queue<int> q;
  q.push(1);
  q.push(2);
  q.push(3);
  EXPECT_EQ(q.size(), 3);  // Проверка, что размер очереди 3
  EXPECT_EQ(q.front(), 1);  // Проверка первого элемента
  EXPECT_EQ(q.back(), 3);  // Проверка последнего элемента
}

// Тесты для метода pop
TEST(Queue_Modifiers, Pop) {
  s21::queue<int> q{1, 2, 3};
  q.pop();
  EXPECT_EQ(q.size(), 2);  // Проверка, что размер очереди 2
  EXPECT_EQ(q.front(), 2);  // Проверка первого элемента
  q.pop();
  EXPECT_EQ(q.front(), 3);  // Проверка следующего элемента
}

// Тесты для метода swap
TEST(Queue_Modifiers, Swap) {
  s21::queue<int> q1{1, 2, 3};
  s21::queue<int> q2{4, 5, 6};
  q1.swap(q2);
  EXPECT_EQ(q1.front(), 4);  // Проверка, что первый элемент новой очереди
  EXPECT_EQ(q2.front(), 1);  // Проверка, что первый элемент новой очереди
  EXPECT_EQ(q1.size(), 3);  // Проверка, что размер очереди 3
}

// Тесты для конструктора копирования с использованием std::queue для сравнения
TEST(Queue_Constructor, Copy_With_StdQueue) {
  s21::queue<int> our_queue{1, 2, 3};
  s21::queue<int> our_copy(our_queue);
  std::queue<int> std_queue;
  std_queue.push(1);
  std_queue.push(2);
  std_queue.push(3);
  std::queue<int> std_copy(std_queue);
  EXPECT_EQ(our_copy.front(), std_copy.front());  // Проверка первого элемента
  EXPECT_EQ(our_copy.back(), std_copy.back());  // Проверка последнего элемента
}

// Тесты для перемещения очереди с использованием std::queue для сравнения
TEST(Queue_Constructor, Move_With_StdQueue) {
  s21::queue<int> our_queue{1, 2, 3};
  s21::queue<int> our_move(std::move(our_queue));
  std::queue<int> std_queue;
  std_queue.push(1);
  std_queue.push(2);
  std_queue.push(3);
  std::queue<int> std_move(std::move(std_queue));
  EXPECT_EQ(our_move.front(), std_move.front());  // Проверка первого элемента
  EXPECT_EQ(our_move.back(), std_move.back());  // Проверка последнего элемента
  EXPECT_TRUE(our_queue.empty());  // Проверка, что исходная очередь пустая
}

// Тесты для вставки нескольких элементов в конец очереди
TEST(Queue_Modifiers, InsertManyBack) {
  s21::queue<int> our_queue_int;
  our_queue_int.insert_many_back(1, 2, 3);
  EXPECT_EQ(our_queue_int.front(), 1);  // Проверка первого элемента
  EXPECT_EQ(our_queue_int.back(), 3);  // Проверка последнего элемента
}
