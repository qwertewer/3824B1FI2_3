#include "pch.h"
#include "TBitField.cpp"
#include "TSet.cpp"
//Проверка на исключения
TEST(TestExcept1, TestName_Init) {//Проверка инициализации
	EXPECT_ANY_THROW({
		int n = -1;
		TBitField T(n);
		});
	EXPECT_TRUE(true);
}

TEST(TestExcept2, TestName_Clr) {//Проверка функции ClrBit
	EXPECT_ANY_THROW({
		int n = 10;
		TBitField T(n);
		T.ClrBit(2 * n);
		});
	EXPECT_TRUE(true);
}

TEST(TestExcept3, TestName_Set) {//Проверка функции SetBit
	EXPECT_ANY_THROW({
		int n = 10;
		TBitField T(n);
		T.SetBit(2 * n);
		});
	EXPECT_TRUE(true);
}

TEST(TestExcept4, TestName_Get) { // Проверка функции GetBit
	EXPECT_ANY_THROW({
		int n = 10;
		TBitField T(n);
		T.GetBit(2 * n);
		});
	EXPECT_TRUE(true);
}

//Проверка на отсутствие исключений
TEST(TestNoExcept1, TestName_Init) {//Проверка инициализации
	EXPECT_NO_THROW({
		int n = 10;
		TBitField T(n);
		});
}

TEST(TestNoExcept2, TestName_Clr) {//Проверка функции ClrBit
	EXPECT_NO_THROW({
		int n = 10;
		TBitField T(n);
		T.ClrBit(n - 2);
		});
}

TEST(TestNoExcept3, TestName_Set) {//Проверка функции SetBit
	EXPECT_NO_THROW({
		int n = 10;
		TBitField T(n);
		T.SetBit(n - 2);
		});
}

TEST(TestNoExcept4, TestName_Get) {// Проверка функции GetBit
	EXPECT_NO_THROW({
		int n = 10;
		TBitField T(n);
		T.GetBit(n - 2);
		});
}

TEST(TestNoExcept5, TestNameCopyInit) {//Проверка конструктора копирования
	int n = 8;
	string s = "11110010";
	TBitField T(n);
	istringstream stream(s);
	stream >> T;
	TBitField B(T);
	EXPECT_EQ(B, T);
}

//Проверка на ввод
TEST(TestInput1, TestNameNoExcept) {//Корректный ввод
	int n = 8;
	string s = "11110010";
	istringstream stream(s);
	TBitField T(n);
	stream >> T;
}

TEST(TestInput2, TestNameExcept1) {//Некорректный ввод - содержит символы кроме 1 и 0
	EXPECT_ANY_THROW({
		int n = 8;
		string s = "11110021";
		istringstream stream(s);
		TBitField T(n);
		stream >> T;
		});
}

TEST(TestInput3, TestNameExcept2) {//Некорректный ввод - неправильная длина
	EXPECT_ANY_THROW({
		int n = 8;
		string s = "111100111001";
		istringstream stream(s);
		TBitField T(n);
		stream >> T;
		});
}

//Проверка операторов
//Оператор И
TEST(Test_And1, TestNameSameLengths) {//Строки равной длины
	int n = 8;
	string s = "11110011", s1 = "11101010", res = "11100010";
	istringstream stream(s), stream1(s1), Res(res);
	TBitField T(n), B(n), R(n);
	stream >> T;
	stream1 >> B;
	Res >> R;
	EXPECT_EQ(T & B, R);
}

TEST(Test_And2, TestNameDifferentLengths) {//Строки разной длины
	int n = 8;
	string s = "11110011", s1 = "0011101010", res = "0011100010";
	istringstream stream(s), stream1(s1), Res(res);
	TBitField T(n), B(n + 2), R(n + 2);
	stream >> T;
	stream1 >> B;
	Res >> R;
	EXPECT_EQ(T & B, R);
}

TEST(Test_And3, TestNameSameLengthsWrong) {//СТроки равной длины, но неправильный результат
	int n = 8;
	string s = "00000000", s1 = "11101010", res = "11100010";
	istringstream stream(s), stream1(s1), Res(res);
	TBitField T(n), B(n), R(n);
	stream >> T;
	stream1 >> B;
	Res >> R;
	EXPECT_FALSE((T & B) == R);
}

TEST(Test_And4, TestNameDifferentLengthsWrong) {//Строки разной длины, но неправильный результат
	int n = 8;
	string s = "11110011", s1 = "0011101010", res = "0010000010";
	istringstream stream(s), stream1(s1), Res(res);
	TBitField T(n), B(n + 2), R(n + 2);
	stream >> T;
	stream1 >> B;
	Res >> R;
	EXPECT_FALSE((T & B) == R);
}

TEST(Test_And5, TestNameDifferentLengths2) {//Строки разной длины
	int n = 5;
	string s = "10010", s1 = "0110000", res = "0010000";
	istringstream stream(s), stream1(s1), Res(res);
	TBitField T(n), B(n + 2), R(n + 2);
	stream >> T;
	stream1 >> B;
	Res >> R;
	EXPECT_EQ(T & B, R);
}

