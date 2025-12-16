#include "pch.h"
#include <../../../Lab1Code/RealizationTBitField_Lab1.cpp>
#include <../../../Lab1Code/RealizationTSet_Lab1.cpp>

TEST(BitField, CreateBitFieldNoThrow) 
{
	EXPECT_NO_THROW({ //Не вернёт исключение.
		int n = 10;
		TBitField bf(n);
		});

	EXPECT_NO_THROW({ //Не вернёт исключение.
		int n = 10;
		TBitField bf1(n);
		TBitField bf2(bf1);
		});
}

TEST(BitField, CreateBitFieldAnyThrow)
{
	//Исключения:
	EXPECT_ANY_THROW({ //Вернёт исключение.
		int n = -10;
		TBitField bf(n);
		});

	EXPECT_ANY_THROW({ //Вернёт исключение.
		int n = 0;
		TBitField bf(n);
		});
}

TEST(BitField, AccessToBitNoThrow)
{
	EXPECT_NO_THROW({
		int n = 10;
		TBitField bf(10);
		EXPECT_EQ(bf.GetLength(), n);
		for (int i = 0; i < n; ++i)
		{
			EXPECT_EQ(bf.GetBit(i), 0);
			bf.SetBit(i); 
			EXPECT_EQ(bf.GetBit(i), 1);
			bf.ClrBit(i);
			EXPECT_EQ(bf.GetBit(i), 0);
		}
		});
}

TEST(BitField, AccessToBitAnyThrow)
{
	//Исключения:
	int n = 10;
	TBitField bf(10);
	EXPECT_ANY_THROW(bf.SetBit(n + 1));
	EXPECT_ANY_THROW(bf.GetBit(n + 1));
	EXPECT_ANY_THROW(bf.ClrBit(n + 1));
	EXPECT_ANY_THROW(bf.SetBit(-n));
	EXPECT_ANY_THROW(bf.GetBit(-n));
	EXPECT_ANY_THROW(bf.ClrBit(-n));
}

TEST(BitField, BitOperationsCompareSameBitLen)
{
	//Одинаковый размер битовых полей:
	int n = 10, bit = n-1;
	TBitField bf1(n), bf2(n), bf3(n);
	
	bf1.SetBit(bit); //  1000000000
	bf2.SetBit(bit); //  1000000000
	bf3.SetBit(0);   //  0000000001

	EXPECT_EQ(bf1 == bf1, 1);
	EXPECT_EQ(bf1 == bf2, 1);
	EXPECT_EQ(bf1 == bf3, 0);

	EXPECT_EQ(bf1 != bf1, 0);
	EXPECT_EQ(bf1 != bf2, 0);
	EXPECT_EQ(bf1 != bf3, 1);
}

TEST(BitField, BitOperationsCompareOtherBitLen)
{
	//Разный размер битовых полей:
	int n = 10, bit = n - 1;
	TBitField bf1(n), bf2(n + 1);

	bf1.SetBit(bit); //  1000000000
	bf2.SetBit(bit); // 01000000000

	EXPECT_EQ(bf1 == bf2, 0);

	EXPECT_EQ(bf1 != bf2, 1);

	bf2 = bf1; // bf2 станет 1000000000
	EXPECT_EQ(bf2 == bf1, 1);
}

TEST(BitField, BitFieldOperationsAndOrNotSameBitLen)
{
	//Одинаковый размер битовых полей:
	int n = 5;
	TBitField resbf1(n), resbf2(n), resbf3(n), bf1(n), bf2(n), bf3(n);
	bf1.SetBit(0);    //00001
	bf1.SetBit(2);    //00101
	bf2.SetBit(1);    //00010
	bf2.SetBit(2);    //00110
	resbf1.SetBit(0); //00001
	resbf1.SetBit(1); //00011
	resbf1.SetBit(2); //00111
	resbf2.SetBit(2); //00100
	EXPECT_EQ(bf1 | bf2, resbf1);
	EXPECT_EQ(bf1 & bf3, bf3);
	EXPECT_EQ(bf1 & bf2, resbf2);

	for (int i = 0; i < n; ++i) //resbf3 - 11111
	{
		resbf3.SetBit(i);
	}
	EXPECT_EQ(~bf3, resbf3);

	resbf3.ClrBit(2);
	resbf3.ClrBit(0);
	EXPECT_EQ(~bf1, resbf3);
}

TEST(BitField, BitFieldOperationsAndOrNotOtherBitLen)
{
	//Разный размер битовых полей:
	int k = 7, n = 5;
	TBitField bf_1(n), bf_2(k), res_1(k), res_2(k);
	bf_1.SetBit(4);  //  10000
	bf_1.SetBit(1);  //  10010
	bf_2.SetBit(5);  //0100000
	res_1.SetBit(4); //0010000
	res_1.SetBit(1); //0010010
	res_1.SetBit(5); //0110010
	EXPECT_EQ(bf_1 | bf_2, res_1);
	EXPECT_EQ(bf_2 | bf_1, res_1);

	bf_2.SetBit(4);  //0110000
	res_2.SetBit(4); //0010000
	EXPECT_EQ(bf_1 & bf_2, res_2);
	EXPECT_EQ(bf_2 & bf_1, res_2);
}

