#include "pch.h"
#include <stdexcept> 
#include "../TBitField_TSet/tbitfield.cpp"
#include "../TBitField_TSet/tset.cpp"

//-----------------------  TBitField  ----------------------

TEST(BitField, ConstructAndLength) {
    TBitField bf(10);
    EXPECT_EQ(bf.GetLength(), 10);
    EXPECT_THROW(TBitField(-1), std::invalid_argument);
}

TEST(BitField, SetClrGetBit) {
    TBitField bf(5);
    bf.SetBit(2);
    EXPECT_EQ(bf.GetBit(2), 1);
    bf.ClrBit(2);
    EXPECT_EQ(bf.GetBit(2), 0);
    EXPECT_THROW(bf.SetBit(5), std::out_of_range);
    EXPECT_THROW(bf.GetBit(-1), std::out_of_range);
}

TEST(BitField, LogicOperators) {
    TBitField a(4), b(4);
    a.SetBit(1);
    b.SetBit(2);
    TBitField u = a | b;
    EXPECT_TRUE(u.GetBit(1));
    EXPECT_TRUE(u.GetBit(2));
    TBitField i = a & b;
    EXPECT_FALSE(i.GetBit(1));
    EXPECT_FALSE(i.GetBit(2));
    TBitField neg = ~a;
    EXPECT_FALSE(neg.GetBit(1));
    for (int i = 0; i < 4; ++i)
        if (i != 1) EXPECT_TRUE(neg.GetBit(i));
}

TEST(BitField, DifferentLength) {
    TBitField a(5), b(10);
    a.SetBit(1);
    b.SetBit(7);
    TBitField u = a | b;
    EXPECT_TRUE(u.GetBit(1));
    EXPECT_TRUE(u.GetBit(7));
    EXPECT_EQ(u.GetLength(), 10);
}

TEST(BitField, EqualAndInequal) {
    TBitField a(5), b(5);
    a.SetBit(2);
    b.SetBit(2);
    EXPECT_TRUE(a == b);
    b.SetBit(3);
    EXPECT_TRUE(a != b);
}

TEST(BitField, RepeatedSet) {
    TBitField bf(5);
    bf.SetBit(2);
    bf.SetBit(2); // повторная установка
    EXPECT_EQ(bf.GetBit(2), 1);
}

TEST(BitField, EmptyInversion) {
    TBitField bf(4);
    TBitField neg = ~bf;
    for (int i = 0; i < 4; i++)
        EXPECT_TRUE(neg.GetBit(i));
}

TEST(BitField, CopyConstructorIsCorrect) {
    TBitField original(6);
    original.SetBit(3);
    TBitField copy(original);
    EXPECT_EQ(copy.GetLength(), 6);
    EXPECT_TRUE(copy.GetBit(3));
    EXPECT_TRUE(original == copy);
}

TEST(BitField, AssignmentOperatorIsCorrect) {
    TBitField a(4);
    a.SetBit(1);
    TBitField b(2);
    b.SetBit(0);
    b = a;
    EXPECT_EQ(b.GetLength(), 4);
    EXPECT_TRUE(b.GetBit(1));
    EXPECT_TRUE(a == b);
}

//--------------------------  TSet  --------------------------

TEST(Set, InsDelIsmemTest) {
    TSet s(5);
    EXPECT_EQ(s.IsMember(3), 0);
    s.InsElem(3);
    EXPECT_EQ(s.IsMember(3), 1);
    s.DelElem(3);
    EXPECT_EQ(s.IsMember(3), 0);
}

TEST(Set, UniIntersOps) {
    TSet a(4), b(4);
    a.InsElem(1); b.InsElem(2);
    TSet u = a + b;
    EXPECT_TRUE(u.IsMember(1) && u.IsMember(2));
    TSet inter = a * b;
    EXPECT_FALSE(inter.IsMember(1));
}

TEST(Set, Complement) {
    TSet s(3);
    s.InsElem(0);
    TSet comp = ~s; // 011
    EXPECT_FALSE(comp.IsMember(0));
    EXPECT_TRUE(comp.IsMember(1));
    EXPECT_TRUE(comp.IsMember(2));
}

TEST(Set, EqualAndInequal) {
    TSet a(5), b(5);
    a.InsElem(2);
    b.InsElem(2);
    EXPECT_TRUE(a == b);
    b.InsElem(3);
    EXPECT_TRUE(a != b);
}

TEST(Set, DifferentSizes) {
    TSet a(5), b(8);
    EXPECT_THROW(a + b, std::invalid_argument);

}

TEST(Set, IntersectionDifferentSizes) {
    TSet a(5), b(8);
    EXPECT_THROW(a * b, std::invalid_argument);
}

TEST(Set, ConversionToBitField) {
    TSet s(5);
    s.InsElem(2);
    TBitField bf = s;
    EXPECT_EQ(bf.GetBit(2), 1);
}

TEST(Set, SetInversion) {
    TSet s(3);
    s.InsElem(0);
    s.InsElem(1);
    s.InsElem(2);
    TSet comp = ~s;
    for (int i = 0; i < 3; i++)
        EXPECT_FALSE(comp.IsMember(i));
}
TEST(Set, CopyConstructorIsCorrect) {
    TSet original(6);
    original.InsElem(4);
    TSet copy(original);
    EXPECT_EQ(copy.GetMaxPower(), 6);
    EXPECT_TRUE(copy.IsMember(4));
    EXPECT_TRUE(original == copy);
}

TEST(Set, AssignmentOperatorIsCorrect) {
    TSet a(5);
    a.InsElem(2);
    TSet b(3);
    b = a;
    EXPECT_EQ(b.GetMaxPower(), 5);
    EXPECT_TRUE(b.IsMember(2));
    EXPECT_TRUE(a == b);
}

TEST(Set, OutOfRangeThrows) {
    TSet s(4);
    EXPECT_THROW(s.InsElem(5), std::out_of_range);
    EXPECT_THROW(s.InsElem(-1), std::out_of_range);
    EXPECT_THROW(s.DelElem(6), std::out_of_range);
    EXPECT_THROW(s.DelElem(-2), std::out_of_range);
    EXPECT_THROW(s.IsMember(10), std::out_of_range);
    EXPECT_THROW(s.IsMember(-3), std::out_of_range);
}

