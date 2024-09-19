#include "test_s21_containers.h"

TEST(MemberFunctTest, MemberFunctVector) {
  s21::vector<int> v1; /*basic*/
  EXPECT_TRUE(v1.empty());
  EXPECT_EQ(v1.size(), 0);
  EXPECT_EQ(v1.capacity(), 0);

  s21::vector<int> v2(7);
  EXPECT_FALSE(v2.empty()); /*parametric1*/
  EXPECT_EQ(v2.size(), 7);
  EXPECT_EQ(v2.capacity(), 7);

  s21::vector<int> v3(0); /*parametric2*/
  EXPECT_TRUE(v3.empty());
  EXPECT_EQ(v3.size(), 0);
  EXPECT_EQ(v3.capacity(), 0);

  s21::vector<int> v4 = {}; /*initializerList1*/
  EXPECT_TRUE(v4.empty());
  EXPECT_EQ(v4.size(), 0);
  EXPECT_EQ(v4.capacity(), 0);

  s21::vector<int> v5{1, 2, 3, 4, 5}; /*initializerList2*/
  EXPECT_FALSE(v5.empty());
  EXPECT_EQ(v5.size(), 5);
  EXPECT_EQ(v5.capacity(), 5);
  EXPECT_EQ(v5[0], 1);
  EXPECT_EQ(v5[4], 5);

  s21::vector<int> v7(v1); /*copy1*/
  EXPECT_TRUE(v7.empty());
  EXPECT_EQ(v7.size(), 0);
  EXPECT_EQ(v7.capacity(), 0);

  s21::vector<int> v8{1, 2, 3}; /*copy2*/
  s21::vector<int> v9(v8);
  EXPECT_EQ(v9.size(), v8.size());
  EXPECT_EQ(v9.capacity(), v8.capacity());
  for (size_t i = 0; i < v8.size(); i++) {
    EXPECT_EQ(v8[i], v9[i]);
  }

  s21::vector<int> v10(3); /*move1*/
  s21::vector<int> v11(std::move(v10));
  EXPECT_FALSE(v11.empty());
  EXPECT_EQ(v10.size(), 0);
  EXPECT_EQ(v10.capacity(), 0);
  EXPECT_TRUE(v10.empty());
  EXPECT_EQ(v11.size(), 3);
  EXPECT_EQ(v11.capacity(), 3);

  s21::vector<int> v12{1, 2, 3}; /*move2*/
  s21::vector<int> v13(std::move(v12));
  EXPECT_EQ(v13.size(), 3);
  EXPECT_EQ(v13.capacity(), 3);
  EXPECT_TRUE(v12.empty());
  EXPECT_EQ(v12.size(), 0);
  EXPECT_EQ(v12.capacity(), 0);

  v1 = std::move(v7); /*oper=1*/
  EXPECT_TRUE(v1.empty());
  EXPECT_EQ(v1.size(), 0);
  EXPECT_EQ(v1.capacity(), 0);
  EXPECT_TRUE(v7.empty());
  EXPECT_EQ(v7.size(), 0);
  EXPECT_EQ(v7.capacity(), 0);

  s21::vector<int> v16{1, 2, 3};
  v7 = std::move(v16); /*oper=2*/
  EXPECT_EQ(v7.size(), 3);
  EXPECT_EQ(v7.capacity(), 3);
  EXPECT_EQ(v7[0], 1);
  EXPECT_EQ(v7[1], 2);
  EXPECT_EQ(v7[2], 3);
  EXPECT_TRUE(v16.empty());
  EXPECT_EQ(v16.size(), 0);
  EXPECT_EQ(v16.capacity(), 0);

  s21::vector<int> v18; /*oper=3*/
  s21::vector<int> v19{4, 5, 6};
  v19 = std::move(v18);
  EXPECT_TRUE(v19.empty());
  EXPECT_EQ(v19.size(), 0);

  s21::vector<double> v20{1.453, 2.34235, 4353}; /*oper=4*/
  s21::vector<double> v21{4.780, 0.005, 354.6};
  v21 = std::move(v20);
  EXPECT_EQ(v21.size(), 3);
  EXPECT_DOUBLE_EQ(v21[0], 1.453);
  EXPECT_DOUBLE_EQ(v21[1], 2.34235);
  EXPECT_DOUBLE_EQ(v21[2], 4353);
  EXPECT_TRUE(v20.empty());

  s21::vector<int> v22(1); /*oper=5*/
  s21::vector<int> v23(6);
  v23 = std::move(v22);
  EXPECT_EQ(v23.size(), 1);
  EXPECT_TRUE(v22.empty());
  v22 = std::move(v23);
  EXPECT_EQ(v22.size(), 1);
  EXPECT_TRUE(v23.empty());
}

