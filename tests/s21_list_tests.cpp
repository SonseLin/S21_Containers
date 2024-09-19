#include "test_s21_containers.h"

TEST(ListConstructor, Constructor) {
  s21::list<int> list1;
  s21::list<int> list2;
  EXPECT_TRUE(list1.empty());
}

TEST(ListConstructor, InitializedListConstructor) {
  s21::list<int> list1{1, 2, 3};
  s21::list<int> list2{1, 2, 3};
  EXPECT_TRUE(list1.front() == list2.front() && list2.back() == list1.back());
}

TEST(ListConstructor, MoveConstructor) {
  s21::list<int> original{1, 2, 3, 4, 5};
  s21::list<int> moved(std::move(original));  // Конструктор перемещения

  EXPECT_TRUE(moved.size() == 5);
  EXPECT_TRUE(original.empty());  // Исходный список должен быть пустым
  EXPECT_EQ(moved.front(), 1);
  EXPECT_EQ(moved.back(), 5);
}

TEST(ListMeasure, Equality) {
  s21::list<int> list1{1, 2, 3};
  s21::list<int> list2{1, 2, 3};
  s21::list<int> list3{4, 5, 6};

  EXPECT_TRUE(list1 == list2);
  EXPECT_FALSE(list1 == list3);
}

TEST(ListParams, Empty) {
  s21::list<int> list;

  EXPECT_TRUE(list.empty());

  list.push_back(1);
  EXPECT_FALSE(list.empty());

  list.pop_back();
  EXPECT_TRUE(list.empty());
}

TEST(ListParams, Size) {
  s21::list<int> list;

  EXPECT_EQ(list.size(), 0);

  list.push_back(1);
  EXPECT_EQ(list.size(), 1);

  list.push_back(2);
  EXPECT_EQ(list.size(), 2);

  list.pop_front();
  EXPECT_EQ(list.size(), 1);

  list.pop_back();
  EXPECT_EQ(list.size(), 0);
}

TEST(ListParams, MaxSize) {
  s21::list<int> list;

  EXPECT_GT(list.max_size(), 100000);

  s21::list<double> list2;
  EXPECT_EQ(list.max_size(), list2.max_size());
}

TEST(ListModify, Clear) {
  s21::list<int> list{1, 2, 3, 4, 5};

  EXPECT_FALSE(list.empty());
  EXPECT_EQ(list.size(), 5);

  list.clear();
  EXPECT_TRUE(list.empty());
  EXPECT_EQ(list.size(), 0);

  list.clear();
  EXPECT_TRUE(list.empty());
  EXPECT_EQ(list.size(), 0);
}

TEST(ListModify, Insert) {
  s21::list<int> list{1, 3, 4};

  auto it = list.begin();
  ++it;
  list.insert(it, 2);

  s21::list<int> expectedList{1, 2, 3, 4};
  EXPECT_TRUE(list == expectedList);

  list.insert(list.begin(), 0);
  s21::list<int> expectedList2{0, 1, 2, 3, 4};
  EXPECT_TRUE(list == expectedList2);

  list.insert(list.last(), 5);
  s21::list<int> expectedList3{0, 1, 2, 3, 4, 5};
  EXPECT_TRUE(list == expectedList3);
}

TEST(ListModify, Erase) {
  s21::list<int> list{1, 2, 3, 4, 5};

  auto it = list.begin();
  ++it;
  list.erase(it);
  s21::list<int> expectedList{1, 3, 4, 5};
  EXPECT_TRUE(list == expectedList);

  list.erase(list.begin());
  expectedList = s21::list<int>{3, 4, 5};
  EXPECT_TRUE(list == expectedList);

  list.erase(--list.last());
  expectedList = s21::list<int>{3, 4};
  EXPECT_TRUE(list == expectedList);

  list.erase(list.begin());
  list.erase(list.begin());
  EXPECT_TRUE(list.empty());
  EXPECT_EQ(list.size(), 0);
}

TEST(ListModify, PushBack) {
  s21::list<int> list;

  list.push_back(1);
  list.push_back(2);
  list.push_back(3);

  s21::list<int> expectedList{1, 2, 3};
  EXPECT_TRUE(list == expectedList);

  EXPECT_EQ(list.size(), 3);
}

TEST(ListModify, PushFront) {
  s21::list<int> list;

  list.push_front(3);
  list.push_front(2);
  list.push_front(1);

  s21::list<int> expectedList{1, 2, 3};
  EXPECT_TRUE(list == expectedList);

  // Проверяем размер списка
  EXPECT_EQ(list.size(), 3);
}

