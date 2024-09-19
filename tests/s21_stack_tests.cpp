#include "test_s21_containers.h"
// Конструктор по умолчанию
TEST(Stack_Constructor, Default) {
  s21::stack<int> int_s;
  s21::stack<double> double_s;
  EXPECT_TRUE(int_s.empty());
  EXPECT_TRUE(double_s.empty());
}

// Инициализация списка
TEST(Stack_Constructor, InitializerList) {
  s21::stack<int> int_s{1, 2, 3, 4, 5};
  EXPECT_EQ(int_s.size(), 5);
  EXPECT_FALSE(int_s.empty());
}

// Конструктор копирования
TEST(Stack_Constructor, Copy) {
  s21::stack<int> int_s1{1, 2, 3, 4, 5};
  s21::stack<int> int_s2(int_s1);
  EXPECT_FALSE(int_s2.empty());
}

// Конструктор перемещения
TEST(Stack_Constructor, Move) {
  s21::stack<int> int_s1{1, 2, 3, 4, 5};
  s21::stack<int> int_s2(std::move(int_s1));
  EXPECT_FALSE(int_s2.empty());
  EXPECT_TRUE(int_s1.empty());
}

// Оператор присваивания перемещением
TEST(Stack_Operator, MoveAssign) {
  s21::stack<int> int_s1{1, 2, 3, 4, 5};
  s21::stack<int> int_s2;
  int_s2 = std::move(int_s1);
  EXPECT_EQ(int_s2.size(), 5);
  EXPECT_TRUE(int_s1.empty());
}

// Доступ к верхнему элементу
TEST(Stack_Element_Access, Top) {
  s21::stack<int> int_s{1, 2, 3, 4, 5};
  EXPECT_EQ(int_s.top(), 5);
}

// Пустой стек при доступе к верхнему элементу
TEST(Stack_Element_Access, TopEmpty) {
  s21::stack<int> int_s;
  EXPECT_THROW(int_s.top(), std::out_of_range);
}

// Проверка пустоты стека
TEST(Stack_Capacity, Empty) {
  s21::stack<int> int_s1{1, 2, 3, 4, 5};
  s21::stack<int> int_s2;
  EXPECT_FALSE(int_s1.empty());
  EXPECT_TRUE(int_s2.empty());
}

// Проверка размера стека
TEST(Stack_Capacity, Size) {
  s21::stack<int> int_s1{1, 2, 3, 4, 5};
  s21::stack<int> int_s2;
  EXPECT_EQ(int_s1.size(), 5);
  EXPECT_EQ(int_s2.size(), 0);
}

// Добавление элемента в стек
TEST(Stack_Modifiers, Push) {
  s21::stack<int> int_s{1, 2, 3, 4, 5};
  int_s.push(6);
  EXPECT_EQ(int_s.size(), 6);
  EXPECT_EQ(int_s.top(), 6);
}

// Добавление элемента в пустой стек
TEST(Stack_Modifiers, PushEmpty) {
  s21::stack<int> int_s;
  int_s.push(1);
  EXPECT_FALSE(int_s.empty());
  EXPECT_EQ(int_s.size(), 1);
}

// Удаление верхнего элемента
TEST(Stack_Modifiers, Pop) {
  s21::stack<int> int_s{1, 2, 3, 4, 5};
  int_s.pop();
  EXPECT_EQ(int_s.top(), 4);
}

// Удаление элемента из пустого стека
TEST(Stack_Modifiers, PopEmpty) {
  s21::stack<int> int_s;
  EXPECT_THROW(int_s.pop(), std::out_of_range);
}

// Обмен содержимого стеков
TEST(Stack_Modifiers, Swap) {
  s21::stack<int> int_s1{1, 2, 3, 4, 5};
  s21::stack<int> int_s2;
  EXPECT_FALSE(int_s1.empty());
  EXPECT_TRUE(int_s2.empty());
  int_s1.swap(int_s2);
  EXPECT_TRUE(int_s1.empty());
  EXPECT_FALSE(int_s2.empty());
}

// Вставка нескольких элементов
TEST(Stack_Modifiers, InsertMany) {
  s21::stack<int> int_s{1, 2, 3, 4, 5};
  int_s.insert_many_back(4, 5, 6, 7, 8);
  EXPECT_EQ(int_s.size(), 10);
}
