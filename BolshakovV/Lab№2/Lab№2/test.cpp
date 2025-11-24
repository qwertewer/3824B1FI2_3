#include "pch.h"
#include "../Project1/UTMATRIX.h"

TEST(TVector_test_0, constructor_default) { //проверка установки значений по умолчанию
	TVector<int> vec;
	EXPECT_EQ(vec.GetSize(), 10);
	EXPECT_EQ(vec.GetStartIndex(), 0);
}

TEST(TVector_test_0, constructor_default_0) { //проверка установки значений элементов
	TVector<int> vec(10, 0);
	for (size_t i = 0; i < vec.GetSize(); ++i) {
		EXPECT_EQ(vec[i], 0); 
	}
}

TEST(TVector_test_0, constructor_1) { //установка собственных значений
	TVector<double> vec(15, 6);
	EXPECT_EQ(vec.GetSize(), 15);
	EXPECT_EQ(vec.GetStartIndex(), 6); 
}

TEST(TVector_test_0, constructor_2) { //установка некорректных значений 
	try {
		TVector<float>vec(0, 5);
	}
	catch (const std::invalid_argument& a) {
		EXPECT_STREQ(a.what(), "Error. Incorrect size");
	}
}

TEST(TVector_test_0, constructor_2_1) {
	try {
		TVector<char>vec(MAX_VECTOR_SIZE + 1, 5);
	}
	catch (const std::invalid_argument& a) {
		EXPECT_STREQ(a.what(), "Error. Incorrect size");
	}
}

TEST(TVector_test_0, constructor_2_2) {
	try {
		TVector<char>vec(10, -1);
	}
	catch (const std::invalid_argument& a) {
		EXPECT_STREQ(a.what(), "Error. Incorrect start_index");
	}
}

TEST(TVector_test_0, constructor_2_3) {
	try {
		TVector<std::string>vec(MAX_VECTOR_SIZE, MAX_VECTOR_SIZE);
	}
	catch (const std::invalid_argument& a) {
		EXPECT_STREQ(a.what(), "Error. Incorrect start_index");
	}
}

TEST(TVector_test_0, constructor_big_size) {
	TVector<int>vec(MAX_VECTOR_SIZE);
}
////////
TEST(TVector_test0_0, access_0) { //оператор индексации
	TVector<int> vec(3, 0);
	vec[0] = 1;
	vec[1] = 4;
	EXPECT_EQ(vec[0], 1);
	EXPECT_EQ(vec[1], 4);
}

TEST(TVector_test0_0, access_1) {
	TVector<int> vec(2, 1);
	vec[1] = 5;
	EXPECT_EQ(vec[1], 5);
}

TEST(TVector_test0_0, access_2) { //исключение
	TVector<int> vec(2, 0);
	ASSERT_THROW({ vec[3]; }, std::out_of_range);
}

TEST(TVector_test0_0, access_2_1) { //раньше стартового индекса
	TVector<int>vec(2, 1);
	try {
		vec[0] = 7;
	}
	catch (const std::out_of_range& a) {
		EXPECT_STREQ(a.what(), "Incorrect index");
	}
}

TEST(TVector_test0_0, access_3) { //тип string
	TVector<std::string>vec(2, 0);
	vec[0] = "AA";
	vec[1] = "BBC";
	EXPECT_EQ(vec[0], "AA");
	EXPECT_EQ(vec[1], "BBC");
}

TEST(TVector_test0_0, access_4) { //изменение значения
	TVector<int>vec(2, 1);
	vec[1] = 10;
	vec[1] = 11;
	EXPECT_EQ(vec[1], 11);
}

TEST(TVector_test0_0, access_5) {
	TVector<int>vec(10, 7);
	vec[7] = 5;
	vec[8] = 6;
	EXPECT_EQ(vec[7], 5);
	EXPECT_EQ(vec[8], 6);
	try {
		vec[10] = 18;
	}
	catch (const std::out_of_range& a) {
		EXPECT_STREQ(a.what(), "Incorrect index");
	}
}
///////////
TEST(TVector_test_0, constructor_copy) { //конструктор копирования

	TVector<int>vec(2, 0);
	vec[0] = 67;
	vec[1] = 78;
	TVector<int>vec1(vec);
	EXPECT_EQ(vec1.GetSize(), 2);
	EXPECT_EQ(vec1.GetStartIndex(), 0);
	EXPECT_EQ(vec1[0], 67);
	EXPECT_EQ(vec1[1], 78);
}

TEST(TVector_test_0, constructor_copy_1) { //большой размер
	TVector<int>vec(1000, 0);
	for (size_t i = 0; i < vec.GetSize(); ++i) {
		vec[i] = i;
	}

	TVector<int>vec1(vec);
	EXPECT_EQ(vec1.GetSize(), 1000);
	EXPECT_EQ(vec1.GetStartIndex(), 0);
	for (size_t i = 0; i < vec1.GetSize(); ++i) {
		EXPECT_EQ(vec1[i], i);
	}
}

