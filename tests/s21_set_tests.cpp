#include "test_s21_containers.h"

// Конструктор
TEST(SetConstructor, NoArg) {
  s21::set<int> _set;
  EXPECT_TRUE(_set.empty());
}

TEST(SetConstructor, InitializerList) {
  s21::set<int> _set({15, 7, 42, 3});
  EXPECT_FALSE(_set.empty());
}

TEST(SetConstructor, Copy) {
  s21::set<int> _set({15, 7, 42, 3});
  s21::set<int> set_copy(_set);
  auto j = set_copy.begin();
  for (auto i = _set.begin(); i != _set.end(); ++i) {
    EXPECT_EQ(i->key, j->key);
    ++j;
  }
}

TEST(SetConstructor, Move) {
  s21::set<int> _set({15, 7, 42, 3});
  s21::set<int> set_copy(_set);
  s21::set<int> set_moved(std::move(_set));
  auto j = set_moved.begin();
  for (auto i = set_copy.begin(); i != set_copy.end(); ++i) {
    EXPECT_EQ(i->key, j->key);
    ++j;
  }
  EXPECT_TRUE(_set.empty());
}

//Операторы
TEST(SetOperator, MoveAssignment) {
  s21::set<std::string> first({"alpha", "beta", "gamma"});
  s21::set<std::string> copy(first);
  s21::set<std::string> second;
  second = std::move(first);
  auto j = second.begin();
  for (auto i = copy.begin(); i != copy.end(); ++i) {
    EXPECT_EQ(i->key, j->key);
    ++j;
  }
  EXPECT_TRUE(first.empty());
}

// // Итераторы
TEST(SetIterator, Begin) {
  s21::set<std::string> _set({"apple", "banana", "cherry"});
  auto i = _set.begin();
  EXPECT_EQ(i->key, "apple");
}

TEST(SetIterator, End) {
  s21::set<std::string> _set({"apple", "banana", "cherry"});
  auto i = _set.end();
  --i;
  EXPECT_EQ(i->key, "cherry");
}

TEST(SetIteratorOperator, Increment) {
  s21::set<std::string> _set({"apple", "banana", "cherry"});
  auto i = _set.begin();
  ++i;
  EXPECT_EQ(i->key, "banana");
  i++;
  EXPECT_EQ(i->key, "cherry");
}

TEST(SetIteratorOperator, Decrement) {
  s21::set<int> _set({12, 9, 7, 5, 3});
  auto i = _set.end();
  --i;
  EXPECT_EQ(i->key, 12);
  i--;
  EXPECT_EQ(i->key, 9);

  int j = 3;
  while (i != _set.begin()) {
    --i;
  }
  EXPECT_EQ(i->key, j);
}

// Размер и операции
TEST(SetSize, SizeCheck) {
  s21::set<int> _set({12, 9, 7, 5, 3});
  EXPECT_EQ(_set.Size(), 5);
  _set.clear();
  EXPECT_TRUE(_set.empty());
  EXPECT_EQ(_set.max_size(), std::numeric_limits<size_t>::max() / sizeof(int));
  EXPECT_EQ(_set.Size(), 0);
}

TEST(SetInsert, InsertSingle) {
  s21::set<int> _set;
  _set.insert(33);
  auto i = _set.begin();
  EXPECT_EQ(i->key, 33);
}

TEST(SetInsert, InsertExisting) {
  s21::set<int> _set({12, 9, 7, 5, 3});
  _set.insert(45);
  EXPECT_TRUE(_set.contains(45));
}

TEST(SetInsert, InsertMany) {
  s21::set<int> _set({12, 9, 7, 5, 3});
  auto v = _set.insert_many(33, 45, 67);
  EXPECT_TRUE(_set.contains(33));
  EXPECT_TRUE(_set.contains(45));
  EXPECT_TRUE(_set.contains(67));
  EXPECT_EQ(v[0].second, 1);
  EXPECT_EQ(v[1].second, 1);
  EXPECT_EQ(v[2].second, 1);
}

TEST(SetErase, EraseSingle) {
  s21::set<int> _set({12, 9, 7, 5, 3});
  auto i = _set.insert(21).first;
  _set.erase(i);
  EXPECT_FALSE(_set.contains(21));
}

TEST(SetSwap, SwapTest) {
  s21::set<int> _set({12, 9, 7, 5});
  s21::set<int> set_copy(_set);
  s21::set<int> _s({33, 45, 67});
  s21::set<int> s_copy(_s);
  _set.swap(_s);
  auto it = _s.begin();
  for (auto i = set_copy.begin(); i != set_copy.end(); ++i) {
    EXPECT_EQ(i->key, it->key);
    ++it;
  }
  it = _set.begin();
  for (auto i = s_copy.begin(); i != s_copy.end(); ++i) {
    EXPECT_EQ(i->key, it->key);
    ++it;
  }
}

TEST(SetMerge, MergeTest) {
  s21::set<int> _set({9, 7, 5});
  s21::set<int> _s({8, 10, 6});
  _set.merge(_s);
  int i = 5;
  for (auto it = _set.begin(); it != _set.end(); ++it) {
    EXPECT_EQ(it->key, i++);
  }
}

TEST(SetContains, ContainsTest) {
  s21::set<int> _set({12, 7, 5});
  _set.insert(33);
  EXPECT_TRUE(_set.contains(33));
  EXPECT_FALSE(_set.contains(99));
}

TEST(SetFind, FindTest) {
  s21::set<int> _set({12, 7, 5});
  int k = 12;
  auto i = _set.find(k);
  for (auto it = _set.begin(); it != _set.end(); ++it) {
    if (it->key == k) {
      EXPECT_EQ(it, i);
    }
  }
}

// Тесты на очистку
TEST(SetClear, ClearTest) {
  s21::set<int> set({8, 16});
  set.clear();
  EXPECT_TRUE(set.empty());
  EXPECT_EQ(set.Size(), 0u);
}
