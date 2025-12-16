#include "pch.h"
#include "../Lab1/TBitField.cpp"
#include "../Lab1/TSet.cpp"
#include <random>
#include <fstream> 

using std::uniform_int_distribution;
using std::default_random_engine;
using std::string;
using std::ofstream;
using std::ifstream;

TBitField get_random_bitfield(int len) {
	TBitField res(len);
	uniform_int_distribution<> un(0, 1);
	default_random_engine re;
	for (int i = 0; i < len; ++i) {
		if (un(re)) {
			res.SetBit(i);
		}
	}
	return res;
}

//TBitField Tests

TEST(TBitfield_Constructor, len_constructor) {
	uniform_int_distribution<> un(1, 1024);
	default_random_engine re;
	for (int i = 0; i < 10; ++i) {
		EXPECT_NO_THROW(TBitField(un(re)));
	}
}

TEST(TBitfield_Constructor, copy_constructor) {
	uniform_int_distribution<> un(1, 1024);
	default_random_engine re;
	TBitField tst = get_random_bitfield(un(re));
	EXPECT_NO_THROW(TBitField copy(tst));
	TBitField copy(tst);
	EXPECT_EQ(tst.GetLength(), copy.GetLength());
	int length = tst.GetLength();
	for (int i = 0; i < length; ++i) {
		EXPECT_EQ(tst.GetBit(i), copy.GetBit(i));
	}
	tst.GetBit(0) == 0 ? copy.SetBit(0) : copy.ClrBit(0);
	EXPECT_NE(tst, copy);
}

TEST(Bits_Access, GetLength) {
	uniform_int_distribution<> un(1, 1024);
	default_random_engine re;
	int MemLen = un(re);
	TBitField test(get_random_bitfield(MemLen));
	EXPECT_EQ(MemLen, test.GetLength());
}

TEST(Bits_Access, SetBit_and_GetBit) {
	uniform_int_distribution<> un(1, 1024);
	default_random_engine re;
	int BitLen = un(re);
	un.param(uniform_int_distribution<>::param_type(0, 1));
	TBitField test(BitLen);
	EXPECT_EQ(0, test.GetBit(0)); 
	bool *arr = new bool[BitLen];
	for (int i = 0; i < BitLen; ++i) {
		if (un(re)) {
			arr[BitLen - 1 - i] = 1;
			test.SetBit(i);
 		}
		else {
			arr[BitLen - 1 - i] = 0;
		}
	}
	for (int i = 0; i < BitLen; ++i) {
		EXPECT_EQ(arr[BitLen - 1 - i], test.GetBit(i));
	}
	delete[] arr;
}

TEST(Bits_Access, ClrBit) {
	TBitField test(2);
	test.SetBit(1);
	test.ClrBit(0);
	test.ClrBit(1);
	EXPECT_EQ(0, test.GetBit(0)); // Проверка того, что ClrBit не меняет нулевой бит
	EXPECT_EQ(0, test.GetBit(1)); // Проверка того, что ClrBit обнуляет ненулевой бит
}

TEST(Bitwise_operations, Equal) {
	int BitLen = 20;
	TBitField test(get_random_bitfield(BitLen));
	EXPECT_TRUE(test == test); // Проверка равенства идентичных объектов
	BitLen = 10;
	TBitField zero_1(BitLen);
	TBitField zero_2(BitLen + 1);
	EXPECT_TRUE(zero_1 == zero_2); // Проверка равенства разных объектов, разного размера, содержащих одинаковые элементы
	EXPECT_FALSE(test == zero_1); // Проверка отсутствия равенства разных объектов с разными элементами
}

TEST(Bitwise_operations, Not_Equal) {
	int BitLen = 20;
	TBitField test(get_random_bitfield(BitLen));
	BitLen = 10;
	TBitField zero_1(BitLen);
	TBitField zero_2(BitLen);
	EXPECT_FALSE(test != test);
	EXPECT_FALSE(zero_1 != zero_2);
	EXPECT_TRUE(test != zero_1);
}

TEST(Bitwise_operations, Assignment) {
	int BitLen = 20;
	TBitField test(get_random_bitfield(BitLen));
	BitLen = 10;
	TBitField zero(BitLen);
	EXPECT_EQ(test, zero = test);
}

TEST(Bitwise_operations, Self_Assignment) {
	int BitLen = 20;
	TBitField test(get_random_bitfield(BitLen));
	TBitField test_before(test);
	EXPECT_EQ(test_before, test = test);
}

TEST(Bitwise_operations, Or_Equal_Sizes) {
	int BitLen = 65;
	TBitField test1(get_random_bitfield(BitLen));
	TBitField test2(get_random_bitfield(BitLen));
	TBitField test_or(BitLen);
	for (int i = 0; i < BitLen; ++i) {
		if (test1.GetBit(i) || test2.GetBit(i)) {
			test_or.SetBit(i);
		}
	}
	EXPECT_EQ(test_or, test1 | test2);
}