TEST(TVector_test_0, constructor_copy_2) { //изменение vec1 не приводит к изменению vec
	TVector<int>vec(2, 0);
	vec[0] = 67;
	vec[1] = 78;
	TVector<int>vec1(vec);
	vec1[0] = 69;
	EXPECT_EQ(vec[0], 67);
}
//////////
TEST(TVector_test_1, operator_eq) { // оператор ==
	TVector<double>vec(2, 0);
	vec[0] = 3.4;
	vec[1] = 5.6;

	TVector<double>vec1(2, 0);
	vec1[0] = 3.4;
	vec1[1] = 5.6;
	EXPECT_TRUE(vec == vec1);
}

TEST(TVector_test_1, operator_eq_1) { //разные размеры
	TVector<int>vec(2, 0);
	TVector<int>vec1(3, 0);
	EXPECT_FALSE(vec == vec1);
}

TEST(TVector_test_1, operator_eq_1_1) {
	TVector<double>vec(8, 2);
	vec[2] = 0.0;
	vec[3] = 0.0;
	vec[4] = 0.0;
	vec[5] = 1.0;
	vec[6] = 2.5;
	vec[7] = 2.4;

	TVector<double>vec1(8, 5);
	vec1[5] = 1.0;
	vec1[6] = 2.5;
	vec1[7] = 2.4;

	EXPECT_TRUE(vec == vec1);
}

TEST(TVector_test_1, operator_eq_1_2) {
	TVector<double>vec(8, 2);
	vec[2] = 0.0;
	vec[3] = 0.0;
	vec[4] = 0.0;
	vec[5] = 1.0;
	vec[6] = 2.5;
	vec[7] = 2.4;

	TVector<double>vec1(8, 5);
	vec1[5] = 1.0;
	vec1[6] = 2.5;
	vec1[7] = 2.4;

	EXPECT_TRUE(vec1 == vec);
}

TEST(TVector_test_1, operator_eq_1_3) {
	TVector<double>vec(8, 2);
	vec[2] = 0.0;
	vec[3] = 1.0;
	vec[4] = 0.0;
	vec[5] = 1.0;
	vec[6] = 2.5;
	vec[7] = 2.4;

	TVector<double>vec1(8, 5);
	vec1[5] = 1.0;
	vec1[6] = 2.5;
	vec1[7] = 2.4;

	EXPECT_FALSE(vec == vec1);
}

///////////
TEST(TVector_test_1, operator_not_eq) { //оператор !=
	TVector<int>vec(2, 1);
	TVector<int>vec1(3, 1);
	EXPECT_TRUE(vec != vec1);
}


TEST(TVector_test_1, operator_not_eq_1) { //разные значения
	TVector<int>vec(2, 0);
	vec[0] = 4;
	vec[1] = 678;

	TVector<int>vec1(2, 0);
	vec1[0] = 4;
	EXPECT_TRUE(vec != vec1);
}

TEST(TVector_test_1, operator_not_eq_2) { //одинаковые векторы
	TVector<int>vec(2, 1);
	TVector<int>vec1(2, 1);
	EXPECT_FALSE(vec != vec1);
}
///////////
TEST(TVector_test_1, operator_assign) { //оператор присваивания 
	TVector<int> vec(3, 0);
	TVector<int> vec1;
	vec1 = vec;
	EXPECT_TRUE(vec1 == vec);
}

TEST(TVector_test_1, operator_assign_1) {
	TVector<int> vec(3, 0);
	vec[0] = 23;
	vec[1] = 14;

	TVector<int> vec1;
	vec1[0] = 45;
	vec1[1] = 14;
	vec1 = vec;
	EXPECT_TRUE(vec1 == vec);
}

TEST(TVector_test_1, operator_assign_2) { //несколько присваиваний подряд
	TVector<double> vec(3, 0);
	TVector<double> vec1(4, 3);
	TVector<double> vec3(2, 1);
	vec3[1] = 56.7;
	vec = vec1 = vec3;
	EXPECT_TRUE(vec1 == vec3);
	EXPECT_TRUE(vec == vec1);
}

TEST(TVector_test_1, operator_assign_3) { //самоприсваивание
	TVector<float> vec(3, 0);
	vec[0] = 45.3f;
	vec = vec;

	EXPECT_NEAR(vec[0], 45.3f, 0.0001); //при использовании float просто EXPECT_EQ выдает ошибку
	EXPECT_EQ(vec.GetSize(), 3);
	EXPECT_EQ(vec.GetStartIndex(), 0);
}
////////////
//скалярные операции
TEST(TVector_test_2, sum) { //int
	TVector<int>vec(2, 0);
	vec[0] = 2;
	vec[1] = 3;
	vec = vec + 1;
	EXPECT_EQ(vec[0], 3);
	EXPECT_EQ(vec[1], 4);
	EXPECT_EQ(vec.GetSize(), 2);
	EXPECT_EQ(vec.GetStartIndex(), 0);
}

