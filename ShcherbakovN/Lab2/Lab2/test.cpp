#include "pch.h"
#include "..\..\Lab2\Lab2Code\RealizationTVectorAndTMatrix.h"
#define ValType int

//Тесты класса TVector:

TEST(Vector, CreateVectorNoThrow) 
{
	int s = 20, si = 2;
	EXPECT_NO_THROW({ //Не вернёт исключение.
		TVector<ValType> v1; //Конструктор по умолчанию.
		TVector<ValType> v2(s, si); //Конструктор с параметрами.
		TVector<ValType> v3(MAX_VECTOR_SIZE, 0); //Граничный случай.
		TVector<ValType> v4(1, 0); //Граничный случай.
		});

	EXPECT_NO_THROW({
		TVector<ValType> v5(si, s); //Размер вектора меньше индекса первого элемента вектора.
		});

	s = 30, si = 15;
	EXPECT_NO_THROW({
		TVector<ValType> v6(s, si);
		TVector<ValType> v7(v6); //Конструктор копирования.
		});
}

TEST(Vector, CreateVectorAnyThrow)
{
	//Исключения:

	int s = 15, si = 5;
	EXPECT_THROW(TVector<ValType> v1(-s, si), std::out_of_range);
	EXPECT_THROW(TVector<ValType> v2(-s, -si), std::out_of_range);
	EXPECT_THROW(TVector<ValType> v3(s, -si), std::out_of_range);
	EXPECT_THROW(TVector<ValType> v4(0, si), std::out_of_range);
	EXPECT_THROW(TVector<ValType> v5(MAX_VECTOR_SIZE+1, si), std::out_of_range);
}

TEST(Vector, GetSizeAndStartIndex) {
	int s = 67, si = 34;
		TVector<ValType> v(s,si);
		EXPECT_EQ(v.GetSize(), s);
		EXPECT_EQ(v.GetStartIndex(), si);
}

TEST(Vector, AccessToTheElementsNoThrow) {
	int s = 15, si = 5;
	TVector<ValType> v1(s, si);
	EXPECT_NO_THROW({ //Доступ к элементам.
		for (int i = si; i < s + si; ++i)
		{
			v1[i];
		}
		});

	ValType elem = 5;
	TVector<ValType> v2(s, si);
	EXPECT_NO_THROW({ //Инициализация элементов.
		for (int i = si; i < s + si; ++i)
		{
			v2[i] = elem; 
		}
		});
}

TEST(Vector, AccessToTheElementsAnyThrow) {

	//Исключения:

	int s = 15, si = 5;
	TVector<ValType> v(s, si);
	EXPECT_THROW(v[si - 1], std::out_of_range);
	EXPECT_THROW(v[s + si], std::out_of_range);
}

TEST(Vector, CompareVector) {
	int s = 5, si = 0;
	TVector<ValType> v1(s, si);
	TVector<ValType> v2(s + 1, si);
	TVector<ValType> v3(s + 1, si + 1);
	TVector<ValType> v4(s, si + 1);
	TVector<ValType> v5(s, si);
	EXPECT_EQ(v1 == v2, false);
	EXPECT_EQ(v1 == v3, false);
	EXPECT_EQ(v1 == v4, false);
	EXPECT_EQ(v1 == v5, true);

	EXPECT_EQ(v1 != v2, true);
	EXPECT_EQ(v1 != v3, true);
	EXPECT_EQ(v1 != v4, true);
	EXPECT_EQ(v1 != v5, false);

	//С инициализированными элементами:

	ValType elem = 5;
	v1[si] = elem;
	v5[si] = elem;
	EXPECT_EQ(v1 == v5, true);
	EXPECT_EQ(v1 != v5, false);

	v5[si + 1] = elem;
	EXPECT_EQ(v1 == v5, false);
	EXPECT_EQ(v1 != v5, true);
	
}

TEST(Vector, AssignmentVector) {
	int s = 15, si = 5;
	TVector<ValType> v1(s, si);
	TVector<ValType> v2(s + 5, si + 3);

	EXPECT_EQ(v1 != v2, true);

	v1 = v2;
	EXPECT_EQ(v1 == v2, true);

	//Проверяем, что элементы копируются:

	TVector<ValType> v3(s, si);
	TVector<ValType> v4(s + 1, si + 1);
	ValType elem = 5;

	v3[si] = elem;
	EXPECT_EQ(v3 != v4, true);

	v4 = v3;
	EXPECT_EQ(v4 == v3, true);
}

TEST(Vector, VectorOperationsWithScalar) {

	//Прибавление скаляра:

	ValType elem = 10;
	int s = 5, si = 0;
	TVector<ValType> v1(s, si);
	TVector<ValType> v2(s, si);

	for (int i = si; i < s + si; ++i)
	{
		v2[i] += elem;
	}

	EXPECT_EQ((v1 + elem) == v2, true);

	//Вычитание скаляра:
	
	TVector<ValType> v3(s, si);
	TVector<ValType> v4(s, si);

	for (int i = si; i < s + si; ++i)
	{
		v4[i] -= elem;
	}

	EXPECT_EQ((v3 - elem) == v4, true);

	//Умножение на скаляр:

	TVector<ValType> v5(s, si);
	TVector<ValType> v6(s, si);

	for (int i = si; i < s + si; ++i)
	{
		v6[i] += elem;
		v6[i] *= elem;
	}

	EXPECT_EQ(((v5 + elem) * elem) == v6, true);
}

