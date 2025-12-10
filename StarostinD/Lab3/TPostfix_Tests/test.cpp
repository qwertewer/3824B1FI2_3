#include "pch.h"
#include "..\Lab3\TPostfix.h"
#include "..\Lab3\TPostfix.cpp"

using namespace std;

bool compare_vectors(vector<string>& lhs, vector<string>& rhs) {
	if (lhs.size() != rhs.size()) return false;
	for (int i = 0; i < lhs.size(); ++i) {
		if (lhs[i] != rhs[i]) return false;
	}
}

TEST(Constructor, one_operation_no_throw) {
	EXPECT_NO_THROW(TPostfix("A + b"));
	EXPECT_NO_THROW(TPostfix("c - d"));
	EXPECT_NO_THROW(TPostfix("aaa / b"));
	EXPECT_NO_THROW(TPostfix("ab * bc"));
	EXPECT_NO_THROW(TPostfix("-a"));
	EXPECT_NO_THROW(TPostfix("cos(a)"));
}

TEST(Constructor, two_unar_operators_in_row) {
	EXPECT_NO_THROW(TPostfix("-cos(a)"));
	EXPECT_NO_THROW(TPostfix("cos(-a)"));
}

TEST(Constructor, complex_formulas) {
	EXPECT_NO_THROW(TPostfix("cos((A + b * c) / 2)"));
	EXPECT_NO_THROW(TPostfix("(c * d - d) + -cos(14.1 * a)"));
	EXPECT_NO_THROW(TPostfix("cos(cos(cos(-a)))"));
	EXPECT_NO_THROW(TPostfix("(a-b)*(a+b) - 0.1"));
	EXPECT_NO_THROW(TPostfix("1 + -cos(x) * -cos(x)"));
	EXPECT_NO_THROW(TPostfix("(a + b) * (c + d) / (h + k)"));
}

TEST(GetInfix, is_correct) {
	TPostfix t("a + b");
	EXPECT_EQ("a + b", t.GetInfix());
}

TEST(GetPostfix, is_correct) {
	TPostfix t1("a + b");
	TPostfix t2("cos(cos(cos(-a)))");
	TPostfix t3("(a + b * c) * (c / d - e)");
	EXPECT_EQ("ab+", t1.GetPostfix());
	EXPECT_EQ("a~^^^", t2.GetPostfix());
	EXPECT_EQ("abc*+cd/e-*", t3.GetPostfix());
}

TEST(GetOperands, is_correct) {
	TPostfix t1("a + b");
	TPostfix t2("cos(cos(cos(-a)))");
	TPostfix t3("(a + b * c) * (c / d - a)");
	vector<string> ops;
	EXPECT_TRUE(compare_vectors(vector<string>({ "a", "b" }), t1.GetOperands()));
	EXPECT_TRUE(compare_vectors(vector<string>({ "a" }), t2.GetOperands()));
	EXPECT_TRUE(compare_vectors(vector<string>({ "a", "b" , "c", "d" }), t3.GetOperands()));
}

TEST(Calculate, is_correct_and_no_throw) {
	TPostfix t1("cos(cos(cos(-a)))");
	vector<pair<string, double>> ops ={ {"a", 1} };
	EXPECT_NO_THROW(t1.Calculate(ops));
	EXPECT_EQ(t1.Calculate(ops), cos(cos(cos(-1))));
	TPostfix t2("(a + b * cd) * (cd / d - a)");
	ops = { {"a" , 1}, {"b", 2 }, {"cd", 3.2}, {"d", 4} };
	EXPECT_NO_THROW(t2.Calculate(ops));
	EXPECT_EQ(t2.Calculate(ops), (1 + 2 * 3.2) * (3.2 / 4. - 1));
	TPostfix t3("b - a");
	ops = { {"a", 2 }, { "b", 1 } };
	EXPECT_NO_THROW(t3.Calculate(ops));
	EXPECT_EQ(t3.Calculate(ops),1 - 2 );
	ops = { {"a", 2 }, { "b", 1 } , {"Pi", 3.14} };
	EXPECT_NO_THROW(t3.Calculate(ops));
	EXPECT_EQ(t3.Calculate(ops), 1 - 2);
}

TEST(Calculate, throw_) {
	TPostfix t1("cos(cos(cos(-a)))");
	vector<pair<string, double>> ops = { {"c", 1} };
	EXPECT_THROW(t1.Calculate(ops), invalid_argument);
	TPostfix t2("b - a");
	EXPECT_THROW(t2.Calculate(ops), invalid_argument);
}

TEST(Parse, brackets_throw) {
	EXPECT_THROW(TPostfix("cos((x)"), invalid_argument);
	EXPECT_THROW(TPostfix(")(a"), invalid_argument);
	EXPECT_THROW(TPostfix("(a + b) + ( a * 2))"), invalid_argument);
	EXPECT_THROW(TPostfix("((a + b)"), invalid_argument);
	EXPECT_THROW(TPostfix("(a + b + )"), invalid_argument);
	EXPECT_THROW(TPostfix("a(a + b)"), invalid_argument);
}

TEST(Parse, variables_throw) {
	EXPECT_THROW(TPostfix("a a + b"), invalid_argument);
	EXPECT_THROW(TPostfix("a / b c"), invalid_argument);
	EXPECT_THROW(TPostfix("2 a + b"), invalid_argument);
	EXPECT_THROW(TPostfix("a / 3 b"), invalid_argument);
}

TEST(Parse, digits_throw) {
	EXPECT_THROW(TPostfix("a 2 + 3"), invalid_argument);
	EXPECT_THROW(TPostfix("4 / c 3"), invalid_argument);
	EXPECT_THROW(TPostfix("2 5 + 1"), invalid_argument);
	EXPECT_THROW(TPostfix("1 / 6. 3"), invalid_argument);
}

TEST(Parse, point_throw) {
	EXPECT_THROW(TPostfix("2.3.4 + a"), invalid_argument);
}

TEST(Parse, unar_minus_throw) {
	EXPECT_THROW(TPostfix("a + --b"), invalid_argument);
	EXPECT_THROW(TPostfix("a - --b"), invalid_argument);
}

TEST(Parse, operations_throw) {
	EXPECT_THROW(TPostfix("a + + b"), invalid_argument);
	EXPECT_THROW(TPostfix("a + / b"), invalid_argument);
	EXPECT_THROW(TPostfix("a + * b"), invalid_argument);
	EXPECT_THROW(TPostfix("a - + b"), invalid_argument);
	EXPECT_THROW(TPostfix("a - / b"), invalid_argument);
	EXPECT_THROW(TPostfix("a - * b"), invalid_argument);
	EXPECT_THROW(TPostfix("a * + b"), invalid_argument);
	EXPECT_THROW(TPostfix("a * / b"), invalid_argument);
	EXPECT_THROW(TPostfix("a * * b"), invalid_argument);
	EXPECT_THROW(TPostfix("a / + b"), invalid_argument);
	EXPECT_THROW(TPostfix("a / / b"), invalid_argument);
	EXPECT_THROW(TPostfix("a / * b"), invalid_argument);
	EXPECT_THROW(TPostfix("( + a + b)"), invalid_argument);
	EXPECT_THROW(TPostfix("( / a + b)"), invalid_argument);
	EXPECT_THROW(TPostfix("b + "), invalid_argument);
	EXPECT_THROW(TPostfix(" / b"), invalid_argument);
	EXPECT_THROW(TPostfix(" * b"), invalid_argument);

}

TEST(Parse, unknown_symbol) {
	EXPECT_THROW(TPostfix("a + @"), invalid_argument);
}