TEST(TVector_test_2, sum_1) { //double
	TVector<double>vec(2, 0);
	vec[0] = 1.5;
	vec[1] = 2.5;
	vec = vec + 1.5;
	EXPECT_EQ(vec[0], 3.0);
	EXPECT_EQ(vec[1], 4.0);
}

TEST(TVector_test_2, sum_1_1) { //std::string
	TVector<std::string>vec(1, 0);
	vec[0] = "A";
	vec = vec + "B";
	EXPECT_EQ(vec[0], "AB");
}

TEST(TVector_test_2, sum_2) { //переполнение
	TVector<int>vec(1, 0);
	vec[0] = INT_MAX;
	vec = vec + 1;
	EXPECT_EQ(vec[0], INT_MIN);
}
TEST(TVector_test2, sum_3) {
	TVector<int>vec(3, 1);
	vec[1] = 4;
	vec[2] = 56;
	vec = vec + 1;
	EXPECT_EQ(vec[1], 5);
	EXPECT_EQ(vec[2], 57);

}

///////////
TEST(TVector_test2, diff) { //вычесть скаляр
	TVector<int> vec(2, 0);
	vec[0] = 4;
	vec[1] = 3;
	vec = vec - 1;
	EXPECT_EQ(vec[0], 3);
	EXPECT_EQ(vec[1], 2);
}

TEST(TVector_test2, diff_1) {
	TVector<double>vec(2, 0);
	vec[0] = 2.5;
	vec[1] = 3.5;
	vec = vec - 1.5;
	EXPECT_EQ(vec[0], 1.0);
	EXPECT_EQ(vec[1], 2.0);
}

TEST(TVector_test2, diff_1_1) {
	TVector<int>vec(1, 0);
	vec[0] = 2;
	vec = vec - 1.5;
	EXPECT_EQ(vec[0], 1);
}

TEST(TVector_test2, diff_2) {
	TVector<int>vec(1, 0);
	vec[0] = INT_MIN;
	vec = vec - 1;
	EXPECT_EQ(vec[0], INT_MAX);
}
///////////
TEST(TVector_test2, multip) { //умножить на скаляр
	TVector<int>vec(2, 0);
	vec[1] = 1;
	vec = vec * 2;
	EXPECT_EQ(vec[0], 0);
	EXPECT_EQ(vec[1], 2);
}
TEST(TVector_test2, multip_1) { //разный тип вектора и скаляра
	TVector<int>vec(1, 0);
	vec[0] = 2;
	vec = vec * 1.5;
	EXPECT_EQ(vec[0], 2);
}
//////////
TEST(TVector_test3, SUM) {
	TVector<int>vec(2, 0);
	vec[0] = 1;
	vec[1] = 2;
	TVector<int>vec1(2, 0);
	vec1[0] = -1;
	vec1[1] = 4;
	vec1 = vec + vec1;
	EXPECT_EQ(vec1[0], 0);
	EXPECT_EQ(vec1[1], 6);
}

TEST(TVector_test3, SUM_01) {
	TVector<int>vec(5, 2);
	vec[2] = 1;
	vec[3] = 2;
	vec[4] = 3;
	TVector<int>vec1(5, 3);
	vec1[3] = 1;
	vec1[4] = 1;
	TVector<int>vec2 = vec + vec1;
	EXPECT_EQ(vec2.GetSize(), 5);
	EXPECT_EQ(vec2.GetStartIndex(), 2);
	EXPECT_EQ(vec2[2], 1);
	EXPECT_EQ(vec2[3], 3);
	EXPECT_EQ(vec2[4], 4);
}

TEST(TVector_test3, SUM_02) {
	TVector<int>vec(5, 4);
	vec[4] = 1;
	TVector<int>vec1(5, 2);
	vec1[2] = 1;
	vec1[3] = 2;
	vec1[4] = 3;
	TVector<int>vec2 = vec + vec1;
	EXPECT_EQ(vec2.GetSize(), 5);
	EXPECT_EQ(vec2.GetStartIndex(), 2);
	EXPECT_EQ(vec2[2], 1);
	EXPECT_EQ(vec2[3], 2);
	EXPECT_EQ(vec2[4], 4);
}

TEST(TVector_test3, SUM_1) {
	TVector<int>vec(2, 0);
	vec[0] = 3;
	TVector<int>vec1(1, 0);
	vec1[0] = 4;
	try {
		vec = vec + vec1;
	}
	catch (const std::runtime_error& a) {
		EXPECT_STREQ(a.what(), "The vectors have different sizes");
	}
}
/////////
TEST(TVector_test3, DIFF) {
	TVector<double>vec(2, 0);
	vec[0] = 1.5;
	TVector<double>vec1(2, 0);
	vec1[0] = 2.5;
	vec1 = vec1 - vec;
	EXPECT_EQ(vec1[0], 1.0);
	EXPECT_EQ(vec1[1], 0.0);
	EXPECT_EQ(vec[0], 1.5);
}

