#include "pch.h"
#include "utmatrix.h"
using namespace std;
//Тесты TVector
TEST(TestNameVectorInit, TestNameVector1) { // Проверка корректности конструкторов
    EXPECT_ANY_THROW({
        TVector<int> T(-3);
        });
    EXPECT_ANY_THROW({
        TVector<int> T(3,6);
        });
    EXPECT_ANY_THROW({
        TVector<int> T(5,-1);
        });
    EXPECT_ANY_THROW({
        TVector<int> T(MAX_VECTOR_SIZE + 10,1);
        });
    EXPECT_ANY_THROW({
        TVector<int> T(10,MAX_VECTOR_SIZE);
        });
    EXPECT_NO_THROW({
         TVector<int> T(10,5);
        });
    EXPECT_NO_THROW({
        TVector<int> T(100);
        });
}

TEST(TestNameVectorOperators1, TestNameSquareBrackets) { //Проверка квадратных скобок
    TVector<int> v(5, 2);
    std::string data_for_vector = "4 5 6";
    std::stringstream ss_vector(data_for_vector);
    ss_vector >> v;
    //std::cout << "Vector v initialized from string: " << v << std::endl;
    //cout << v[4];
    EXPECT_ANY_THROW({
        int a = v[5];
        });
    EXPECT_ANY_THROW({
        int a = v[1];
        });
    EXPECT_ANY_THROW({
        int a = v[-3];
        });
    EXPECT_EQ(v[4], 6);
    EXPECT_EQ(v[3], 5);
}

TEST(TestNameVectorOperators2, TestNameEquations1) { //Проверка операторов равенства, приравнивания, конструстора копирования
    TVector<int> v(5, 2);
    std::string data_for_vector = "1 2 3";
    std::stringstream ss_vector(data_for_vector);
    ss_vector >> v;
    TVector<int> c(v);
    TVector<int> b(5, 2);
    b = v;
    EXPECT_EQ(c, v);
    EXPECT_EQ(v, v);
    EXPECT_EQ((v == b), 1);
    EXPECT_EQ((v != b), 0);
}

TEST(TestNameVectorOperators3, TestNameEquations2) { //Проверка операторов равенства, приравнивания
    TVector<int> v(5, 2);
    std::string data_for_vector = "4 5 6";
    std::stringstream ss_vector(data_for_vector);
    ss_vector >> v;
    TVector<int> b(5, 2);
    b = v;
    EXPECT_EQ(v, b);
    v = v;
    EXPECT_EQ(v, b);
}

TEST(TestNameVectorOperators4, TestNameVectorAddSub) {//Проверка работы векторных операций
    TVector<int> v(5, 2);
    std::string data_for_vector = "1 2 3";
    std::stringstream ss_vector(data_for_vector);
    ss_vector >> v;
    EXPECT_EQ(v * 2, v + v);
    EXPECT_EQ(v * 0, v - v);
    v = v + v;
    EXPECT_EQ(v[4], 6);
    EXPECT_EQ(v[2], 2);

    TVector<int> t(5, 2);
    std::string data_for_vector1 = "4 5 6";
    std::stringstream ss_vector1(data_for_vector1);
    ss_vector1 >> t;
    EXPECT_EQ(t[4], v[4]);
    EXPECT_EQ(v[3] + 1, t[3]);

    TVector<int> b(5, 2);
    std::string data_for_vector2 = "2 1 0";
    std::stringstream ss_vector2(data_for_vector2);
    ss_vector2 >> b;
    EXPECT_EQ(b, t - v);
}

TEST(TestNameVectorOperators5, TestNameVectorMult) { // Проверка скалярного произведения векторов
    TVector<int> v(5, 2);
    std::string data_for_vector = "1 2 3";
    std::stringstream ss_vector(data_for_vector);
    ss_vector >> v;
    TVector<int> t(5, 2);
    std::string data_for_vector1 = "4 5 6";
    std::stringstream ss_vector1(data_for_vector1);
    ss_vector1 >> t;
    TVector<int> b(5, 2);
    std::string data_for_vector2 = "2 1 0";
    std::stringstream ss_vector2(data_for_vector2);
    ss_vector2 >> b;
    EXPECT_EQ(t * v, 32);
    EXPECT_EQ(t * b, 13);
    EXPECT_EQ(b * v, 4);
}

TEST(TestNameVectorOperators6, TestNameVectorDiffDImensions) { //Проверка векторных операций с разными длинами векторов
    TVector<int> v(6, 2);
    std::string data_for_vector = "1 2 3 4";
    std::stringstream ss_vector(data_for_vector);
    ss_vector >> v;
    TVector<int> t(5, 2);
    std::string data_for_vector1 = "4 5 6";
    std::stringstream ss_vector1(data_for_vector1);
    ss_vector1 >> t;
    EXPECT_ANY_THROW({
        int a = t * v;
        });
    EXPECT_ANY_THROW({
        t = t + v;
        });
    EXPECT_ANY_THROW({
        t = t - v;
        });
}