TEST(Bitwise_operations, And_Equal_Sizes) {
	int BitLen = 65;
	TBitField test1(get_random_bitfield(BitLen));
	TBitField test2(get_random_bitfield(BitLen));
	TBitField test_and(BitLen);
	for (int i = 0; i < BitLen; ++i) {
		if (test1.GetBit(i) && test2.GetBit(i)) {
			test_and.SetBit(i);
		}
	}
	EXPECT_EQ(test_and, test1 | test2);
}

TEST(Bitwise_operations, Or_Different_sizes) {
	int BitLen = 15;
	TBitField test1(get_random_bitfield(BitLen));
	TBitField test2(get_random_bitfield(BitLen + 1));
	TBitField test_or(test2);
	for (int i = 0; i < BitLen; ++i) {
		if (test1.GetBit(i) || test2.GetBit(i)) {
			test_or.SetBit(i);
		}
	}
	EXPECT_EQ(test_or, test1 | test2);
}

TEST(Bitwise_operations, And_Different_sizes) {
	int BitLen = 15;
	TBitField test1(get_random_bitfield(BitLen));
	TBitField test2(get_random_bitfield(BitLen + 1));
	TBitField test_and(BitLen + 1);
	for (int i = 0; i < BitLen; ++i) {
		if (test1.GetBit(i) && test2.GetBit(i)) {
			test_and.SetBit(i);
		}
	}
	EXPECT_EQ(test_and, test1 & test2);
}

TEST(Bitwise_operations, Negation) {
	int BitLen = 60;
	TBitField test(get_random_bitfield(BitLen));
	TBitField test_neg(BitLen);
	for (int i = 0; i < BitLen; ++i) {
		if (!test.GetBit(i)) {
			test_neg.SetBit(i);
		}
	}
	EXPECT_EQ(test_neg, ~test);
}

TEST(TBitfield_Input_Output, output) {
	default_random_engine re;
	uniform_int_distribution<> un(1, 120);
	int BitLen = un(re);
	TBitField test_out(get_random_bitfield(BitLen));
	string bit_string(BitLen, ' ');
	for (int i = 0; i < BitLen; ++i) {
		if (test_out.GetBit(i)) {
			bit_string[BitLen - 1 - i] = '1';
		}
		else {
			bit_string[BitLen - 1 - i] = '0';
		}
	}
	ofstream ofstr("test.txt");
	ofstr << test_out;
	ofstr.close();
	ifstream ifstr("test.txt");
	string string_from_file;
	ifstr >> string_from_file;
	ifstr.close();
	EXPECT_EQ(bit_string, string_from_file);
}

TEST(TBitfield_Input_Output, input) {
	default_random_engine re;
	uniform_int_distribution<> un(1, 120);
	int BitLen = un(re);
	TBitField test_from_file(BitLen);
	TBitField test_out(BitLen);
	string bit_string(BitLen, ' ');
	for (int i = 0; i < BitLen; ++i) {
		if (un(re)) {
			bit_string[BitLen - 1 - i] = '1';
			test_out.SetBit(i);
		}
		else {
			bit_string[BitLen - 1 - i] = '0';
		}
	}
	ofstream ofstr("test.txt");
	ofstr << bit_string;
	ofstr.close();
	ifstream ifstr("test.txt");
	ifstr >> test_from_file;
	ifstr.close();
	EXPECT_EQ(test_out, test_from_file);
}

TEST(TBitfield_Exceptions, Constructor_Not_Positive_Length) {
	EXPECT_THROW(TBitField(0), std::invalid_argument);
	EXPECT_THROW(TBitField(-1), std::invalid_argument);
}

TEST(TBitfield_Exceptions, Bits_Access_Out_Of_Range) {
	int BitLen = 17;
	TBitField test(get_random_bitfield(BitLen));
	EXPECT_THROW(test.GetBit(BitLen + 1), std::out_of_range);
	EXPECT_THROW(test.ClrBit(BitLen + 1), std::out_of_range);
	EXPECT_THROW(test.SetBit(BitLen + 1), std::out_of_range);
}

TEST(TBitfield_Exceptions, Bits_Access_Invalid_Argument) {
	int BitLen = 17;
	TBitField test(get_random_bitfield(BitLen));
	EXPECT_THROW(test.GetBit(-1), std::invalid_argument);
	EXPECT_THROW(test.ClrBit(-1), std::invalid_argument);
	EXPECT_THROW(test.SetBit(-1), std::invalid_argument);
}

TEST(TBitfield_Exceptions, Input_length_error) {
	int BitLen = 17;
	string bit_string(BitLen + 1, '1');
	TBitField test_from_file(BitLen);
	ofstream ofstr("test.txt");
	ofstr << bit_string;
	ofstr.close();
	ifstream ifstr("test.txt");
	EXPECT_THROW(ifstr >> test_from_file, std::length_error);
	ifstr.close();
}