TEST(TVector_test3, DIFF_01) {
	TVector<int>vec(7, 3);
	vec[3] = 1;
	vec[4] = 2;
	vec[5] = 3;
	vec[6] = 8;
	TVector<int>vec1(7, 1);
	vec1[1] = 2;
	vec1[2] = 3;
	vec1[3] = 4;
	vec1[4] = 5;
	vec1[5] = 6;
	vec1[6] = 7;

	TVector<int>vec2 = vec - vec1;
	EXPECT_EQ(vec2.GetSize(), 7);
	EXPECT_EQ(vec2.GetStartIndex(), 1);
	EXPECT_EQ(vec2[1], -2);
	EXPECT_EQ(vec2[2], -3);
	EXPECT_EQ(vec2[3], -3);
	EXPECT_EQ(vec2[4], -3);
	EXPECT_EQ(vec2[5], -3);
	EXPECT_EQ(vec2[6], 1);
}


TEST(TVector_test3, DIFF_02) {
	TVector<int>vec(7, 1);
	vec[1] = 2;
	vec[2] = 3;
	vec[3] = 4;
	vec[4] = 5;
	vec[5] = 6;
	vec[6] = 7;

	TVector<int>vec1(7, 3);
	vec1[3] = 1;
	vec1[4] = 2;
	vec1[5] = 3;
	vec1[6] = 8;

	TVector<int>vec2 = vec - vec1;
	EXPECT_EQ(vec2.GetSize(), 7);
	EXPECT_EQ(vec2.GetStartIndex(), 1);
	EXPECT_EQ(vec2[1], 2);
	EXPECT_EQ(vec2[2], 3);
	EXPECT_EQ(vec2[3], 3);
	EXPECT_EQ(vec2[4], 3);
	EXPECT_EQ(vec2[5], 3);
	EXPECT_EQ(vec2[6], -1);
}

TEST(TVector_test3, DIFF_1) { //разный размер
	TVector<int>vec(2, 0);
	TVector<int>vec1(3, 0);
	try {
		vec1 = vec1 - vec;
	}
	catch (const std::runtime_error& a) {
		EXPECT_STREQ(a.what(), "The vectors have different sizes");
	}
}

/////////
TEST(TVector_test3, composition) {
	TVector<int>vec(3, 0);
	TVector<int>vec1(3, 0);
	vec[0] = 1;
	vec[1] = 2;
	vec[2] = 3;

	vec1[0] = 2;
	vec1[1] = 3;
	vec1[2] = 4;

	int m = vec * vec1;
	EXPECT_EQ(m, 20);
}

TEST(TVector_test3, composition_01) {
	TVector<int>vec(7, 1);
	vec[1] = 1;
	vec[2] = 1;
	vec[3] = 1;
	vec[4] = 1;
	vec[5] = 1;
	vec[6] = 7;

	TVector<int>vec1(7, 3);
	vec1[3] = 1;
	vec1[4] = 2;
	vec1[5] = 3;
	vec1[6] = 8;

	int res = vec * vec1;
	EXPECT_EQ(res, 62);
}

TEST(TVector_test3, composition_02) {

	TVector<int>vec(7, 3);
	vec[3] = 1;
	vec[4] = 2;
	vec[5] = 3;
	vec[6] = 8;

	TVector<int>vec1(7, 1);
	vec1[1] = 1;
	vec1[2] = 1;
	vec1[3] = 1;
	vec1[4] = 1;
	vec1[5] = 1;
	vec1[6] = 7;

	int res = vec * vec1;
	EXPECT_EQ(res, 62);
}

TEST(TVector_test3, composition_1) {
	TVector<int>vec(3, 0);
	TVector<int>vec1(3, 0);
	vec[0] = 1;
	vec[1] = 2;
	vec[2] = 3;

	vec1[0] = 2;
	vec1[1] = 3;
	vec1[2] = 4;

	float m = vec * vec1;  //переменная типа float, double
	double m1 = vec * vec1;
	EXPECT_EQ(m, 20);
	EXPECT_EQ(m1, 20);
}

TEST(TVector_test3, composition_2) {
	TVector<double>vec(2, 0);
	TVector<double>vec1(2, 0);
	vec[0] = 1.5;
	vec[1] = 2;

	vec1[0] = 2.4;
	vec1[1] = 3.5;

	double res1 = vec * vec1; //тип векторов double, проверка результатов double, float, int
	float res2 = vec * vec1;
	int res3 = vec * vec1;
	EXPECT_EQ(res1, 10.6);
	EXPECT_EQ(res2, 10.6f);
	EXPECT_EQ(res3, 10);
}

