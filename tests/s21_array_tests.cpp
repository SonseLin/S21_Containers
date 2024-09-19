#include "test_s21_containers.h"

TEST(MemberFunctTest, MemberFunctArray) {
  s21::array<int, 7> arr1;
  EXPECT_EQ(arr1.size(), 7); /*basic1*/
  for (size_t i = 0; i < arr1.size(); ++i) {
    EXPECT_EQ(arr1[i], 0);
  }

  s21::array<double, 0> arr2; /*basic2*/
  EXPECT_EQ(arr2.size(), 0);

  s21::array<int, 5> arr3{1, 2, 3, 4, 5}; /*initializerList1*/
  EXPECT_EQ(arr3.size(), 5);
  for (size_t i = 0; i < arr3.size(); ++i) {
    EXPECT_EQ(arr3[i], static_cast<int>(i) + 1);
  }

  s21::array<int, 1> arr4{}; /*initializerList2*/
  EXPECT_EQ(arr4.size(), 1);
  EXPECT_EQ(arr4[0], 0);

  s21::array<int, 3> arr5{1, 2}; /*initializerList3*/
  EXPECT_EQ(arr5.size(), 3);
  EXPECT_EQ(arr5[0], 1);
  EXPECT_EQ(arr5[1], 2);
  EXPECT_EQ(arr5[2], 0);

  s21::array<int, 5> arr3copy(arr3); /*copy1*/
  EXPECT_EQ(arr3copy.size(), 5);
  for (size_t i = 0; i < arr3.size(); ++i) {
    EXPECT_EQ(arr3copy[i], arr3[i]);
  }

  s21::array<double, 0> arr2copy(arr2); /*copy2*/
  EXPECT_EQ(arr2copy.size(), 0);

  s21::array<int, 3> arr5move(std::move(arr5)); /*move*/
  EXPECT_EQ(arr5move.size(), 3);
  EXPECT_EQ(arr5move[0], 1);
  EXPECT_EQ(arr5move[1], 2);
  EXPECT_EQ(arr5move[2], 0);
  EXPECT_EQ(arr5.size(), 0);

  s21::array<double, 2> arr6{1.3423, -12413.425}; /*operator=*/
  s21::array<double, 2> resarr6;
  resarr6 = std::move(arr6);
  EXPECT_EQ(resarr6.size(), 2);
  EXPECT_DOUBLE_EQ(resarr6[0], 1.3423);
  EXPECT_DOUBLE_EQ(resarr6[1], -12413.425);
  EXPECT_EQ(arr6.size(), 0);
}

TEST(ElementAccessTest, ElementAccessArray) {
  s21::array<double, 5> arr1; /*at1*/
  EXPECT_THROW(arr1.at(7), std::out_of_range);

  s21::array<std::string, 2> arr2{"Hello", "World"}; /*at2*/
  const char *str = arr2.at(1).c_str();
  EXPECT_EQ(std::string(str), "World");

  s21::array<double, 7> arr3{1123.453, 4523.345,  45.545,  98908,
                             78.00001, 0.0002345, 234.2345}; /*at3*/
  double at3 = arr3.at(4);
  EXPECT_DOUBLE_EQ(at3, 78.00001);
  at3 = arr3.at(0);
  EXPECT_DOUBLE_EQ(at3, 1123.453);
  at3 = arr3.at(6);
  EXPECT_DOUBLE_EQ(at3, 234.2345);

  EXPECT_EQ(arr2[0], "Hello"); /*operator[]1*/
  EXPECT_EQ(arr2[1], "World");

  EXPECT_DOUBLE_EQ(arr3[1], 4523.345); /*operator[]2*/
  EXPECT_DOUBLE_EQ(arr3[2], 45.545);
  EXPECT_DOUBLE_EQ(arr3[3], 98908);
  EXPECT_DOUBLE_EQ(arr3[5], 0.0002345);

  str = arr2.front().c_str(); /*front/back1*/
  EXPECT_EQ(std::string(str), "Hello");
  str = arr2.back().c_str();
  EXPECT_EQ(std::string(str), "World");

  double x = arr3.front(); /*front/back2*/
  EXPECT_DOUBLE_EQ(x, 1123.453);
  x = arr3.back();
  EXPECT_DOUBLE_EQ(x, 234.2345);

  x = arr1.front(); /*front/back3*/
  EXPECT_DOUBLE_EQ(x, 0.0);
  x = arr1.back();
  EXPECT_DOUBLE_EQ(x, 0.0);
}

TEST(IteratorsTest, IteratorsArray) {
  s21::array<int, 5> arr1{1, 2, 3, 4, 5}; /*begin/end1*/
  auto iter_b1 = arr1.begin();
  EXPECT_EQ(*iter_b1, 1);
  *iter_b1 = 10;
  EXPECT_EQ(arr1[0], 10);
  auto iter_e1 = arr1.end();
  EXPECT_EQ(iter_e1, iter_b1 + 5);
  EXPECT_EQ(*(--iter_e1), 5);

  s21::array<double, 3> arr2{54234.678678, -232.32454, -0.21312}; /*begin/end2*/
  auto iter_b2 = arr2.begin();
  EXPECT_EQ(*iter_b2, 54234.678678);
  *iter_b2 = -4534.8909;
  EXPECT_EQ(arr2[0], -4534.8909);
  auto iter_e2 = arr2.end();
  EXPECT_EQ(iter_e2, iter_b2 + 3);
  EXPECT_EQ(*(--iter_e2), -0.21312);
}

TEST(CapacityTest, CapacityArray) {
  s21::array<float, 0> arr1; /*empty, size, max_size1*/
  EXPECT_TRUE(arr1.empty());
  EXPECT_EQ(arr1.size(), 0);
  EXPECT_EQ(arr1.max_size(), 0);

  s21::array<float, 8> arr2; /*empty, size, max_size2*/
  EXPECT_FALSE(arr2.empty());
  EXPECT_EQ(arr2.size(), 8);
  EXPECT_EQ(arr2.max_size(), 8);

  s21::array<float, 4> arr3{2.4, 5.6, 7.8}; /*empty, size, max_size3*/
  EXPECT_FALSE(arr3.empty());
  EXPECT_EQ(arr3.size(), 4);
  EXPECT_EQ(arr3.max_size(), 4);
}

TEST(ModifiersTest, ModifiersArray) {
  s21::array<int, 5> arr1{1, 2, 3, 4, 5}; /*swap*/
  s21::array<int, 5> arr2{6, 7, 8, 9, 10};
  arr1.swap(arr2);
  for (size_t i = 0; i < arr1.size(); ++i) {
    EXPECT_EQ(arr1[i], static_cast<int>(i) + 6);
  }
  for (size_t i = 0; i < arr2.size(); ++i) {
    EXPECT_EQ(arr2[i], static_cast<int>(i) + 1);
  }

  arr1.fill(0); /*fill*/
  for (size_t i = 0; i < arr1.size(); ++i) {
    EXPECT_EQ(arr1[i], 0);
  }

  s21::array<std::string, 3> arr3;
  arr3.fill("!");
  for (size_t i = 0; i < arr3.size(); ++i) {
    EXPECT_EQ(arr3[i], "!");
  }
}