TEST(TBitfield_Exceptions, Input_invalid_argument_error) {
	int BitLen = 1;
	string bit_string = "2";
	TBitField test_from_file(BitLen);
	ofstream ofstr("test.txt");
	ofstr << bit_string;
	ofstr.close();
	ifstream ifstr("test.txt");
	EXPECT_THROW(ifstr >> test_from_file, std::invalid_argument);
	ifstr.close();
}


//TSet Tests

TSet get_random_set(int mp) {
	return TSet(get_random_bitfield(mp));
}

TEST(TSet_Constructor, mp_constructor) {
	uniform_int_distribution<> un(1, 1024);
	default_random_engine re;
	for (int i = 0; i < 10; ++i) {
		EXPECT_NO_THROW(TSet(un(re)));
	}
}

TEST(TSet_Constructor, copy_constructor) {
	uniform_int_distribution<> un(1, 512);
	default_random_engine re;
	TSet tst(get_random_set(un(re)));
	EXPECT_NO_THROW(TSet copy(tst));
	TSet copy(tst);
	tst.IsMember(0) ? copy.DelElem(0) : copy.InsElem(0);
	EXPECT_NE(tst.IsMember(0), copy.IsMember(0));
}

TEST(TSet_Constructor, converting_constructor) {
	uniform_int_distribution<> un(1, 512);
	default_random_engine re;
	EXPECT_NO_THROW(TSet(get_random_bitfield(un(re))));
}

TEST(Type_Conversion_Operator, Operator) {
	uniform_int_distribution<> un(1, 120);
	default_random_engine re;
	TBitField test_bitfield(get_random_bitfield(un(re)));
	TSet test_set(test_bitfield);
	EXPECT_EQ(test_bitfield, TBitField(test_set));
}

TEST(Elements_Access, GetMaxPower) {
	uniform_int_distribution<> un(1, 1024);
	default_random_engine re;
	int MaxPower = un(re);
	TSet test(get_random_bitfield(MaxPower));
	EXPECT_EQ(MaxPower, test.GetMaxPower());
}

TEST(Elements_Access, InsElem_And_IsMember) {
	uniform_int_distribution<> un(1, 1024);
	default_random_engine re;
	int MaxPower = un(re);
	TSet test(MaxPower);
	un.param(uniform_int_distribution<>::param_type(0, MaxPower - 1));
	int rand_elem = un(re);
	EXPECT_FALSE(test.IsMember(rand_elem));
	EXPECT_NO_THROW(test.InsElem(rand_elem));
	EXPECT_TRUE(test.IsMember(rand_elem));
}

TEST(Elements_Access, DelElem) {
	uniform_int_distribution<> un(1, 1024);
	default_random_engine re;
	int MaxPower = un(re);
	TSet test(MaxPower);
	un.param(uniform_int_distribution<>::param_type(0, MaxPower - 1));
	int rand_elem = un(re);
	test.DelElem(rand_elem);
	EXPECT_FALSE(0, test.IsMember()); //Проверка того, что DelElem не влияет на отсутствующие в множестве элементы
	test.InsElem(rand_elem);
	EXPECT_TRUE(test.IsMember(rand_elem));
	test.DelElem(rand_elem);
	EXPECT_FALSE(test.IsMember(rand_elem));
}

TEST(SetTheoretic_Operations, Equal) {
	int MaxPower = 20;
	TSet test(get_random_set(MaxPower));
	EXPECT_TRUE(test == test);
	MaxPower = 10;
	TSet zero_1(MaxPower);
	TSet zero_2(MaxPower);
	TSet zero_3(MaxPower + 1);
	EXPECT_TRUE(zero_1 == zero_2);
	EXPECT_FALSE(zero_1 == zero_3);
	EXPECT_FALSE(test == zero_1);
}

TEST(SetTheoretic_Operations, Not_Equal) {
	int MaxPower = 20;
	TSet test(get_random_set(MaxPower));
	EXPECT_FALSE(test != test);
	MaxPower = 10;
	TSet zero_1(MaxPower);
	TSet zero_2(MaxPower);
	TSet zero_3(MaxPower + 1);
	EXPECT_FALSE(zero_1 != zero_2);
	EXPECT_TRUE(zero_1 != zero_3);
	EXPECT_TRUE(test != zero_1);
}

TEST(SetTheoretic_Operations, Assignment) {
	int MaxPower = 20;
	TSet test(get_random_set(MaxPower));
	MaxPower = 1;
	TSet zero(MaxPower);
	EXPECT_EQ(test, zero = test);
}