TEST(TVector_test3, composition_3) {
	TVector<int>vec(2, 0);
	TVector<int>vec1(3, 0);

	try {
		int m = vec * vec1;
	}
	catch (const std::runtime_error& a) {
		EXPECT_STREQ(a.what(), "The vectors have different sizes");
	}
}
//////////
TEST(TVector_test4, Oper_input) {
	TVector<int> vec(4, 0);
	vec[0] = 1;
	vec[1] = 1;
	vec[2] = 1;
	vec[3] = 1;

	std::istringstream in("2 3 4 5");
	in >> vec;
	EXPECT_EQ(vec.GetSize(), 4);
	EXPECT_EQ(vec.GetStartIndex(), 0);
	EXPECT_EQ(vec[0], 2);
	EXPECT_EQ(vec[1], 3);
	EXPECT_EQ(vec[2], 4);
	EXPECT_EQ(vec[3], 5);
}

TEST(TVector_test4, Oper_input_1) {
	TVector<int> vec(4, 0);
	vec[0] = 1;
	vec[1] = 1;
	vec[2] = 1;
	vec[3] = 1;

	std::istringstream in("2,3 4 5");
	try {
		in >> vec;
	}
	catch (const std::invalid_argument& a) {
		EXPECT_STREQ(a.what(), "Incorrect input");
	}
}

TEST(TVector_test4, Oper_input_2) {
	TVector<int> vec(4, 0);
	vec[0] = 1;
	vec[1] = 1;
	vec[2] = 1;
	vec[3] = 1;

	std::istringstream in("2 3.67 4 5");
	try {
		in >> vec;
	}
	catch (const std::invalid_argument& a) {
		EXPECT_STREQ(a.what(), "Incorrect input");
	}

	EXPECT_EQ(vec[0], 1);
	EXPECT_EQ(vec[1], 1);
	EXPECT_EQ(vec[2], 1);
	EXPECT_EQ(vec[3], 1);
}

TEST(TVector_test4, Oper_input_3) {
	TVector<int> vec(4, 0);
	vec[0] = 1;
	vec[1] = 1;
	vec[2] = 1;
	vec[3] = 1;

	std::istringstream in("2 3 4 5 6 a");
	in >> vec;

	EXPECT_EQ(vec[0], 2);
	EXPECT_EQ(vec[1], 3);
	EXPECT_EQ(vec[2], 4);
	EXPECT_EQ(vec[3], 5);
}

TEST(TVector_test4, Oper_input_4) {
	TVector<int> vec(4, 1);
	vec[1] = 1;
	vec[2] = 1;
	vec[3] = 1;

	std::istringstream in("2 3 4 5 6 a");
	in >> vec;

	EXPECT_EQ(vec[1], 2);
	EXPECT_EQ(vec[2], 3);
	EXPECT_EQ(vec[3], 4);
}

TEST(TVector_test4, Oper_input_5) {
	TVector<int> vec(4, 1);
	vec[1] = 1;
	vec[2] = 1;
	vec[3] = 1;

	std::istringstream in("2");
	ASSERT_THROW({ in >> vec; }, std::invalid_argument);
}

TEST(TVector_test4, Oper_input_6) {
	TVector<int> vec(3, 0);
	TVector<int>vec1(2, 0);
	std::istringstream in("1 2 3 1 2");
	in >> vec >> vec1;
	EXPECT_EQ(vec[0], 1);
	EXPECT_EQ(vec[1], 2);
	EXPECT_EQ(vec[2], 3);

	EXPECT_EQ(vec1[0], 1);
	EXPECT_EQ(vec1[1], 2);
}
//////////
TEST(TVector_test4, Oper_output) {
	TVector<int>vec(3, 0);
	vec[0] = 2;
	vec[1] = 6;
	vec[2] = 89;
	std::ostringstream out;
	out << vec;
	EXPECT_EQ(out.str(), "2 6 89");
}


TEST(TVector_test4, Oper_output_1) {
	TVector<int>vec(6, 3);
	vec[3] = 1;
	vec[4] = 4;
	vec[5] = 6;

	std::ostringstream out;
	out << vec;
	EXPECT_EQ(out.str(), "0 0 0 1 4 6");
}

TEST(TVector_test4, Oper_output_2) {

	TVector<int>vec(3, 0);
	vec[0] = 2;
	vec[1] = 6;
	vec[2] = 89;

	TVector<double>vec1(3, 0); 
	vec1[0] = 4.48;
	vec1[1] = -1.5; 
	vec1[2] = -67.39;

	TVector<std::string>vec2(4, 0);
	vec2[0] = "A";
	vec2[1] = "B";
	vec2[2] = "C";
	vec2[3] = "D";

	std::ostringstream out;
	out << vec << "| " << vec1 << "| " << vec2;
	EXPECT_EQ(out.str(), "2 6 89| 4.48 -1.5 -67.39| A B C D");
}

