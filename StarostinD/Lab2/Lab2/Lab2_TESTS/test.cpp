#include "pch.h"
#include "..\utmatrix.cpp"
#include <random>

using std::uniform_int_distribution;
using std::default_random_engine;

//TVector

TVector<int> get_rand_vect(int sz, int si=0) {
	default_random_engine re;
	uniform_int_distribution<> un(-256, 256);
	TVector<int> v(sz, si);
	for (int i = si; i < sz; ++i) {
		v[i] = un(re);
	}
	return v;
}

TEST(TVector_Constructor, Size_Constructor) {
	default_random_engine re;
	uniform_int_distribution<> un(1, 100);
	EXPECT_NO_THROW(TVector<int>());
	TVector<int> def;
	EXPECT_EQ(10, def.GetSize());
	EXPECT_EQ(0, def.GetStartIndex());
	int sz = un(re), si = un(re);
	EXPECT_NO_THROW(TVector<double> t(sz, si));
	TVector<double> t(sz, si);
	EXPECT_EQ(sz, t.GetSize());
	EXPECT_EQ(si, t.GetStartIndex());
}

TEST(TVector_Constructor, Copy_Constructor) {
	default_random_engine re;
	uniform_int_distribution<> un(1, 100);
	int sz = un(re), si = un(re);
	TVector<int> t(sz, si);
	for (int i = si; i < sz; ++i) {
		t[i] = un(re);
	}
	TVector<int> cp(t);
	EXPECT_EQ(t.GetSize(), cp.GetSize());
	EXPECT_EQ(t.GetStartIndex(), cp.GetStartIndex());
	for (int i = si; i < si; ++i) {
		EXPECT_EQ(t[i], cp[i]);
	}
	cp[si] = -t[si] - 1;
	EXPECT_NE(cp[si], t[si]);
}

TEST(TVector_Get, Get_Size_And_StartIndex) {
	TVector<int> v(10, 4);
	EXPECT_EQ(10, v.GetSize());
	EXPECT_EQ(4, v.GetStartIndex());
}

TEST(TVector_Operators, Access) {
	TVector<int> v;
	EXPECT_NO_THROW(v[3] = 15);
	v[3] = 15;
	EXPECT_EQ(15, v[3])	;
}

TEST(TVector_Operators, Equal) {
	TVector<int> v1(get_rand_vect(10, 4));
	TVector<int> v2(v1);
	EXPECT_TRUE(v1 == v1);
	EXPECT_TRUE(v1 == v2);
	v2[5] = -v1[5];
	EXPECT_FALSE(v1 == v2);
	TVector<int> v3(10, 1);
	for (int i = v1.GetStartIndex(); i < v1.GetSize(); ++i) {
		v3[i] = v1[i];
	}
	EXPECT_TRUE(v3 == v1);
	TVector<int> v4(1);
	EXPECT_FALSE(v1 == v4);
}

TEST(TVector_Operators, Not_Equal) {
	TVector<int> v1(get_rand_vect(10, 4));
	TVector<int> v2(v1);
	EXPECT_FALSE(v1 != v1);
	EXPECT_FALSE(v1 != v2);
	v2[5] = -v1[5];
	EXPECT_TRUE(v1 != v2);
	TVector<int> v3(10, 1);
	for (int i = v1.GetStartIndex(); i < v1.GetSize(); ++i) {
		v3[i] = v1[i];
	}
	EXPECT_FALSE(v3 != v1);
	TVector<int> v4(1);
	EXPECT_TRUE(v1 != v4);
}

TEST(TVector_Operators, Assignment) {
	TVector<int> v(get_rand_vect(20,5));
	TVector<int> cp(3, 1);
	EXPECT_NO_THROW(cp = v);
	cp = v;
	EXPECT_EQ(cp, v);
}

TEST(TVector_Operators, Self_Assignment) {
	TVector<int> v(get_rand_vect(20, 5));
	EXPECT_NO_THROW(v = v);
	TVector<int> before(v);
	EXPECT_EQ(before, v = v);
}

TEST(TVector_Scalar_Operations, Addition) {
	TVector<int> v(get_rand_vect(10, 3));
	TVector<int> after(v);
	const int scalar = rand() % 20;
	for (int i = after.GetStartIndex(); i < after.GetSize(); ++i) {
		after[i] += scalar;
	}
	EXPECT_EQ(after, v + scalar);
}

TEST(TVector_Scalar_Operations, Subtraction) {
	TVector<int> v(get_rand_vect(10, 3));
	TVector<int> after(v);
	const int scalar = rand() % 20;
	for (int i = after.GetStartIndex(); i < after.GetSize(); ++i) {
		after[i] -= scalar;
	}
	EXPECT_EQ(after, v - scalar);
}

