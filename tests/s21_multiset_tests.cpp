#include "test_s21_containers.h"

// Конструктор по умолчанию должен создавать пустой multiset
TEST(multiset_constructor, no_arg) {
  s21::multiset<int> _multiset;
  EXPECT_EQ(_multiset.empty(), 1);  // Проверяем, что multiset пустой
}

// Конструктор с инициализатором должен создавать непустой multiset
TEST(multiset_constructor, initializer_list) {
  s21::multiset<int> _multiset({3, 1, 4});
  EXPECT_EQ(_multiset.empty(), 0);  // Проверяем, что multiset не пустой
}

// Конструктор копирования должен создавать копию multiset
TEST(multiset_constructor, copy) {
  s21::multiset<int> _multiset({3, 1, 4});
  s21::multiset<int> multiset_copy(_multiset);
  auto j = multiset_copy.begin();
  for (auto i = _multiset.begin(); i != _multiset.end(); ++i) {
    ASSERT_EQ(i->key, j->key);  // Проверяем, что элементы совпадают
    ++j;
  }
}

// Конструктор перемещения должен перемещать содержимое multiset
TEST(multiset_constructor, move) {
  s21::multiset<int> _multiset({3, 1, 4});
  s21::multiset<int> multiset_moved(std::move(_multiset));
  EXPECT_EQ(_multiset.empty(), 1);  // Проверяем, что исходный multiset пуст
  auto i = multiset_moved.begin();
  EXPECT_EQ(i->key, 1);  // Проверяем, что элементы перемещены
}

// Оператор присвоения перемещением должен переносить содержимое
TEST(multiset_operator, move_assignment) {
  s21::multiset<int> first({3, 1, 4});
  s21::multiset<int> second;
  second = std::move(first);
  EXPECT_EQ(first.empty(), 1);  // Проверяем, что исходный multiset пуст
  auto i = second.begin();
  EXPECT_EQ(i->key, 1);  // Проверяем, что элементы перемещены
}

// Вставка одного элемента в multiset
TEST(multiset_insert, insert_single) {
  s21::multiset<int> _multiset;
  _multiset.insert(7);
  auto i = _multiset.begin();
  EXPECT_EQ(i->key, 7);  // Проверяем, что элемент вставлен
}

// Вставка нескольких элементов в multiset
TEST(multiset_insert, insert_many) {
  s21::multiset<int> _multiset({1, 2, 3});
  auto result = _multiset.insert_many(1, 7, 2);
  EXPECT_EQ(_multiset.contains(7), 1);  // Проверяем, что элементы вставлены
  EXPECT_EQ(_multiset.count(2),
            2);  // Проверяем количество вставленных элементов
  EXPECT_EQ(result[0].second, 1);  // Проверяем результаты вставки
  EXPECT_EQ(result[1].second, 1);
}

// Проверка размера multiset и очистка
TEST(multiset_size, size_and_clear) {
  s21::multiset<int> _multiset({1, 2, 2, 3});
  EXPECT_EQ(_multiset.Size(), 4);  // Проверяем размер multiset
  _multiset.clear();
  EXPECT_EQ(_multiset.empty(), 1);  // Проверяем, что multiset очищен
}

// Удаление элемента из multiset
TEST(multiset_erase, erase_element) {
  s21::multiset<int> _multiset({1, 2, 3, 4});
  auto it = _multiset.find(3);
  _multiset.erase(it);
  EXPECT_EQ(_multiset.contains(3), 0);  // Проверяем, что элемент удален
}

// Обмен содержимого двух multiset
TEST(multiset_swap, swap_contents) {
  s21::multiset<int> set1({1, 2, 3});
  s21::multiset<int> set2({7, 8, 9});
  set1.swap(set2);
  auto i = set1.begin();
  EXPECT_EQ(i->key, 7);  // Проверяем, что содержимое обменено
}

// Слияние двух multiset
TEST(multiset_merge, merge_sets) {
  s21::multiset<int> set1({1, 2, 3});
  s21::multiset<int> set2({4, 5, 6});
  set1.merge(set2);
  int expected_values[] = {1, 2, 3, 4, 5, 6};
  int index = 0;
  for (auto it = set1.begin(); it != set1.end(); ++it) {
    EXPECT_EQ(it->key,
              expected_values[index++]);  // Проверяем, что слияние выполнено
                                          // правильно
  }
}

// Проверка наличия элемента в multiset
TEST(multiset_contains, check_contains) {
  s21::multiset<int> _multiset({1, 2, 3});
  EXPECT_EQ(_multiset.contains(2), 1);  // Проверяем, что элемент присутствует
  EXPECT_EQ(_multiset.contains(4), 0);  // Проверяем, что элемента нет
}

// Поиск элемента в multiset
TEST(multiset_find, find_element) {
  s21::multiset<int> _multiset({1, 2, 3});
  auto it = _multiset.find(2);
  EXPECT_EQ(it->key,
            2);  // Проверяем, что найденный элемент соответствует искомому
}

// Проверка нижней и верхней границ для элемента
TEST(multiset_bounds, lower_upper_bound) {
  s21::multiset<int> _multiset({1, 2, 2, 3});
  auto lower = _multiset.lower_bound(2);
  auto upper = _multiset.upper_bound(2);
  EXPECT_EQ(lower->key,
            2);  // Проверяем, что lower_bound возвращает корректное значение
  EXPECT_EQ((--upper)->key,
            2);  // Проверяем, что upper_bound возвращает корректное значение
}

// Проверка диапазона равенства для элемента
TEST(multiset_equal_range, equal_range) {
  s21::multiset<int> _multiset({1, 2, 2, 3});
  auto range = _multiset.equal_range(2);
  int count = 0;
  for (auto it = range.first; it != range.second; ++it) {
    EXPECT_EQ(
        it->key,
        2);  // Проверяем, что все элементы в диапазоне равны искомому значению
    count++;
  }
  EXPECT_EQ(count, 2);  // Проверяем количество элементов в диапазоне
}