TEST(ElementAccessTest, ElementAccessVector) {
  s21::vector<int> v1{1, 2, 3, 4, 5}; /*at1*/
  EXPECT_EQ(v1.at(0), 1);
  EXPECT_EQ(v1.at(2), 3);
  EXPECT_EQ(v1.at(4), 5);

  EXPECT_THROW(v1.at(5), std::out_of_range); /*at2*/
  EXPECT_THROW(v1.at(10), std::out_of_range);

  EXPECT_EQ(v1[0], 1); /*oper[]*/
  EXPECT_EQ(v1[2], 3);
  EXPECT_EQ(v1[4], 5);

  EXPECT_EQ(v1.front(), 1); /*front*/

  EXPECT_EQ(v1.back(), 5); /*back*/

  int *v1Ptr = v1.data(); /*data1*/
  EXPECT_EQ(*v1Ptr, 1);
  *v1Ptr = -1;
  EXPECT_EQ(v1[0], -1);

  s21::vector<double> v2; /*data2*/
  double *v2Ptr = v2.data();
  EXPECT_EQ(v2Ptr, nullptr);
}

TEST(IteratorsTest, IteratorsVector) {
  s21::vector<double> v1{0.32524, 234132, 47.3678, 36.4, 3124.0006}; /*begin*/
  s21::vector<double>::iterator iter1 = v1.begin();
  EXPECT_DOUBLE_EQ(*iter1, 0.32524);
  *iter1 = -5674.1;
  EXPECT_DOUBLE_EQ(v1[0], -5674.1);

  s21::vector<int> v2{1, 2, 3, 4, 5}; /*end*/
  s21::vector<int>::iterator iter2 = v2.end();
  --iter2;
  EXPECT_DOUBLE_EQ(*iter2, 5);
}

TEST(CapacityTest, CapacityVector) {
  s21::vector<int> v1; /*empty, size, max_size1*/
  EXPECT_TRUE(v1.empty());
  EXPECT_EQ(v1.size(), 0);
  EXPECT_GT(v1.max_size(), 0);

  s21::vector<int> v2{1, 2, 3}; /*empty, size, max_size2*/
  EXPECT_FALSE(v2.empty());
  EXPECT_EQ(v2.size(), 3);
  EXPECT_GT(v2.max_size(), 0);

  s21::vector<int> v3{4, 5, 6}; /*capacity, reserve1*/
  size_t capacityNow1 = v3.capacity();
  size_t capacityNew1 = capacityNow1 + 10;
  v3.reserve(capacityNew1);
  EXPECT_GE(v3.capacity(), capacityNew1);
  EXPECT_EQ(v3[0], 4);
  EXPECT_EQ(v3[1], 5);
  EXPECT_EQ(v3[2], 6);

  s21::vector<int> v4{1, 2, 3, 4, 5}; /*capacity, reserve2*/
  size_t capacityNow2 = v4.capacity();
  size_t capacityNew2 = capacityNow2 - 2;
  v4.reserve(capacityNew2);
  EXPECT_LE(v4.capacity(), capacityNow2);
  EXPECT_GE(v4.capacity(), capacityNew2);

  v1.shrink_to_fit(); /*shrink_to_fit1*/
  EXPECT_GE(v1.capacity(), 0);

  s21::vector<int> v5{1, 2, 3, 4, 5}; /*shrink_to_fit2*/
  size_t capacityNow = v5.capacity();
  v5.pop_back();
  v5.shrink_to_fit();
  EXPECT_LE(v5.capacity(), v5.size());
  EXPECT_LE(v5.capacity(), capacityNow);
}