TEST(TVector_Scalar_Operations, Multiplication) {
	TVector<int> v(get_rand_vect(10, 3));
	TVector<int> after(v);
	const int scalar = rand() % 20;
	for (int i = after.GetStartIndex(); i < after.GetSize(); ++i) {
		after[i] *= scalar;
	}
	EXPECT_EQ(after, v * scalar);
}

TEST(TVector_Vector_Operations, Addition) {
	TVector<int> first(get_rand_vect(10, 3)), second(get_rand_vect(10, 6));
	TVector<int> after(10, 3);
	for (int i = first.GetStartIndex(); i < second.GetStartIndex(); ++i) {
		after[i] += first[i];
	}
	for (int i = second.GetStartIndex(); i < second.GetSize(); ++i) {
		after[i] += first[i] + second[i];
	}
	EXPECT_EQ(after, first + second);
}


TEST(TVector_Vector_Operations, Subtraction_Equal_Sizes) {
	TVector<int> first(get_rand_vect(10, 3)), second(get_rand_vect(10, 3));
	TVector<int> after(10, 3);
	for (int i = first.GetStartIndex(); i < first.GetSize(); ++i) {
		after[i] += first[i] - second[i];
	}
	EXPECT_EQ(after, first - second);
}

TEST(TVector_Vector_Operations, Subtraction_Differernt_Sizes) {
	TVector<int> first(get_rand_vect(10, 6)), second(get_rand_vect(10, 3));
	TVector<int> after(10, 3);
	for (int i = second.GetStartIndex(); i < first.GetStartIndex(); ++i) {
		after[i] -= second[i];
	}
	for (int i = first.GetStartIndex(); i < first.GetSize(); ++i) {
		after[i] += first[i] - second[i];
	}
	EXPECT_EQ(after, first - second);
}

TEST(TVector_Vector_Operations, Product_Equal_Sizes) {
	TVector<int> first(get_rand_vect(10, 3)), second(get_rand_vect(10, 3));
	int prod = 0;
	for (int i = first.GetStartIndex(); i < first.GetSize(); ++i) {
		prod += first[i] * second[i];
	}
	EXPECT_EQ(prod, first * second);
}

TEST(TVector_Vector_Operations, Product_Differernt_Sizes) {
	TVector<int> first(get_rand_vect(10, 6)), second(get_rand_vect(10, 3));
	int prod = 0;
	for (int i = first.GetStartIndex(); i < first.GetSize(); ++i) {
		prod += first[i] * second[i];
	}
	EXPECT_EQ(prod, first * second);
}

TEST(TVector_Exceptions, Constructor) {
	EXPECT_THROW(TVector<int>(-1, 0), std::invalid_argument);
	EXPECT_THROW(TVector<int>(1, -1), std::invalid_argument);
	EXPECT_THROW(TVector<int>(1, 2), std::invalid_argument);
	EXPECT_THROW(TVector<int>(MAX_VECTOR_SIZE + 1, 0), std::invalid_argument);
}

TEST(TVector_Exceptions, Access) {
	TVector<int> v(10, 5);
	EXPECT_THROW(v[0], std::out_of_range);
	EXPECT_THROW(v[11], std::out_of_range);
}

TEST(TVector_Exceptions, Vector_Operations) {
	TVector<int> v1(10, 5), v2(11, 5);
	EXPECT_THROW(v1 + v2, std::invalid_argument);
	EXPECT_THROW(v1 - v2, std::invalid_argument);
	EXPECT_THROW(v1 * v2, std::invalid_argument);
}

//TMatrix

TEST(TMatrix_Constructor, Size_Constructor) {
	default_random_engine re;
	uniform_int_distribution<> un(1, 100);
	EXPECT_NO_THROW(TMatrix<int>());
	TMatrix<int> def;
	EXPECT_EQ(10, def.GetSize());
	int sz = un(re);
	EXPECT_NO_THROW(TVector<double> t(sz));
	TMatrix<double> t(sz);
	EXPECT_EQ(sz, t.GetSize());
	for (int i = 0; i < sz; ++i) {
		EXPECT_EQ(sz, t[i].GetSize());
		EXPECT_EQ(i, t[i].GetStartIndex());
	}
}

TEST(TMatrix_Constructor, Copy_Constructor) {
	default_random_engine re;
	uniform_int_distribution<> un(1, 100);
	int sz = un(re);
	TMatrix<int> t(sz);
	for (int i = 0; i < sz; ++i) {
		for (int j = i; j < sz; ++j) {
			t[i][j] = un(re);
		}
	}
	TMatrix<int> cp(t);
	EXPECT_EQ(t.GetSize(), cp.GetSize());
	for (int i = 0; i < sz; ++i) {
		for (int j = i; j < sz; ++j) {
			EXPECT_EQ(t[i][j], cp[i][j]);
		}
	}
	cp[0][0] = -t[0][0] + 1;
	EXPECT_NE(cp[0][0], t[0][0]);
}