TEST(Vector, VectorOperationsWithVectorNoThrow) {
	int s = 15, si = 5;
	TVector<ValType> v1(s, si);
	TVector<ValType> v2(s, si);
	TVector<ValType> v3(s, si);
	TVector<ValType> v4(s, si);
	TVector<ValType> v9(s, si);
	ValType elem1 = 1;
	ValType elem2 = 5;
	EXPECT_NO_THROW({ //Сложение векторов.
		v1 = v1 + elem1;
		v2 = v2 + elem2;
		v3 = v1 + v2;
		for (int i = si; i < s + si; ++i)
		{
			EXPECT_EQ(v3[i], v1[i] + v2[i]);
		}

		v3 = v2 + v1;
		for (int i = si; i < s + si; ++i)
		{
			EXPECT_EQ(v3[i], v2[i] + v1[i]);
		}

		v4 = v1 + v1; //Сложение с самим собой.
		for (int i = si; i < s + si; ++i)
		{
			EXPECT_EQ(v4[i], v1[i] + v1[i]);
		}
		});

	EXPECT_NO_THROW({ //Вычитание векторов.
		v1 = v1 - elem2;
		v2 = v2 - elem1 - elem1;
		v3 = v1 - v2;
		for (int i = si; i < s + si; ++i)
		{
			EXPECT_EQ(v3[i], v1[i] - v2[i]);
		}

		v3 = v2 - v1;
		for (int i = si; i < s + si; ++i)
		{
			EXPECT_EQ(v3[i], v2[i] - v1[i]);
		}

		v9 = v1 - v1; //Вычитание с самим собой.
		for (int i = si; i < s + si; ++i)
		{
			EXPECT_EQ(v9[i], v1[i] - v1[i]);
		}
		});


	s = 8, si = 1;
	TVector<ValType> v5(s, si);
	TVector<ValType> v6(s, si);

	TVector<ValType> v7(s, si);
	TVector<ValType> v8(s, si);
	ValType elem3 = 0;

	EXPECT_NO_THROW({ //Скалярное произведение векторов.
		v5 = v5 + elem1 + elem1;
		v6 = v6 + elem2;
		ValType scalar_product = 0;
		for (int i = si; i < s + si; ++i)
		{
			scalar_product += v5[i] * v6[i];
		}
		EXPECT_EQ(v5 * v6, scalar_product);

		EXPECT_EQ(v7 * v8, elem3); //Скалярное произведение на нулевых векторах.
		});
}

TEST(Vector, VectorOperationsWithVectorAnyThrow) {

	//Исключения:

	int s = 15, si = 5;
	TVector<ValType> v1(s, si);
	TVector<ValType> v2(s + 1, si + 1);
	TVector<ValType> v3(s + 1, si);
	TVector<ValType> v4(s, si + 1);

	EXPECT_THROW(v1 + v2, std::invalid_argument);
	EXPECT_THROW(v1 + v3, std::invalid_argument);
	EXPECT_THROW(v1 + v4, std::invalid_argument);

	EXPECT_THROW(v1 - v2, std::invalid_argument);
	EXPECT_THROW(v1 - v3, std::invalid_argument);
	EXPECT_THROW(v1 - v4, std::invalid_argument);

	EXPECT_THROW(v1 * v2, std::invalid_argument);
	EXPECT_THROW(v1 * v3, std::invalid_argument);
	EXPECT_THROW(v1 * v4, std::invalid_argument);
}

//Тесты класса TMatrix:

TEST(Matrix, CreateMatrixNoThrow) {
	int s = 5;
	EXPECT_NO_THROW({
		TMatrix<ValType> m1; //Конструктор по умолчанию.
		TMatrix<ValType> m2(s); //Конструктор с параметром.
		TMatrix<ValType> m3(MAX_MATRIX_SIZE); //Граничный случай.
		TMatrix<ValType> m4(1); //Граничный случай.
		});

	s = 10;
	EXPECT_NO_THROW({
		TMatrix<ValType> m5(s);
		ValType elem = 1;

		m5[0][0] = elem; //Изменяем 1 элемент матрицы.

		TMatrix<ValType> m6(m5); //Конструктор копирования.
		EXPECT_EQ(m6[0][0], elem);
		});
}

TEST(Matrix, CreateMatrixAnyThrow) {

	//Исключения:

	int s = 5;
	EXPECT_THROW(TMatrix<ValType> m1(-s), std::out_of_range);
	EXPECT_THROW(TMatrix<ValType> m2(0), std::out_of_range);
	EXPECT_THROW(TMatrix<ValType> m2(MAX_MATRIX_SIZE + 1), std::out_of_range);
}