TEST(TestNameVectorOperators7, TestNameVectorDiffStart) {// Проверка операций с разными StartIndex - определены, поэтому не дают ошибок
    TVector<int> v(5, 3);
    std::string data_for_vector = "1 2";
    std::stringstream ss_vector(data_for_vector);
    ss_vector >> v;
    TVector<int> t(5, 2);
    std::string data_for_vector1 = "4 5 6";
    std::stringstream ss_vector1(data_for_vector1);
    ss_vector1 >> t;
    TVector<int> b(5, 2);
    std::string data_for_vector2 = "4 6 8";
    std::stringstream ss_vector2(data_for_vector2);
    ss_vector2 >> b;
    TVector<int> c(5, 2);
    std::string data_for_vector3 = "4 4 4";
    std::stringstream ss_vector3(data_for_vector3);
    ss_vector3 >> c;
    EXPECT_NO_THROW({
        TVector<int> d(5, 2);
        d = t * v;
        d = t + v;
        d = t - v;
        });
    EXPECT_EQ(t* v, 17);
    EXPECT_EQ(t + v, b);
    EXPECT_EQ(t - v, c);
}

TEST(TestNameVectorOperators8, TestNameScalar) { //Проверка на операции со скалярами
    TVector<int> v(5, 3);
    std::string data_for_vector = "1 2";
    std::stringstream ss_vector(data_for_vector);
    ss_vector >> v;
    v = v + 2;
    EXPECT_EQ(v[0], 2);
    EXPECT_EQ(v[4], 4);
    v = v - 3;
    EXPECT_EQ(v[3], 0);
    EXPECT_EQ(v[4], 1);
    v = v * 2;
    EXPECT_EQ(v[1], -2);
    EXPECT_EQ(v[4], 2);
}

//Тест TMatrix

TEST(TestMatricesInit, TestNameMatrix1) { //Проверка конструкторов TMatrix
    EXPECT_ANY_THROW({
        TMatrix<int> T(-3);
        });
    EXPECT_ANY_THROW({
        TMatrix<int> T(MAX_MATRIX_SIZE * 2);
        });
    EXPECT_NO_THROW({
        TMatrix<int> s(10);
        });
    TMatrix<int> m(3);
    std::string data_for_matrix = "1 2 3 4 5 6";
    std::stringstream ss_matrix(data_for_matrix);
    ss_matrix >> m;
    TMatrix<int> m1(m);
    EXPECT_EQ(m, m1);

    TVector<TVector<int>> A(4);
    for (int i = 0; i < A.GetSize(); ++i) {
        TVector<int> S(4, i);
        A[i] = S;
    }
    EXPECT_NO_THROW({
        TMatrix<int> mt(A);
        });
    TVector<TVector<int>> B(4);
    for (int i = 0; i < B.GetSize(); ++i) {
        TVector<int> S(4);
        B[i] = S;
    }
    EXPECT_ANY_THROW({
        TMatrix<int> mt(B);
        });
}

TEST(TestNameMatricesOperator1, TestNameEquation1) { //Операторы равенства для матриц
    TMatrix<int> m(3);
    std::string data_for_matrix = "1 2 3 4 5 6";
    std::stringstream ss_matrix(data_for_matrix);
    ss_matrix >> m;
    TMatrix<int> m1(3);
    m1 = m;
    EXPECT_EQ(m1, m);
    m = m;
    EXPECT_EQ(m1, m);
    TMatrix<int> m2(3);
    std::string data_for_matrix1 = "1 2 3 4 5 6";
    std::stringstream ss_matrix1(data_for_matrix1);
    ss_matrix1 >> m2;
    EXPECT_EQ(m2, m);
    m2[0][1] = 0;
    EXPECT_EQ((m2 != m), 1);
}

TEST(TestNameMatricesOperator2, TestNameAddSub) { //Операторы сложения и вычитания для матриц
    TMatrix<int> m(3);
    std::string data_for_matrix = "1 2 3 4 5 6";
    std::stringstream ss_matrix(data_for_matrix);
    ss_matrix >> m;

    TMatrix<int> E(3);
    std::string data_for_matrix1 = "1 0 0 1 0 1";
    std::stringstream ss_matrix1(data_for_matrix1);
    ss_matrix1 >> E;

    TMatrix<int> m2(3);
    std::string data_for_matrix2 = "2 2 3 5 5 7";
    std::stringstream ss_matrix2(data_for_matrix2);
    ss_matrix2 >> m2;

    TMatrix<int> m3(3);
    std::string data_for_matrix3 = "0 2 3 3 5 5";
    std::stringstream ss_matrix3(data_for_matrix3);
    ss_matrix3 >> m3;

    EXPECT_EQ(E + m, m2);
    EXPECT_EQ(m2 - E, m);
    EXPECT_EQ(m - E, m3);

    TMatrix<int> Ex(4);
    std::string data_for_matrix4 = "1 2 3 4 5 6 7 8 9 10";
    std::stringstream ss_matrix4(data_for_matrix4);
    ss_matrix4 >> Ex;
    EXPECT_ANY_THROW({
        Ex = Ex + E;
        });
    EXPECT_ANY_THROW({
        Ex = Ex - E;
        });
    EXPECT_ANY_THROW({
        Ex = Ex + m;
        });
    EXPECT_ANY_THROW({
        Ex = Ex - m;
        });
}