TEST(TMatrix_Constructor, Converting_Constructor) {
	TVector<TVector<int>> v;
	for (int i = 0; i < v.GetSize(); ++i) {
		v[i] = get_rand_vect(v.GetSize(), i);
	}
	TMatrix<int> test;
	for (int i = 0; i < v.GetSize(); ++i) {
		for (int j = i; j < v.GetSize(); ++j) {
			test[i][j] = v[i][j];
		}
	}
	TMatrix<int> converted(v);
	EXPECT_EQ(test, converted);
}

TEST(TMatrix_Operators, Equal) {
	TMatrix<int> m1, m2(10);
	TMatrix<int> m3(11);
	for (int i = 0; i < m1.GetSize(); ++i) {
		m1[i] = get_rand_vect(m1.GetSize(), i);
	}
	for (int i = 0; i < m1.GetSize(); ++i) {
		for (int j = i; j < m1.GetSize(); ++j) {
			m2[i][j] = m1[i][j];
		}
	}
	EXPECT_TRUE(m1 == m2);
	m2[0][0] = m1[0][0] + 1;
	EXPECT_FALSE(m1 == m2);
	EXPECT_FALSE(m1 == m3);
}

TEST(TMatrix_Operators, Not_Equal) {
	TMatrix<int> m1, m2(10);
	TMatrix<int> m3(11);
	for (int i = 0; i < m1.GetSize(); ++i) {
		m1[i] = get_rand_vect(m1.GetSize(), i);
	}
	for (int i = 0; i < m1.GetSize(); ++i) {
		for (int j = i; j < m1.GetSize(); ++j) {
			m2[i][j] = m1[i][j];
		}
	}
	EXPECT_FALSE(m1 != m2);
	m2[0][0] = m1[0][0] + 1;
	EXPECT_TRUE(m1 != m2);
	EXPECT_TRUE(m1 != m3);
}

TEST(TMatrix_Operators, Assignment) {
	TMatrix<int> m, cp(15);
	for (int i = 0; i < m.GetSize(); ++i) {
		m[i] = get_rand_vect(m.GetSize(), i);
	}
	EXPECT_NO_THROW(cp = m);
	cp = m;
	EXPECT_EQ(cp, cp = m);
}

TEST(TMatrix_Operators, Self_Assignment) {
	TMatrix<int> m;
	for (int i = 0; i < m.GetSize(); ++i) {
		m[i] = get_rand_vect(m.GetSize(), i);
	}
	EXPECT_NO_THROW(m = m);
	TMatrix<int> before(m);
	EXPECT_EQ(before, m = m);
}

TEST(TMatrix_Operators, Addition) {
	TMatrix<int> first, second;
	for (int i = 0; i < first.GetSize(); ++i) {
		first[i] = get_rand_vect(first.GetSize(), i);
		second[i] = get_rand_vect(second.GetSize(), i);
	}
	TMatrix<int> sum;
	for (int i = 0; i < first.GetSize(); ++i) {
		sum[i] = first[i] + second[i];
	}
	EXPECT_EQ(sum, first + second);
}

TEST(TMatrix_Operators, Subtraction) {
	TMatrix<int> first, second;
	for (int i = 0; i < first.GetSize(); ++i) {
		first[i] = get_rand_vect(first.GetSize(), i);
		second[i] = get_rand_vect(second.GetSize(), i);
	}
	TMatrix<int> diff;
	for (int i = 0; i < first.GetSize(); ++i) {
		diff[i] = first[i] - second[i];
	}
	EXPECT_EQ(diff, first - second);
}

TEST(TMatrix_Exceptions, Size_Constructor) {
	EXPECT_THROW(TMatrix<int>(-1), std::invalid_argument);
	EXPECT_THROW(TMatrix<int>(MAX_MATRIX_SIZE + 1), std::invalid_argument);
}

TEST(TMatrix_Exceptions, Converting_Constructor) {
	TVector<TVector<int>> wrong_si(2, 1), wrong_size_of_rows(3, 0);
	wrong_size_of_rows[0] = TVector<int>(3, 0);
	wrong_size_of_rows[1] = TVector<int>(2, 1);
	wrong_size_of_rows[2] = TVector<int>(3, 2);
	EXPECT_THROW(TMatrix<int> t(wrong_si), std::invalid_argument);
	EXPECT_THROW(TMatrix<int> t(wrong_size_of_rows), std::invalid_argument);
}

TEST(TMatrix_Exceptions, Operators) {
	TMatrix<int> m1(3), m2(2);
	EXPECT_THROW(m1 - m2, std::invalid_argument);
	EXPECT_THROW(m1 + m2, std::invalid_argument);
}