TEST(SetTheoretic_Operations, Self_Assignment) {
	int MaxPower = 20;
	TSet test(get_random_set(MaxPower));
	TSet test_before(test);
	EXPECT_EQ(test_before, test = test);
}

TEST(SetTheoretic_Operations, Union_With_Element) {
	int MaxPower = 20;
	uniform_int_distribution<> un(0, MaxPower - 1);
	default_random_engine re;
	TSet test1(MaxPower);
	int random_elem = un(re);
	TSet test2 = test1;
	test2.InsElem(random_elem);
	EXPECT_EQ(test2, test1 + random_elem);
	test1 = test1 + random_elem;
	EXPECT_EQ(test2, test1 + random_elem);
}

TEST(SetTheoretic_Operations, Difference_With_Element) {
	int MaxPower = 20;
	uniform_int_distribution<> un(0, MaxPower - 1);
	default_random_engine re;
	TSet test1(MaxPower);
	int random_elem = un(re);
	test1.InsElem(random_elem);
	TSet test2 = test1;
	test2.DelElem(random_elem);
	EXPECT_EQ(test2, test1 - random_elem);
	test1 = test1 - random_elem;
	EXPECT_EQ(test1, test1 - random_elem);
}

TEST(SetTheoretic_Operations, Union_With_Set) {
	uniform_int_distribution<> un(1, 1024);
	default_random_engine re;
	int MaxPower = un(re);
	TSet test1(get_random_set(MaxPower));
	TSet test2(get_random_set(MaxPower));
	TSet test_union(MaxPower);
	for (int i = 0; i < MaxPower; ++i) {
		if (test1.IsMember(i) || test2.IsMember(i)) {
			test_union.InsElem(i);
		}
	}
	EXPECT_EQ(test_union, test1 + test2);
}

TEST(SetTheoretic_Operations, Intersection) {
	uniform_int_distribution<> un(1, 1024);
	default_random_engine re;
	int MaxPower = un(re);
	TSet test1(get_random_set(MaxPower));
	TSet test2(get_random_set(MaxPower));
	TSet test_union(MaxPower);
	for (int i = 0; i < MaxPower; ++i) {
		if (test1.IsMember(i) && test2.IsMember(i)) {
			test_union.InsElem(i);
		}
	}
	EXPECT_EQ(test_union, test1 * test2);
}

TEST(SetTheoretic_Operations, Addition) {
	uniform_int_distribution<> un(1, 1024);
	default_random_engine re;
	int MaxPower = un(re);
	TSet test(get_random_set(MaxPower));
	TSet test_addition(MaxPower);
	for (int i = 0; i < MaxPower; ++i) {
		if (!test.IsMember(i)) {
			test_addition.InsElem(i);
		}
	}
	EXPECT_EQ(test_addition, ~test);
}

TEST(TSet_Input_Output, Output) {
	default_random_engine re;
	uniform_int_distribution<> un(1, 120);
	int MaxPower = un(re);
	TSet test_out(get_random_set(MaxPower));
	int Power = 0;
	string set_string = "{ ";
	for (int i = 0; i < MaxPower; ++i) {
		if (test_out.IsMember(i)) {
			set_string += std::to_string(i) + ", ";
		}
	}
	if (set_string.rfind(',') != set_string.npos) {
		set_string.erase(set_string.rfind(','), 1);
	}
	set_string += '}';
	ofstream ofstr("test.txt");
	ofstr << test_out;
	ofstr.close();
	ifstream ifstr("test.txt");
	string string_from_file;
	getline(ifstr, string_from_file);
	ifstr.close();
	EXPECT_EQ(set_string, string_from_file);
}

TEST(TSet_Input_Output, input) {
	default_random_engine re;
	uniform_int_distribution<> un(1, 120);
	int MaxPower = un(re);
	TSet test_from_file(MaxPower);
	TSet test_out(MaxPower);
	string set_string;
	un.param(uniform_int_distribution<>::param_type(0, 1));
	for (int i = 0; i < MaxPower; ++i) {
		if (un(re)) {
			set_string += std::to_string(i) + ' ';
			test_out.InsElem(i);
		}
	}
	if (set_string.length() != 0) {
		set_string.pop_back();
	}
	ofstream ofstr("test.txt");
	ofstr << set_string;
	ofstr.close();
	ifstream ifstr("test.txt");
	ifstr >> test_from_file;
	ifstr.close();
	EXPECT_EQ(test_out, test_from_file);
}

TEST(TSet_Exceptions_Test, SetTheoretic_Operations_invalid_argument) {
	uniform_int_distribution<> un(1, 10);
	default_random_engine re;
	int MaxPower = un(re);
	TSet set_1(get_random_set(MaxPower));
	TSet set_2(get_random_set(MaxPower + 1));
	EXPECT_THROW(set_1 + set_2, std::invalid_argument);
	EXPECT_THROW(set_1 * set_2, std::invalid_argument);
}