//////////////
TEST(TMatrix_test1, contructor) {
	TMatrix<int> mat;

	EXPECT_EQ(mat.GetSize(), 10);
}

TEST(TMatrix_test1, contructor_1) {
	TMatrix<int> mat(3);

	EXPECT_EQ(mat.GetSize(), 3);

	EXPECT_EQ(mat[0].GetStartIndex(), 0);
	EXPECT_EQ(mat[1].GetStartIndex(), 1);
	EXPECT_EQ(mat[2].GetStartIndex(), 2);

	EXPECT_EQ(mat[0].GetSize(), 3);
	EXPECT_EQ(mat[1].GetSize(), 3);
	EXPECT_EQ(mat[2].GetSize(), 3);
}

TEST(TMatrix_test1, constructor_1_1) {
	TMatrix<int>mat(2);

	for (size_t i = 0; i < mat.GetSize(); ++i) {
		for (size_t j = mat[i].GetStartIndex(); j < mat[i].GetSize(); ++j) {
			EXPECT_EQ(mat[i][j], 0);
		}
	}
}

TEST(TMatrix_test1, constructor_2) {
	try {
		TMatrix<double>mat(0);
	}
	catch (const std::invalid_argument& a) {
		EXPECT_STREQ(a.what(), "Error. Incorrect size");
	}
}

TEST(TMatrix_test1, constructor_3) {
	try {
		TMatrix<double>mat(MAX_MATRIX_SIZE + 1);
	}
	catch (const std::invalid_argument& a) {
		EXPECT_STREQ(a.what(), "Invalid matrix size");
	}
}

TEST(TMatrix_test1, constructor_big_size) {
	TMatrix<int>mat(MAX_MATRIX_SIZE);
}
/////////
TEST(TMatrix_test1, constructor_copy) {
	TMatrix<int>mat(3);

	mat[0][0] = 1;
	mat[0][1] = 2;
	mat[0][2] = 3;

	mat[1][1] = 1;
	mat[1][2] = 3;

	mat[2][2] = 4;
	TMatrix<int>mat2(mat);
	EXPECT_EQ(mat2.GetSize(), mat.GetSize());
	EXPECT_EQ(mat2[0].GetStartIndex(), mat[0].GetStartIndex());
	EXPECT_EQ(mat2[1].GetStartIndex(), mat[1].GetStartIndex());
	EXPECT_EQ(mat2[2].GetStartIndex(), mat[2].GetStartIndex());
	for (size_t i = 0; i < mat.GetSize(); ++i) {
		for (size_t j = mat[i].GetStartIndex(); j < mat[i].GetSize(); ++j) {
			EXPECT_EQ(mat2[i][j], mat[i][j]);
		}
	}
}

TEST(TMatrix_test1, constructor_copy_1) {
	TMatrix<int>mat(2);
	mat[0][0] = 1;
	mat[0][1] = 2;
	mat[1][1] = 3;

	TMatrix<int>mat2(mat);

	mat2[1][1] = 4;
	EXPECT_EQ(mat[1][1], 3);
}
///////////////
TEST(TMatrix_test1, transform) {
	int size = 2;
	TVector<TVector<int>>vec(size);
	for (size_t i = 0; i < size; ++i) {
		vec[i] = TVector<int>(size, i);
	}

	vec[0][0] = 1;
	vec[0][1] = 2;
	vec[1][1] = 3;

	TMatrix<int>mat(vec);
	EXPECT_EQ(mat.GetSize(), 2);
	EXPECT_EQ(mat[0].GetStartIndex(), 0);
	EXPECT_EQ(mat[1].GetStartIndex(), 1);

	EXPECT_EQ(mat[0][0], 1);
	EXPECT_EQ(mat[0][1], 2);
	EXPECT_EQ(mat[1][1], 3);
}

TEST(TMatrix_test1, transform_1) {
	int size = 2;
	TVector<TVector<int>>vec(size);
	for (size_t i = 0; i < size; ++i) {
		vec[i] = TVector<int>(size, 0);
	}

	try {
		TMatrix<int>mat(vec);
	}
	catch (const std::runtime_error& a) {
		EXPECT_STREQ(a.what(), "Matching of the starting indexes");
	}
}

TEST(TMatrix_test1, transform_2) {
	int size = MAX_MATRIX_SIZE + 1;
	TVector<TVector<int>>vec(size);
	for (int i = 0; i < size; ++i) {
		vec[i] = TVector<int>(size, i);
	}

	try {
		TMatrix<int>mat(vec);
	}
	catch (const std::invalid_argument& a) {
		EXPECT_STREQ(a.what(), "Invalid matrix size");
	}
}

