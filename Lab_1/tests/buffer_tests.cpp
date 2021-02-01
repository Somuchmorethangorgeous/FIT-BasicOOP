#include <gtest/gtest.h>
#include "../main/circular_buffer.h"



class CircularBufferFixture : public ::testing::Test {
public:
    ~CircularBufferFixture() override { delete q0; delete q1; delete q2; delete q3;}
protected:
    void SetUp() override {
        q0 = new CircularBuffer<int>();
        q1 = new CircularBuffer<int>(5);
        q2 = new CircularBuffer<int>(26 , 0);
        q3 = new CircularBuffer<int>(26, 3);
    }
    CircularBuffer<int>* q0;
    CircularBuffer<int>* q1;
    CircularBuffer<int>* q2;
    CircularBuffer<int>* q3;
};


TEST_F(CircularBufferFixture, IsEmpty){
    EXPECT_TRUE(q0->empty());
    EXPECT_FALSE( q2->empty());
}


TEST_F(CircularBufferFixture, IsEqual){
    auto tmp2 = CircularBuffer<int>(10,3 );
    auto tmp3 = CircularBuffer<int>(26, 3);
    EXPECT_FALSE(tmp2 == tmp3);
    EXPECT_TRUE( tmp3 == *q3);
}


TEST_F(CircularBufferFixture, AtAndInsert){
    EXPECT_ANY_THROW(q2->at(30));
    EXPECT_NO_THROW(q2->at(3));
    q2->insert(9, 81);
    EXPECT_EQ(81, q2->at(9));
    q2->clear();
    EXPECT_ANY_THROW(q2->insert(8, 5));
    EXPECT_ANY_THROW(q2->insert(0, 102));
    for (int i = 0; i < 5; ++i)
        q2->push_back(i);
    q2->insert(2, 3000);
    EXPECT_EQ(3000, q2->at(2));
}


TEST_F(CircularBufferFixture, PushBackAndPop) {
    for(int i = 5; i > 0; --i)
        q1->push_back(i);
    EXPECT_EQ(5, q1->front());
    EXPECT_EQ(1, q1->back());
    q1->push_back(8);
    EXPECT_EQ(4, q1->front());
    EXPECT_EQ(8, q1->back());
    q1->push_back(9);
    q1->pop_back();
    q1->pop_front();
    EXPECT_EQ(2, q1->front());
    EXPECT_EQ(8, q1->back());
    q1->pop_back();
    EXPECT_EQ(2, q1->front());
    EXPECT_EQ(1, q1->back());
}


TEST_F(CircularBufferFixture, PushFrontAndPop){
    for(int i = 5; i > 0; --i)
        q1->push_front(i);
    EXPECT_EQ(1, q1->front());
    EXPECT_EQ(5, q1->back());
    q1->push_front(8);
    q1->push_front(9);
    EXPECT_EQ(9, q1->front());
    EXPECT_EQ(3, q1->back());
    for(int i = 0; i < 5; ++i)
        q1->pop_back();
    EXPECT_ANY_THROW(q1->pop_back());
}


TEST_F(CircularBufferFixture, Erase){
    for(int i = 0; i < q1->capacity(); ++i)
        q1->push_back(i);
    EXPECT_NO_THROW(q1->erase(0,3));
    EXPECT_EQ(3, q1->at(0));
    EXPECT_EQ(4, q1->at(1));
    EXPECT_NO_THROW(q1->erase(0, 2));
}


TEST_F(CircularBufferFixture, Linearize){
    for (int i = 0; i <= q1->capacity(); ++i)
        q1->push_back(i);
    EXPECT_FALSE(q1->is_linearized());
    q1->linearize();
    EXPECT_EQ(1, q1->at(0));
}


TEST_F(CircularBufferFixture, Swap){
    auto tmp2 = *q2;
    auto tmp3 = *q3;
    q2->swap(*q3);
    EXPECT_TRUE(tmp2 == *q3);
    EXPECT_TRUE(tmp3 == *q2);
}


TEST_F(CircularBufferFixture, Clear){
    q2->clear();
    EXPECT_FALSE(q2->size());
    q2->push_back(1);
    q2->linearize();
    EXPECT_EQ(1, q2->at(0));
    EXPECT_EQ(1, q2->size());
    EXPECT_EQ(1, q2->front());
    EXPECT_EQ(1, q2->back());
}


TEST_F(CircularBufferFixture, ResizeAndSetCap){
    for (int i = 0; i < q1->capacity(); ++i)
        q1->push_back(i);
    q1->resize(5);
    for (int i = 0; i < q1->capacity(); ++i)
        EXPECT_EQ(i, q1->at(i));
    q1->resize(10, 132);
    for (int i = 5; i < q1->capacity(); ++i)
        EXPECT_EQ(132, q1->at(i));
    q1->set_capacity(2);
    EXPECT_EQ(2, q1->capacity());
    for (int i = 0; i < q1->capacity(); ++i)
        EXPECT_EQ(i, q1->at(i));
}


TEST_F(CircularBufferFixture, MixedPushAndPop){
   auto* tmp = new CircularBuffer<int>(25);
   for (int i = 0; i < 25; ++i)
       tmp->push_back(i);
   EXPECT_EQ(0, tmp->front());
   EXPECT_EQ(24, tmp->back());
   tmp->rotate(5);
   EXPECT_EQ(5, tmp->front());
   EXPECT_EQ(4, tmp->back());
   tmp->pop_front();
   tmp->pop_back();
   EXPECT_EQ(6, tmp->front());
   EXPECT_EQ(3, tmp->back());
   tmp->resize(10);
   EXPECT_EQ(6, tmp->front());
   EXPECT_EQ(15, tmp->back());
   tmp->push_front(100);
   tmp->push_front(49);
   EXPECT_EQ(49, tmp->front());
   EXPECT_EQ(13, tmp->back());
   tmp->erase(2, 7);
   delete tmp;
}

