#include "pch.h"
#include "..\utmatrix.cpp"
TEST(TVectorTestsGroup0, HandleConstructor_0) {
	TVector<int> vector1;
	EXPECT_EQ(vector1.GetSize(), 10);
	EXPECT_EQ(vector1.GetStartIndex(), 0);
}
TEST(TVectorTestsGroup0, HandleConstructor_0_0) {
	TVector<int> vector1(10, 0);
	for (size_t i = 0; i < vector1.GetSize(); i++) {
		EXPECT_EQ(vector1[i], 0);
	}
}
TEST(TVectorTestsGroup0, HandleConstructor_0_DifType) {
	TVector<double> vector1;
	for (size_t i = 0; i < vector1.GetSize(); i++) {
		EXPECT_EQ(vector1[i], 0);
	}
	EXPECT_EQ(vector1.GetSize(), 10);
	EXPECT_EQ(vector1.GetStartIndex(), 0);
}
TEST(TVectorTestsGroup0, HandleConstructor_0_Bad) {
	EXPECT_THROW(TVector<double> vector1(MAX_VECTOR_SIZE + 1, 0), invalid_argument);
	EXPECT_THROW(TVector<int> vector1(-1, 0), invalid_argument);
	EXPECT_THROW(TVector<int> vector1(10, -1), out_of_range);
	EXPECT_THROW(TVector<int> vector1(10, 11), out_of_range);
}
TEST(TVectorTestsGroup0, HandleConstructor_Zero) {
	EXPECT_NO_THROW(TVector<int> vector1(0, 0));
	TVector<int> vector1(0, 0);
	EXPECT_EQ(vector1.GetSize(), 0);
	EXPECT_EQ(vector1.GetStartIndex(), 0);
}
TEST(TVectorTestsGroup1, HandleCopyConstructor) {
	TVector<int> vector1(3, 0);
	EXPECT_ANY_THROW(vector1[-1]);
	EXPECT_NO_THROW(vector1[0] = 1);
	vector1[0] = 1;
	EXPECT_NO_THROW(vector1[1] = 2);
	vector1[1] = 2;
	EXPECT_NO_THROW(vector1[2] = 3);
	vector1[2] = 3;
	EXPECT_ANY_THROW(vector1[3] = 4);
	TVector<int> vector2(vector1);
	EXPECT_EQ(vector1.GetSize(), vector2.GetSize());
	EXPECT_EQ(vector1.GetStartIndex(), vector2.GetStartIndex());
	EXPECT_NO_THROW(vector1 == vector2);
	for (size_t i = 0; i < vector1.GetSize(); i++) {
		EXPECT_EQ(vector1[i], vector2[i]);
	}
	EXPECT_TRUE(vector1 == vector2);
}
TEST(TVectorTestsGroup1, HandleCopyConstructor_Zero) {
	TVector<int> vector1(0, 0);
	TVector<int> vector2(vector1);
	EXPECT_EQ(vector2.GetSize(), 0);
	EXPECT_EQ(vector2.GetStartIndex(), 0);
}
TEST(TVectorTestsGroup2, HandleOperatorBracket) {
	TVector<int> vector1(3, 1);
	vector1[1] = 67;
	vector1[2] = 42;
	EXPECT_EQ(vector1[1], 67);
	EXPECT_EQ(vector1[2], 42);
}
TEST(TVectorTestsGroup2, HandleOperatorBracket_Bad) {
	TVector<int> vector1(3, 1);
	vector1[1] = 67;
	vector1[2] = 42;
	EXPECT_THROW(vector1[0], out_of_range);
	EXPECT_THROW(vector1[3], out_of_range);
}
TEST(TVectorTestsGroup2, HandleOperatorEqual) {
	TVector<int> vector1(3, 1);
	TVector<int> vector2(3, 1);
	TVector<int> vector3(4, 1);
	TVector<int> vector4(3, 0);
	TVector<int> vector0_1(0, 0);
	TVector<int> vector0_2(0, 0);
	EXPECT_TRUE(vector1 == vector2);
	EXPECT_TRUE(vector0_1 == vector0_2);
	EXPECT_FALSE(vector0_1 == vector1);
	EXPECT_FALSE(vector1 == vector3);
	EXPECT_FALSE(vector1 == vector4);
}
TEST(TVectorTestsGroup2, HandleOperatorsEqual_DifVals) {
	TVector<int> vector1(3, 1);
	TVector<int> vector2(3, 1);
	vector1[1] = 1;
	vector1[2] = 2;
	vector2[1] = 2;
	vector2[2] = 1;
	EXPECT_FALSE(vector1 == vector2);
}