TEST(TMatrix_test1, transform_3) {
	TVector<TVector<int>>vec(4, 1);
	for (int i = 1; i < 4; ++i) {
		vec[i] = TVector<int>(4, i);
	}

	try {
		TMatrix<int>mat(vec);
	}
	catch (const std::invalid_argument& a) {
		EXPECT_STREQ(a.what(), "Error. The starting index of the vector of vectors should be 0");
	}
}
///////////
TEST(TMatrix_test2, oper_eq) {
	TMatrix<int>mat1(3);
	TMatrix<int>mat2(3);

	mat1[0][0] = 1; mat1[0][1] = 2; mat1[0][2] = 3;
	mat1[1][1] = 3; mat1[1][2] = 4;
	mat1[2][2] = 0;

	mat2[0][0] = 1; mat2[0][1] = 2; mat2[0][2] = 3;
	mat2[1][1] = 3; mat2[1][2] = 4;
	mat2[2][2] = 0;

	EXPECT_TRUE(mat1 == mat2);

}

TEST(TMatrix_test2, oper_eq_1) {
	TMatrix<double>mat1(3);
	TMatrix<double>mat2(2);
	EXPECT_FALSE(mat1 == mat2);
}

TEST(TMatix_test2, oper_eq_2) {
	TMatrix<int>mat1(3);
	TMatrix<int>mat2(3);

	mat1[0][0] = 1; mat1[0][1] = 8; mat1[0][2] = 3;
	mat1[1][1] = 3; mat1[1][2] = 4;
	mat1[2][2] = 0;

	mat2[0][0] = 1; mat2[0][1] = 2; mat2[0][2] = 3;
	mat2[1][1] = 3; mat2[1][2] = 4;
	mat2[2][2] = 0;

	EXPECT_FALSE(mat1 == mat2);
}
///////////
TEST(TMatrix_test2, oper_not_eq) {
	TMatrix<double>mat1(3);
	TMatrix<double>mat2(2);
	EXPECT_TRUE(mat1 != mat2);
}

TEST(TMatrix_test2, oper_not_eq_1) {
	TMatrix<int>mat1(3);
	TMatrix<int>mat2(3);

	mat1[0][0] = 1; mat1[0][1] = 8; mat1[0][2] = 3;
	mat1[1][1] = 3; mat1[1][2] = 4;
	mat1[2][2] = 0;

	mat2[0][0] = 1; mat2[0][1] = 2; mat2[0][2] = 3;
	mat2[1][1] = 3; mat2[1][2] = 4;
	mat2[2][2] = 0;

	EXPECT_TRUE(mat1 != mat2);
}

TEST(TMatrix_test2, oper_not_eq_2) {
	TMatrix<float>mat1(2);
	TMatrix<float>mat2(2);
	EXPECT_FALSE(mat1 != mat2);
}
////////////
TEST(TMatrix_test2, oper_assign) {
	TMatrix<int>mat1(2);
	mat1[0][0] = 1;
	mat1[0][1] = 1;
	mat1[1][1] = 2;

	TMatrix<int>mat2(1);
	mat2[0][0] = 4;
	mat2 = mat1;
	EXPECT_EQ(mat2.GetSize(), 2);
	EXPECT_TRUE(mat2 == mat1);
}

TEST(TMatrix_test2, oper_assign_1) { //изменение второго объекта не приводит к изменению первого
	TMatrix<int>mat1(2);
	mat1[0][0] = 1;
	mat1[0][1] = 1;
	mat1[1][1] = 2;

	TMatrix<int>mat2(1);
	mat2[0][0] = 4;
	mat2 = mat1;
	EXPECT_EQ(mat2.GetSize(), 2);
	mat2[0][0] = 9;
	mat2[0][1] = 4;
	mat2[1][1] = 89;
	EXPECT_EQ(mat1[0][0], 1);
}

TEST(TMatrix_test2, oper_assign_2) { //несколько операций подряд
	TMatrix<int>mat1(2);
	mat1[0][0] = 1;
	mat1[0][1] = 1;
	mat1[1][1] = 2;

	TMatrix<int>mat2(1);
	TMatrix<int>mat3(8);
	mat3 = mat2 = mat1;
	EXPECT_TRUE(mat2 == mat1);
	EXPECT_TRUE(mat3 == mat1);
}

TEST(TMatrix_test2, oper_assign_3) { //проверка на самоприсваивание
	TMatrix<int>mat1(2);
	mat1[0][0] = 1;
	mat1[0][1] = 1;
	mat1[1][1] = 2;

	mat1 = mat1;
	EXPECT_EQ(mat1.GetSize(), 2);
	EXPECT_EQ(mat1[0][0], 1);
	EXPECT_EQ(mat1[0][1], 1);
	EXPECT_EQ(mat1[1][1], 2);
}
///////////
TEST(TMatrix_test2, SUM) {
	TMatrix<int>mat1(2);
	mat1[0][0] = 1;
	mat1[0][1] = 1;
	mat1[1][1] = 2;

	TMatrix<int>mat2(2);
	mat2[0][0] = 1;
	mat2[0][1] = 1;
	mat2[1][1] = 2;


	TMatrix<int>mat = mat1 + mat2;
	EXPECT_EQ(mat.GetSize(), 2);
	EXPECT_EQ(mat[0][0], 2);
	EXPECT_EQ(mat[0][1], 2);
	EXPECT_EQ(mat[1][1], 4);
}