TEST(Set, CreateSetNoThrow)
{
	EXPECT_NO_THROW({ //Не вернёт исключение.
		int n = 10;
		TSet set(n);
		});

	EXPECT_NO_THROW({ //Не вернёт исключение.
		int n = 10;
		TSet set1(n);
		TSet set2(set1);
		});
	EXPECT_NO_THROW({ //Не вернёт исключение.
		int n = 10;
		TBitField bf1(n + n);
		TSet set1(bf1);
		});
}

TEST(Set, CreateSetAnyThrow)
{
	EXPECT_ANY_THROW({ //Вернёт исключение.
		int n = -10;
		TSet set(n);
		});

	EXPECT_ANY_THROW({ //Вернёт исключение.
		int n = 0;
		TSet set(n);
		});
}

TEST(Set, SetConversionToBitField)
{
	EXPECT_NO_THROW({
		int n = 10;
		TBitField bf(n);
		bf.SetBit(1);  //0000000010
		TSet set(n);
		set.InsElem(1);//{ 1 }
		EXPECT_EQ(TBitField(set), bf); // { 1 } => 0000000010
		});
}

TEST(Set, AccessToBitNoThrow)
{
	EXPECT_NO_THROW({
		int n = 10;
		TSet set(n);
		EXPECT_EQ(set.GetMaxPower(), n);
		for (int i = 0; i < n; ++i)
		{
			EXPECT_EQ(set.IsMember(i), 0);
			set.InsElem(i);
			EXPECT_EQ(set.IsMember(i), 1);
			set.DelElem(i);
			EXPECT_EQ(set.IsMember(i), 0);
		}
		});
}

TEST(Set, AccessToBitAnyThrow)
{
	//Исключения:
	int n = 10;
	TSet set(n);
	EXPECT_ANY_THROW(set.InsElem(n + 1));
	EXPECT_ANY_THROW(set.IsMember(n + 1));
	EXPECT_ANY_THROW(set.DelElem(n + 1));
	EXPECT_ANY_THROW(set.InsElem(-n));
	EXPECT_ANY_THROW(set.IsMember(-n));
	EXPECT_ANY_THROW(set.DelElem(-n));
}

TEST(Set, SetCompareSameMaxPower)
{
	//Одинаковый MaxPower (из одного универса):
	int n = 10, elem = n - 1;
	TSet set1(n), set2(n), set3(n);

	set1.InsElem(elem); //{ n-1 }. { 9 }. MaxPower = n;
	set2.InsElem(elem); //{ n-1 }. { 9 }. MaxPower = n;
	set3.InsElem(1);    //{ 1 n-1}. { 1 9 }. MaxPower = n;

	EXPECT_EQ(set1 == set1, 1);
	EXPECT_EQ(set1 == set2, 1);
	EXPECT_EQ(set1 == set3, 0);

	EXPECT_EQ(set1 != set1, 0);
	EXPECT_EQ(set1 != set2, 0);
	EXPECT_EQ(set1 != set3, 1);
}

TEST(Set, SetCompareOtherMaxPower)
{
	//Разный MaxPower (из разных универсов):
	int n = 10, elem = n - 1;
	TSet set1(n), set2(n + 1);

	set1.InsElem(elem); //{ n-1 }. { 9 }. MaxPower = n;
	set2.InsElem(elem); //{ n-1 }. { 9 }. MaxPower = n + 1;

	EXPECT_EQ(set1 == set2, 0);

	EXPECT_EQ(set1 != set2, 1);
	set2 = set1; // set2 станет { n-1 }. { 9 }.
	EXPECT_EQ(set2 == set1, 1);
}

TEST(Set, SetOperationsSameMaxPower)
{
	//Одинаковый MaxPower (из одного универса):
	int n = 5;
	TSet set1(n), set2(n), set3(n), res_set1(n), res_set2(n);

	res_set1.InsElem(2); //{ 2 }.
	EXPECT_EQ(set1 + 2, res_set1);
	res_set1.InsElem(4); //{ 2 4 }.
	EXPECT_EQ(set1 + 4, res_set1 - 2);

	EXPECT_EQ(res_set1 - 2, set1 + 4);
	EXPECT_EQ(res_set1 - 4, set1 + 2);

	set1.InsElem(1); //{ 1 }.
	set1.InsElem(2); //{ 1 2 }.
	set2.InsElem(4); //{ 4 }.
	EXPECT_EQ(set1 + set1, set1);
	EXPECT_EQ(set1 + set2, res_set2 + 1 + 2 + 4);
	EXPECT_EQ(set2 + set1, res_set2 + 1 + 2 + 4);

	set2.InsElem(1); //{ 1 4 }.
	EXPECT_EQ(set1 * set1, set1);
	EXPECT_EQ(set1 * set2, res_set2 + 1);
	EXPECT_EQ(set2 * set1, res_set2 + 1);

	set1.DelElem(2); //{ 1 }.
	set1.InsElem(3); //{ 1 3 }.
	EXPECT_EQ(~set1, res_set1);
	EXPECT_EQ(~res_set1, set1);
	EXPECT_EQ(~~set1, set1);
}

TEST(Set, SetOperationsOtherMaxPower)
{
	//Разный MaxPower (из разных универсов):
	int n = 5;
	TSet set1(n), set2(n + 1);
	set2.InsElem(1); //{ 1 }.
	set2.InsElem(2); //{ 1 2 }.
	EXPECT_ANY_THROW(set2 + set1);
	EXPECT_ANY_THROW(set2 * set1);
}