TEST(Test_And6, TestNameDifferentLengths3) {//Строки разной длины
	int n = 6;
	string s = "100101", s1 = "1000011100", res = "0000000100";
	istringstream stream(s), stream1(s1), Res(res);
	TBitField T(n), B(n + 4), R(n + 4);
	stream >> T;
	stream1 >> B;
	Res >> R;
	EXPECT_EQ(T & B, R);
}

TEST(Test_And7, TestNameDifferentLengths4) {//Строки разной длины
	int n = 7;
	string s = "1101100101", s1 = "1011001", res = "0001000001";
	istringstream stream(s), stream1(s1), Res(res);
	TBitField T(n+3), B(n), R(n + 3);
	stream >> T;
	stream1 >> B;
	Res >> R;
	EXPECT_EQ(T & B, R);
}

TEST(Test_And8, TestNameDifferentLengths5) {//Строки разной длины
	int n = 5;
	string s = "1101011101", s1 = "11001", res = "0000011001";
	istringstream stream(s), stream1(s1), Res(res);
	TBitField T(n + 5), B(n), R(n + 5);
	stream >> T;
	stream1 >> B;
	Res >> R;
	EXPECT_EQ(T & B, R);
}

//Побитовое ИЛИ
TEST(Test_Or1, TestNameSameLengthsOr) {//Строки равной длины
	int n = 8;
	string s = "11110000", s1 = "11001100", res = "11111100";
	istringstream stream(s), stream1(s1), Res(res);
	TBitField T(n), B(n), R(n);
	stream >> T;
	stream1 >> B;
	Res >> R;
	EXPECT_EQ(T | B, R);
}

TEST(Test_Or2, TestNameDifferentLengthsOr) {//Строки разной длины
	int n = 8;
	string s = "11000011", s1 = "1100110000", res = "1111110011";
	istringstream stream(s), stream1(s1), Res(res);
	TBitField T(n), B(n + 2), R(n + 2);
	stream >> T;
	stream1 >> B;
	Res >> R;
	EXPECT_EQ(T | B, R);
}

TEST(Test_Or3, TestNameSameLengthsWrongOr) {//СТроки равной длины, но неправильный результат
	int n = 8;
	string s = "11110000", s1 = "11001100", res = "00111100";
	istringstream stream(s), stream1(s1), Res(res);
	TBitField T(n), B(n), R(n);
	stream >> T;
	stream1 >> B;
	Res >> R;
	EXPECT_FALSE((T | B) == R);
}

TEST(Test_Or4, TestNameDifferentLengthsWrongOr) {//Строки разной длины, но неправильный результат
	int n = 8;
	string s = "11000011", s1 = "1100110000", res = "0011110011";
	istringstream stream(s), stream1(s1), Res(res);
	TBitField T(n), B(n + 2), R(n + 2);
	stream >> T;
	stream1 >> B;
	Res >> R;
	EXPECT_FALSE((T | B) == R);
}

TEST(Test_Or5, TestNameDifferentLengthsOr2) {//Строки разной длины
	int n = 6;
	string s = "110001", s1 = "10011101", res = "10111101";
	istringstream stream(s), stream1(s1), Res(res);
	TBitField T(n), B(n + 2), R(n + 2);
	stream >> T;
	stream1 >> B;
	Res >> R;
	EXPECT_EQ(T | B, R);
}

TEST(Test_Or6, TestNameDifferentLengthsOr3) {//Строки разной длины
	int n = 5;
	string s = "1110010001", s1 = "11101", res = "1110011101";
	istringstream stream(s), stream1(s1), Res(res);
	TBitField T(n+5), B(n), R(n + 5);
	stream >> T;
	stream1 >> B;
	Res >> R;
	EXPECT_EQ(T | B, R);
}

TEST(Test_Or7, TestNameDifferentLengthsOr4) {//Строки разной длины
	int n = 7;
	string s = "1000011011", s1 = "1100000", res = "1001111011";
	istringstream stream(s), stream1(s1), Res(res);
	TBitField T(n + 3), B(n), R(n + 3);
	stream >> T;
	stream1 >> B;
	Res >> R;
	EXPECT_EQ(T | B, R);
}

TEST(Test_Add1, TestName1) {//Отрицание
	int n = 8;
	string s = "11110000", s1 = "00001111";
	TBitField T(n), B(n);
	istringstream stream(s), stream1(s1);
	stream >> T;
	stream1 >> B;
	EXPECT_EQ(T, ~B);
}

TEST(Test_Add2, TestNameWrong) {//Отрицание, неправильный результат
	int n = 8;
	string s = "11110001", s1 = "00001111";
	TBitField T(n), B(n);
	istringstream stream(s), stream1(s1);
	stream >> T;
	stream1 >> B;
	EXPECT_FALSE(T == (~B));
}