TEST(TVectorTestsGroup2, HandleOperatorInEqual) {
	TVector<int> vector1(3, 1);
	TVector<int> vector2(3, 1);
	TVector<int> vector3(4, 1);
	TVector<int> vector4(3, 0);
	TVector<int> vector0_1(0, 0);
	TVector<int> vector0_2(0, 0);
	EXPECT_FALSE(vector1 != vector2);
	EXPECT_FALSE(vector0_1 != vector0_2);
	EXPECT_TRUE(vector0_1 != vector1);
	EXPECT_TRUE(vector1 != vector3);
	EXPECT_TRUE(vector1 != vector4);
}
TEST(TVectorTestsGroup2, HandleOperatorsInEqual_DifVals) {
	TVector<int> vector1(3, 1);
	TVector<int> vector2(3, 1);
	vector1[1] = 1;
	vector1[2] = 2;
	vector2[1] = 2;
	vector2[2] = 1;
	EXPECT_TRUE(vector1 != vector2);
	EXPECT_FALSE(vector1 == vector2);
}
TEST(TVectorTestsGroup2, HandleOperatorsAssignment) {
	TVector<int> vector1(3, 1);
	vector1[1] = 4; vector1[2] = 6;
	TVector<int> vector2(1, 0);
	vector2 = vector1;
	EXPECT_EQ(vector2.GetSize(), vector1.GetSize());
	EXPECT_EQ(vector2.GetStartIndex(), vector1.GetStartIndex());
	EXPECT_TRUE(vector1 == vector2);
}
TEST(TVectorTestsGroup2, HandleOperatorsAssignment_Self) {
	TVector<int> vector1(3, 1);
	vector1[1] = 4; vector1[2] = 6;
	vector1 = vector1;
	EXPECT_EQ(vector1.GetSize(), 3);
	EXPECT_EQ(vector1[1], 4);
	EXPECT_EQ(vector1[2], 6);
}
TEST(TVectorTestsGroup2, HandleOperatorsAssignment_Zero) {
	TVector<int> vector1(0, 0);
	TVector<int> vector2(3, 1);
	vector2 = vector1;
	EXPECT_TRUE(vector1 == vector2);
}
TEST(TVectorTestsGroup2, HandleOperatorsSkalyarSummation) {
	TVector<int> vector1(3, 1);
	vector1[1] = 4; vector1[2] = 6;
	TVector<int> result = vector1 + 2;
	EXPECT_EQ(result[0], 2);
	EXPECT_EQ(result[1], 6);
	EXPECT_EQ(result[2], 8);
}
TEST(TVectorTestsGroup2, HandleOperatorsSkalyarSubstraction) {
	TVector<int> vector1(3, 1);
	vector1[1] = 4; vector1[2] = 6;
	TVector<int> result = vector1 - 2;
	EXPECT_EQ(result[0], -2);
	EXPECT_EQ(result[1], 2);
	EXPECT_EQ(result[2], 4);
}
TEST(TVectorTestsGroup2, HandleOperatorsSkalyarMultiplation) {
	TVector<int> vector1(3, 1);
	vector1[1] = 4; vector1[2] = 6;
	TVector<int> result = vector1 * 2;
	EXPECT_EQ(result[0], 0);
	EXPECT_EQ(result[1], 8);
	EXPECT_EQ(result[2], 12);
}
TEST(TVectorTestsGroup2, HandleOperatorsVectorAddition) {
	TVector<int> vector1(3, 1);
	vector1[1] = 3; vector1[2] = 6;
	TVector<int> vector2(3, 0);
	vector2[0] = 5; vector2[2] = 2;
	TVector<int> result = vector1 + vector2;
	EXPECT_EQ(result[0], 5);
	EXPECT_EQ(result[1], 3);
	EXPECT_EQ(result[2], 8);
	TVector<int> vector3(3, 2);
	vector3[2] = 4;
	result = vector1 + vector3;
	EXPECT_THROW(result[0], out_of_range);
	EXPECT_EQ(result[1], 3);
	EXPECT_EQ(result[2], 10);
	TVector<int> vector4(4, 0);
	EXPECT_THROW(result = vector1 + vector4, invalid_argument);
}
TEST(TVectorTestsGroup2, HandleOperatorsVectorSubstraction) {
	TVector<int> vector1(3, 1);
	vector1[1] = 3; vector1[2] = 6;
	TVector<int> vector2(3, 0);
	vector2[0] = 5; vector2[2] = 2;
	TVector<int> result = vector1 - vector2;
	EXPECT_EQ(result.GetSize(), 3);
	EXPECT_EQ(result.GetStartIndex(), 0);
	EXPECT_EQ(result[0], -5);
	EXPECT_EQ(result[1], 3);
	EXPECT_EQ(result[2], 4);
	TVector<int> vector3(3, 2);
	vector3[2] = 4;
	result = vector1 - vector3;
	EXPECT_THROW(result[0], out_of_range);
	EXPECT_EQ(result[1], 3);
	EXPECT_EQ(result[2], 2);
	TVector<int> vector4(4, 0);
	EXPECT_THROW(result = vector1 + vector4, invalid_argument);
}
TEST(TVectorTestsGroup2, HandleOperatorsVectorSubstraction_0) {
	TVector<int> vector1(0, 0);
	TVector<int> vector2(0, 0);
	TVector<int> vector3(3, 0);
	EXPECT_NO_THROW(TVector<int> result = vector1-vector2);
	TVector<int> result = vector1 - vector2;
	EXPECT_THROW(TVector<int> result = vector1 - vector3, invalid_argument);
}
TEST(TVectorTestsGroup2, HandleOperatorsVectorMultiplication) {
	TVector<int> vector1(3, 1);
	vector1[1] = 3; vector1[2] = 6;
	TVector<int> vector2(3, 0);
	vector2[0] = 5; vector2[2] = 2;
	TVector<int> vector3(4, 0);
	TVector<int> vector4(3, 1);
	vector4[1] = 10; vector4[2] = 10;
	EXPECT_NO_THROW(int result = vector1 * vector2);
	EXPECT_THROW(int result = vector1 * vector3, invalid_argument);
	int result = vector1 * vector2;
	EXPECT_EQ(result, 12);
	result = vector1 * vector4;
	EXPECT_EQ(result, 90);
}
TEST(TVectorTestsGroup2, HandleOperatorsVectorMultiplication_0) {
	TVector<int> vector1(0, 0);
	TVector<int> vector2(0, 0);
	EXPECT_NO_THROW(int result = vector1 * vector2);
	int result = vector1 * vector2;
	EXPECT_EQ(result, 0);
}
TEST(TVectorTestsGroup3, HandleOperatorsInput) {
	TVector<int> vector1(3, 0);
	istringstream input("1 2 3");
	input >> vector1;
	EXPECT_EQ(vector1[0], 1);
	EXPECT_EQ(vector1[1], 2);
	EXPECT_EQ(vector1[2], 3);
}
TEST(TVectorTestsGroup3, HandleOperatorsInput_0) {
	TVector<int> vector1(0, 0);
	istringstream input("1 2 3");
	EXPECT_THROW(input >> vector1, out_of_range);
}
TEST(TVectorTestsGroup3, HandleOperatorsOutput) {
	TVector<int> vector1(3, 0);
	vector1[0] = 1; vector1[1] = 2; vector1[2] = 3;
	ostringstream output;
	output << vector1;
	EXPECT_EQ(output.str(), "1 2 3 \n");
}
TEST(TVectorTestsGroup3, HandleOperatorsOutput_DifStartIndex) {
	TVector<int> vector2(4, 1);
	vector2[1] = 1; vector2[2] = 2; vector2[3] = 3;
	ostringstream output;
	output << vector2;
	EXPECT_EQ(output.str(), "0 1 2 3 \n");
}
TEST(TVectorTestsGroup3, HandleOperatorsOutput_0) {
	TVector<int> vector2(0, 0);
	ostringstream output;
	output << vector2;
	EXPECT_EQ(output.str(), "null\n");
}