TEST(Matrix, VectorOfVectorsConversionToMatrixNoThrow) {
	int s = 5, si = 0;
	TVector<TVector<ValType>> vm(s, si);

	for (int i = 0; i < s; ++i)//Корректируем вектор векторов под вид верхнетреугольной матрицы.
	{
		TVector<ValType> vmi(s - i, i);
		vm[i] = vmi;
	}

	EXPECT_NO_THROW({
		TMatrix<ValType> m(vm);
		});
}

TEST(Matrix, VectorOfVectorsConversionToMatrixAnyThrow) {
	int s = 5, si = 0;

	TVector<TVector<ValType>> vm1(s, si);
	EXPECT_THROW(TMatrix<ValType> m1(vm1), std::invalid_argument);

	si = 1;
	TVector<TVector<ValType>> vm2(s, si);
	EXPECT_THROW(TMatrix<ValType> m2(vm2), std::invalid_argument);
}

TEST(Matrix, CompareMatrix) {
	int s = 5;
	TMatrix<ValType> m1(s);
	TMatrix<ValType> m2(s + 1);
	TMatrix<ValType> m3(s);

	EXPECT_EQ(m1 == m2, false);
	EXPECT_EQ(m1 == m3, true);

	EXPECT_EQ(m1 != m2, true);
	EXPECT_EQ(m1 != m3, false);

	//С инициализированными элементами:

	ValType elem = 1;
	m1[0][0] = elem;
	m3[0][0] = elem;

	EXPECT_EQ(m1 == m3, true);
	EXPECT_EQ(m1 != m3, false);

	m1[0][1] = elem;

	EXPECT_EQ(m1 == m3, false);
	EXPECT_EQ(m1 != m3, true);
}

TEST(Matrix, AssignmentMatrix) {
	int s = 5;
	TMatrix<ValType> m1(s);
	TMatrix<ValType> m2(s + 3);

	EXPECT_EQ(m1 != m2, true);

	m1 = m2;
	EXPECT_EQ(m1 == m2, true);

	//Проверяем, что элементы копируются:

	TMatrix<ValType> m3(s);
	TMatrix<ValType> m4(s + 1);
	ValType elem = 3;

	m3[0][0] = elem;
	EXPECT_EQ(m3 != m4, true);

	m4 = m3;
	EXPECT_EQ(m4 == m3, true);
}

TEST(Matrix, MatrixOperationsAdditionAndSubtractionNoThrow) {
	int s = 5;
	TMatrix<ValType> m1(s);
	TMatrix<ValType> m2(s);
	TMatrix<ValType> m3(s);
	ValType elem1 = 1;
	ValType elem2 = 3;
	EXPECT_NO_THROW({ //Сложение матриц.
		for (int i = 0; i < s; ++i) //Инициализируем матрицу m1.
		{
			for (int j = i; j < s; ++j)
			{
				m1[i][j] = elem1;
			}
		}
		
		for (int i = 0; i < s; ++i) //Инициализируем матрицу m2.
		{
			for (int j = i; j < s; ++j)
			{
				m2[i][j] = elem2;
			}
		}

		m3 = m1 + m2;
		for (int i = 0; i < s; ++i) //Проверяем сложение матриц.
		{
			for (int j = i; j < s; ++j)
			{
				EXPECT_EQ(m3[i][j], m1[i][j] + m2[i][j]);
			}
		}

		m3 = m1 + m1;
		for (int i = 0; i < s; ++i) //Проверяем сложение с самим собой.
		{
			for (int j = i; j < s; ++j)
			{
				EXPECT_EQ(m3[i][j], m1[i][j] + m1[i][j]);
			}
		}
		});

	EXPECT_NO_THROW({ //Вычитание матриц.
		m3 = m1 - m2;
		for (int i = 0; i < s; ++i) //Проверяем вычитание матриц.
		{
			for (int j = i; j < s; ++j)
			{
				EXPECT_EQ(m3[i][j], m1[i][j] - m2[i][j]);
			}
		}

		m3 = m2 - m1;
		for (int i = 0; i < s; ++i)
		{
			for (int j = i; j < s; ++j)
			{
				EXPECT_EQ(m3[i][j], m2[i][j] - m1[i][j]);
			}
		}

		m3 = m1 - m1;
		for (int i = 0; i < s; ++i) //Проверяем вычитание с самим собой.
		{
			for (int j = i; j < s; ++j)
			{
				EXPECT_EQ(m3[i][j], m1[i][j] - m1[i][j]);
			}
		}
		});
}

TEST(Matrix, MatrixOperationsAdditionAndSubtractionAnyThrow) {

	//Исключения:

	int s = 5;
	TMatrix<ValType> m1(s);
	TMatrix<ValType> m2(s + 1);

	EXPECT_THROW(m1 + m2, std::invalid_argument);
	EXPECT_THROW(m2 + m1, std::invalid_argument);

	EXPECT_THROW(m1 - m2, std::invalid_argument);
	EXPECT_THROW(m2 - m1, std::invalid_argument);
}