TEST(ListModify, PopBack) {
  s21::list<int> list{1, 2, 3, 4, 5};

  list.pop_back();
  list.pop_back();

  s21::list<int> expectedList{1, 2, 3};
  EXPECT_TRUE(list == expectedList);

  EXPECT_EQ(list.size(), 3);

  list.pop_back();
  list.pop_back();
  list.pop_back();

  EXPECT_TRUE(list.empty());
  EXPECT_EQ(list.size(), 0);
}

TEST(ListModify, PopFront) {
  s21::list<int> list{1, 2, 3, 4, 5};

  list.pop_front();
  list.pop_front();

  s21::list<int> expectedList{3, 4, 5};
  EXPECT_TRUE(list == expectedList);

  EXPECT_EQ(list.size(), 3);

  list.pop_front();
  list.pop_front();
  list.pop_front();

  // Ожидаемый список пуст
  EXPECT_TRUE(list.empty());
  EXPECT_EQ(list.size(), 0);
}

TEST(ListModify, Swap) {
  s21::list<int> list1{1, 2, 3};
  s21::list<int> list2{4, 5, 6};

  list1.swap(list2);

  s21::list<int> expectedList1{4, 5, 6};
  EXPECT_TRUE(list1 == expectedList1);

  s21::list<int> expectedList2{1, 2, 3};
  EXPECT_TRUE(list2 == expectedList2);
}

TEST(ListModify, Merge) {
  s21::list<int> list1{1, 3, 5};
  s21::list<int> list2{2, 4, 6};

  list1.merge(list2);

  s21::list<int> expectedList{1, 3, 5, 2, 4, 6};
  EXPECT_TRUE(list1 == expectedList);

  EXPECT_TRUE(list2.empty());
  EXPECT_EQ(list2.size(), 0);
}

TEST(ListModify, MergeEmpty) {
  s21::list<int> list1;
  s21::list<int> list2;

  list1.merge(list2);

  EXPECT_TRUE(list1.empty());
}

TEST(ListModify, Splice) {
  s21::list<int> list1{1, 2, 3, 4, 5};
  s21::list<int> list2{10, 20, 30};

  list1.splice(list1.cend(), list2);

  s21::list<int> expectedList{1, 2, 3, 4, 5, 10, 20, 30};
  EXPECT_TRUE(list1 == expectedList);

  EXPECT_TRUE(list2.empty());
  EXPECT_EQ(list2.size(), 0);
}

TEST(ListModify, Reverse) {
  s21::list<int> list{1, 2, 3, 4, 5};
  list.reverse();
  s21::list<int> expectedList{5, 4, 3, 2, 1};
  EXPECT_FALSE(list == expectedList);
  EXPECT_EQ(list.size(), 5);
  EXPECT_TRUE(list.back() == expectedList.front());
}
// вызывает дедлок фикс нужен
// fixed
TEST(ListModify, Unique) {
  s21::list<int> list{1, 1, 2, 2, 3, 3, 3, 4, 4, 4, 4};
  list.unique();
  s21::list<int> expectedList{1, 2, 3, 4};
  EXPECT_TRUE(list == expectedList);
  EXPECT_EQ(list.size(), 4);
}

TEST(ListModify, UniqueEmpty) {
  s21::list<int> my_list;
  EXPECT_TRUE(my_list.size() == 0);
}

TEST(ListModify, SortEmptyList) {
  s21::list<int> l;
  l.sort();
  EXPECT_EQ(l.size(), 0);
}

TEST(ListModify, Sort) {
  s21::list<int> l;
  l.push_back(1);
  l.sort();
  EXPECT_EQ(l.front(), 1);
  EXPECT_EQ(l.size(), 1);
}

TEST(ListTest, InsertMany) {
  s21::list<int> list{1, 2, 3};

  // Вставка множества элементов в середину списка
  auto it = list.cbegin();
  ++it;  // Перемещение итератора на вторую позицию

  list.insert_many(it, 4);  // Вставка элементов 4, 5, 6

  s21::list<int> expectedList{1, 4, 2, 3};

  // Проверка на равенство списков
  EXPECT_TRUE(list == expectedList);

  // Проверка размера списка
  EXPECT_EQ(list.size(), 4);
}

TEST(ListTest, InsertManyBack) {
  s21::list<int> list{1, 2, 3};

  // Вставка множества элементов в конец списка
  list.insert_many_back(4, 5, 6);  // Вставка элементов 4, 5, 6

  s21::list<int> expectedList{1, 2, 3, 4, 5, 6};
  EXPECT_TRUE(list == expectedList);
  EXPECT_EQ(list.size(), 6);
}

TEST(ListTest, InsertManyFront) {
  s21::list<int> list{1, 2, 3};

  // Вставка множества элементов в начало списка
  list.insert_many_front(4, 5, 6);  // Вставка элементов 4, 5, 6

  s21::list<int> expectedList{6, 5, 4, 1, 2, 3};
  EXPECT_TRUE(list == expectedList);
  EXPECT_EQ(list.size(), 6);
}