TEST(TMatrixTestsGroup0, HandleConstructor) {
	TMatrix<int> m(3);
	EXPECT_EQ(m.GetSize(), 3);

	// Check triangular structure
	EXPECT_EQ(m[0].GetSize(), 3);
	EXPECT_EQ(m[1].GetSize(), 3);
	EXPECT_EQ(m[2].GetSize(), 3);

	EXPECT_EQ(m[0].GetStartIndex(), 0);
	EXPECT_EQ(m[1].GetStartIndex(), 1);
	EXPECT_EQ(m[2].GetStartIndex(), 2);
}
TEST(TMatrixTestsGroup0, HandleConstructor_0) {
	TMatrix<int> m;
	EXPECT_EQ(m.GetSize(), 10);
}

TEST(TMatrixTestsGroup0, HandleConstructor_Bad) {
	EXPECT_THROW(TMatrix<int> m(-1), invalid_argument);
	EXPECT_THROW(TMatrix<int> m(MAX_MATRIX_SIZE + 1), invalid_argument);
}

TEST(TMatrixTestsGroup1, HandleCopyConstructor) {
	TMatrix<int> m1(2);
	m1[0][0] = 1; m1[0][1] = 2;
	m1[1][1] = 3;

	TMatrix<int> m2(m1);
	EXPECT_EQ(m2.GetSize(), 2);
	EXPECT_EQ(m2[0][0], 1);
	EXPECT_EQ(m2[0][1], 2);
	EXPECT_EQ(m2[1][1], 3);
}