//Проверка приравнивания
TEST(Test_Eq, TestNameEquating1) {
	int n = 8;
	string s = "11110001";
	TBitField T(n), B(n);
	istringstream stream(s);
	stream >> T;
	B = T;
	EXPECT_EQ(B, T);
}

TEST(Test_Eq2, TestNameEquating2) {//Самоприсваивание проходит корректно
	int n = 8;
	string s = "11110001";
	TBitField T(n), T_former(n);
	istringstream stream(s);
	stream >> T;
	T_former = T;
	T = T;
	EXPECT_EQ(T_former, T);
}

//Проверка равенства
TEST(Test_Are_Equal, TestNameEquation) {
	int n = 8;
	string s = "11110000", s1 = "11110000";
	TBitField T(n), B(n);
	istringstream stream(s), stream1(s1);
	EXPECT_EQ(T, B);
}

TEST(Test_Are_Equal2, TestNameEquation2) {
	int n = 10;
	string s = "1111001100", s1 = "1111001100";
	TBitField T(n), B(n);
	istringstream stream(s), stream1(s1);
	EXPECT_EQ(T, B);
}

//Проверка неравенства
TEST(Test_Are_UnEqual, TestNameUnEquation) {
	int n = 8;
	string s = "11110000", s1 = "11110011";
	TBitField T(n), B(n);
	istringstream stream(s), stream1(s1);
	stream >> T;
	stream1 >> B;
	EXPECT_TRUE(T != B);
}

//Тесты с множествами, Инициализация
TEST(Test_Set1, TestInit) {
	EXPECT_NO_THROW({
		int n = 10;
		TSet S(n);
		});
}

TEST(Test_Set2, TestInitException) {
	EXPECT_ANY_THROW({
		int n = -1;
		TSet S(n);
		});
}

//Функции
TEST(Test_Set3, TestExceptionInsElem) {
	int n = 10;
	TSet S(n);
	EXPECT_ANY_THROW({
		S.InsElem(2 * n);
		});
}

TEST(Test_Set4, TestExceptionDelElem) {
	int n = 10;
	TSet S(n);
	EXPECT_ANY_THROW({
		S.DelElem(2 * n);
		});
}

TEST(Test_Set5, TestExceptionIsMember) {
	int n = 10;
	TSet S(n);
	EXPECT_ANY_THROW({
		S.IsMember(2 * n);
		});
}

TEST(Test_Set6, TestCopy) {
	int n = 8;
	string s = "11110000";
	TBitField T(n);
	istringstream stream(s);
	stream >> T;
	TSet S(T);
	TSet M(S);
	EXPECT_EQ(S, M);
}

//Проверка на сравнения
TEST(Test_Cmp1, TestEquating) {
	int n = 8;
	string s = "11110000";
	TBitField T(n);
	istringstream stream(s);
	stream >> T;
	TSet S(n), B(T);
	S = B;
	EXPECT_EQ(S, B);
}

TEST(Test_Cmp2, TestEquation) {
	int n = 8;
	string s = "11110000";
	TBitField T(n);
	istringstream stream(s);
	stream >> T;
	TSet S(T), B(T);
	EXPECT_EQ(S, B);
}

//Проверка операций
TEST(Test_Oper1, Test_Add) {
	int n = 8;
	string s = "11110000", s1 = "11110100";
	TBitField T(n), B(n);
	istringstream stream(s), stream1(s1);
	stream >> T;
	stream1 >> B;
	TSet S(T), S1(B);
	S = S + 2;
	EXPECT_EQ(S, S1);
}

TEST(Test_Oper2, Test_Sub) {
	int n = 8;
	string s = "11110100", s1 = "11110000";
	TBitField T(n), B(n);
	istringstream stream(s), stream1(s1);
	stream >> T;
	stream1 >> B;
	TSet S(T), S1(B);
	S = S - 2;
	EXPECT_EQ(S, S1);
}

TEST(Test_Oper3, Test_Unify) {
	int n = 8;
	string s = "11110000", s1 = "00001111", s2 = "11111111";
	TBitField T(n), B(n), F(n);
	istringstream stream(s), stream1(s1), stream2(s2);
	stream >> T;
	stream1 >> B;
	stream2 >> F;
	TSet S(T), S1(B), S2(F);
	EXPECT_EQ((S + S1), S2);
}

TEST(Test_Oper4, Test_Cross) {
	int n = 8;
	string s = "11110000", s1 = "00001111", s2 = "00000000";
	TBitField T(n), B(n), F(n);
	istringstream stream(s), stream1(s1), stream2(s2);
	stream >> T;
	stream1 >> B;
	stream2 >> F;
	TSet S(T), S1(B), S2(F);
	EXPECT_EQ((S * S1), S2);
}

TEST(Test_Oper5, Test_Not_Set) {
	int n = 8;
	string s = "10101010", s1 = "01010101";
	TBitField T(n), B(n);
	istringstream stream(s), stream1(s1);
	stream >> T;
	stream1 >> B;
	TSet S(T), S1(B);
	EXPECT_EQ((~S), S1);
}