TEST(ModifiersTest, ModifiersVector) {
  s21::vector<int> v1; /*clear1*/
  v1.clear();
  EXPECT_TRUE(v1.empty());
  EXPECT_EQ(v1.size(), 0);
  EXPECT_GE(v1.capacity(), 0);

  s21::vector<int> v2{1, 2, 3, 4, 5}; /*clear2*/
  v2.clear();
  EXPECT_TRUE(v2.empty());
  EXPECT_EQ(v2.size(), 0);
  EXPECT_GE(v2.capacity(), 0);

  s21::vector<int> v3{1, 2, 3}; /*pop_back1*/
  v3.pop_back();
  EXPECT_EQ(v3.size(), 2);
  EXPECT_EQ(v3.back(), 2);

  v1.pop_back(); /*pop_back2*/
  EXPECT_TRUE(v1.empty());

  s21::vector<double> v4{0.23451,    2.1234, 3234.769, 534.56,
                         524.007689, 123.45, 0.2,      123}; /*pop_back3*/
  v4.pop_back();
  EXPECT_EQ(v4.size(), 7);
  EXPECT_EQ(v4.back(), 0.2);

  s21::vector<int> v5{1, 2, 3}; /*swap1*/
  s21::vector<int> v6{4, 5, 6};
  v5.swap(v6);
  EXPECT_EQ(v5.size(), 3);
  EXPECT_EQ(v6.size(), 3);
  EXPECT_EQ(v5[0], 4);
  EXPECT_EQ(v5[1], 5);
  EXPECT_EQ(v5[2], 6);
  EXPECT_EQ(v6[0], 1);
  EXPECT_EQ(v6[1], 2);
  EXPECT_EQ(v6[2], 3);

  v2.swap(v3); /*swap2*/
  EXPECT_FALSE(v2.empty());
  EXPECT_EQ(v2.size(), 2);
  EXPECT_EQ(v2[0], 1);
  EXPECT_EQ(v2[1], 2);

  EXPECT_EQ(v3.size(), 0);
  EXPECT_TRUE(v3.empty());

  s21::vector<int> v7{1, 2, 3, 4}; /*erase1*/
  v7.erase(++v7.begin());
  EXPECT_EQ(v7.size(), 3);
  EXPECT_EQ(v7[1], 3);

  v4.erase(--v4.end()); /*erase2*/
  EXPECT_EQ(v4.size(), 6);
  EXPECT_EQ(v4[5], 123.45);

  v4.erase(++(++v4.begin())); /*erase3*/
  EXPECT_EQ(v4.size(), 5);
  EXPECT_EQ(v4[1], 2.1234);
  EXPECT_EQ(v4[2], 534.56);

  s21::vector<int> v8{2, 3, 4}; /*insert1*/
  s21::vector<int>::iterator it = v8.insert(v8.begin(), 1);
  EXPECT_EQ(v8.size(), 4);
  EXPECT_EQ(v8[0], 1);
  EXPECT_EQ(*it, 1);

  s21::vector<double> v9{1.1, 25.1}; /*insert2*/
  s21::vector<double>::iterator pos9 = v9.insert(++v9.begin(), 2024);
  EXPECT_EQ(v9.size(), 3);
  EXPECT_DOUBLE_EQ(v9[0], 1.1);
  EXPECT_DOUBLE_EQ(v9[1], 2024);
  EXPECT_DOUBLE_EQ(v9[2], 25.1);
  EXPECT_DOUBLE_EQ(*pos9, 2024);

  pos9 = v9.insert(v9.end(), 5.5); /*insert3*/
  EXPECT_EQ(v9.size(), 4);
  EXPECT_DOUBLE_EQ(v9[0], 1.1);
  EXPECT_DOUBLE_EQ(v9[1], 2024);
  EXPECT_DOUBLE_EQ(v9[2], 25.1);
  EXPECT_DOUBLE_EQ(v9[3], 5.5);
  EXPECT_DOUBLE_EQ(*pos9, 5.5);

  v3.push_back(11); /*push_back1*/
  EXPECT_EQ(v3.size(), 1);
  EXPECT_EQ(v3[0], 11);

  v9.push_back(-5353.3); /*push_back2*/
  EXPECT_EQ(v9.size(), 5);
  EXPECT_DOUBLE_EQ(v9[4], -5353.3);
}

TEST(InsertManyTest, InsertManyVector) {
  s21::vector<int> v1{1, 2, 3, 7, 8}; /*insert_many1*/
  s21::vector<int>::iterator pos1 = v1.insert_many(v1.cbegin() + 3, 4, 5, 6);

  EXPECT_EQ(v1.size(), 8);
  EXPECT_EQ(v1[0], 1);
  EXPECT_EQ(v1[1], 2);
  EXPECT_EQ(v1[2], 3);
  EXPECT_EQ(v1[3], 4);
  EXPECT_EQ(v1[4], 5);
  EXPECT_EQ(v1[5], 6);
  EXPECT_EQ(v1[6], 7);
  EXPECT_EQ(v1[7], 8);
  EXPECT_EQ(*pos1, 6);
  v1.insert_many(v1.cbegin());
  EXPECT_EQ(v1.size(), 8);

  s21::vector<int> v2{3, 4, 7}; /*insert_many2*/
  s21::vector<int>::iterator pos2 = v2.insert_many(v2.cbegin(), 1, 2);
  EXPECT_EQ(v2.size(), 5);
  EXPECT_EQ(v2[0], 1);
  EXPECT_EQ(v2[1], 2);
  EXPECT_EQ(v2[2], 3);
  EXPECT_EQ(v2[3], 4);
  EXPECT_EQ(v2[4], 7);
  EXPECT_EQ(*pos2, 2);
  pos2 = v2.insert_many(--v2.cend(), 5, 6);
  EXPECT_EQ(v2.size(), 7);
  EXPECT_EQ(v2[0], 1);
  EXPECT_EQ(v2[1], 2);
  EXPECT_EQ(v2[2], 3);
  EXPECT_EQ(v2[3], 4);
  EXPECT_EQ(v2[4], 5);
  EXPECT_EQ(v2[5], 6);
  EXPECT_EQ(v2[6], 7);
  EXPECT_EQ(*pos2, 6);

  s21::vector<int> v3{1}; /*insert_many_back*/
  v3.insert_many_back(2);
  v3.insert_many_back(3, 4, 5, 6, 7);
  v3.insert_many_back(8, 9);
  v3.insert_many_back();
  EXPECT_EQ(v3.size(), 9);
  EXPECT_EQ(v3[0], 1);
  EXPECT_EQ(v3[1], 2);
  EXPECT_EQ(v3[2], 3);
  EXPECT_EQ(v3[3], 4);
  EXPECT_EQ(v3[4], 5);
  EXPECT_EQ(v3[5], 6);
  EXPECT_EQ(v3[6], 7);
  EXPECT_EQ(v3[7], 8);
  EXPECT_EQ(v3[8], 9);
}