TEST(TMatrixTestsGroup2, HandleOperatorsAssignment) {
	TMatrix<int> m1(2);
	m1[0][0] = 1; m1[0][1] = 2;
	m1[1][1] = 3;

	TMatrix<int> m2(1);
	m2 = m1;

	EXPECT_EQ(m2.GetSize(), 2);
	EXPECT_EQ(m2[0][0], 1);
	EXPECT_EQ(m2[0][1], 2);
	EXPECT_EQ(m2[1][1], 3);
}

TEST(TMatrixTestsGroup2, HandleOperatorsEqual) {
	TMatrix<int> m1(2);
	m1[0][0] = 1; m1[0][1] = 2;
	m1[1][1] = 3;

	TMatrix<int> m2(2);
	m2[0][0] = 1; m2[0][1] = 2;
	m2[1][1] = 3;

	EXPECT_TRUE(m1 == m2);
	TMatrix<int> m3(2);
	m2[0][0] = 1; m2[0][1] = 2;
	m2[1][1] = 4;

	EXPECT_FALSE(m1 == m3);
}

TEST(TMatrixTestsGroup2, HandleOperatorsInEqual) {
	TMatrix<int> m1(2);
	TMatrix<int> m2(2);
	m1[0][0] = 1; m2[0][0] = 2;

	EXPECT_TRUE(m1 != m2);
	EXPECT_FALSE(m1 == m2);
}

TEST(TMatrixTestsGroup2, HandleOperatorsSummation) {
	TMatrix<int> m1(2);
	m1[0][0] = 1; m1[0][1] = 2;
	m1[1][1] = 3;

	TMatrix<int> m2(2);
	m2[0][0] = 4; m2[0][1] = 5;
	m2[1][1] = 6;

	TMatrix<int> result = m1 + m2;

	EXPECT_EQ(result[0][0], 5);
	EXPECT_EQ(result[0][1], 7);
	EXPECT_EQ(result[1][1], 9);
}

TEST(TMatrixTestsGroup2, HandleOperatorsSubstraction) {
	TMatrix<int> m1(2);
	m1[0][0] = 10; m1[0][1] = 20;
	m1[1][1] = 30;

	TMatrix<int> m2(2);
	m2[0][0] = 1; m2[0][1] = 2;
	m2[1][1] = 3;

	// Note: There's a bug in operator- - it modifies *this instead of returning new matrix
	TMatrix<int> result = m1 - m2;

	EXPECT_EQ(result[0][0], 9);
	EXPECT_EQ(result[0][1], 18);
	EXPECT_EQ(result[1][1], 27);
}

TEST(TMatrixTestsGroup3, HandleOperatorsInput) {
	TMatrix<int> m(2);
	std::istringstream iss("1 2\n3");
	iss >> m;
	EXPECT_EQ(m[0][0], 1);
	EXPECT_EQ(m[0][1], 2);
	EXPECT_EQ(m[1][1], 3);
}

TEST(TMatrixTestsGroup3, HandleOperatorsOutput) {
	TMatrix<int> m(2);
	m[0][0] = 1; m[0][1] = 2;
	m[1][1] = 3;

	std::ostringstream oss;
	oss << m;
	EXPECT_EQ(oss.str(), "1 2 \n0 3 \n");
}