TEST(TMatrix_test2, SUM_1) {
	TMatrix<int>mat1(3);
	TMatrix<int>mat2(2);
	try {
		TMatrix<int>mat = mat1 + mat2;
	}
	catch (const std::runtime_error& a) {
		EXPECT_STREQ(a.what(), "Different sizes of matrices");
	}
}
/////////////
TEST(TMatrix_test2, DIFF) {
	TMatrix<int>mat1(2);
	mat1[0][0] = 1;
	mat1[0][1] = 1;
	mat1[1][1] = 2;

	TMatrix<int>mat2(2);
	mat2[0][0] = 3;
	mat2[0][1] = 4;
	mat2[1][1] = 1;


	TMatrix<int>mat = mat1 - mat2;
	EXPECT_EQ(mat.GetSize(), 2);
	EXPECT_EQ(mat[0][0], -2);
	EXPECT_EQ(mat[0][1], -3);
	EXPECT_EQ(mat[1][1], 1);
}
/////////////
TEST(TMatrix_test3, oper_input) {
	TMatrix<int>mat(2);
	std::istringstream in("1 2\n3");
	in >> mat;
	EXPECT_EQ(mat[0][0], 1);
	EXPECT_EQ(mat[0][1], 2);
	EXPECT_EQ(mat[1][1], 3);
}

TEST(TMatrix_test3, oper_input_1) {
	TMatrix<int>mat(2);
	mat[0][0] = 67;
	mat[0][1] = 89;
	mat[1][1] = 345;

	std::istringstream in("1 2 3");
	in >> mat;
	EXPECT_EQ(mat[0][0], 1);
	EXPECT_EQ(mat[0][1], 2);
	EXPECT_EQ(mat[1][1], 3);
}

TEST(TMatrix_test3, oper_input_2) {
	TMatrix<int>mat(2);
	std::istringstream in("145 2 3 ABC");
	in >> mat;
	EXPECT_EQ(mat[0][0], 145);
	EXPECT_EQ(mat[0][1], 2);
	EXPECT_EQ(mat[1][1], 3);
}

TEST(TMatrix_test3, oper_input_3) {
	TMatrix<int>mat(2);
	mat[0][0] = 67;
	mat[0][1] = 89;
	mat[1][1] = 345;
	std::istringstream in("1 2 ghf");
	try {
		in >> mat;
	}
	catch (const std::invalid_argument& a) {
		EXPECT_STREQ(a.what(), "Incorrect input");
	}

	EXPECT_EQ(mat[0][0], 67);
	EXPECT_EQ(mat[0][1], 89);
	EXPECT_EQ(mat[1][1], 345);
}

TEST(TMatrix_test3, oper_input_4) {
	TMatrix<std::string>mat(2);
	std::istringstream in("AB CD EFG ABC");
	in >> mat;
	EXPECT_EQ(mat[0][0], "AB");
	EXPECT_EQ(mat[0][1], "CD");
	EXPECT_EQ(mat[1][1], "EFG");
}

TEST(TMatrix_test3, oper_input_5) {
	TMatrix<int>mat(2);
	TMatrix<int>mat1(1);
	std::istringstream in("1 2 3 4");
	in >> mat >> mat1;
	EXPECT_EQ(mat[0][0], 1);
	EXPECT_EQ(mat[0][1], 2);
	EXPECT_EQ(mat[1][1], 3);

	EXPECT_EQ(mat1[0][0], 4);
}

//////////////
TEST(TMatrix_test3, oper_out) {
	TMatrix<int>mat(2);
	mat[0][0] = 1;
	mat[0][1] = 2;
	mat[1][1] = 3;
	std::ostringstream out;
	std::string str = "1 2\n0 3\n";
	out << mat;
	EXPECT_EQ(out.str(), str);
}
TEST(TMatrix_test3, oper_out_1) {
	TMatrix<int>mat(2);
	mat[0][0] = 1;
	mat[0][1] = 2;
	mat[1][1] = 3;

	TMatrix<int>mat1(2);
	mat1[0][0] = 4;
	mat1[0][1] = 5;
	mat1[1][1] = 6;

	std::ostringstream out;
	std::string str = "1 2\n0 3\n\n4 5\n0 6\n";
	out << mat << "\n" << mat1;
	EXPECT_EQ(out.str(), str);
}