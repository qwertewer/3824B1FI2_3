#include "pch.h"
#include "Classes.h"

//Тесты Stack
TEST(TestNameStackNoExcept, TestNameStackCheck) {
	EXPECT_NO_THROW({
		TStack<int> S;
		S.push(5);
		S.push(8);
		S.top();
		S.pop();
		S.empty();
		S.size();
		});
}

TEST(TestNameStackCheckExceptions, TestNameStackExcept) {
	TStack<int> S;
	EXPECT_ANY_THROW({
		S.top();
		});
	EXPECT_ANY_THROW({
		S.pop();
		});
}

//Тесты TPostfix
TEST(TestNameOperandsOnly, TestNameOperands) {
	TPostfix calculator1;
	std::string expression1 = "5";
	double result1 = calculator1.evaluate(expression1);
	EXPECT_EQ(result1, 5);

	TPostfix calculator2;
	std::string expression2 = "3";
	double result2 = calculator2.evaluate(expression2);
	EXPECT_EQ(result2, 3);

	TPostfix calculator3;
	std::string expression3 = "1";
	double result3 = calculator3.evaluate(expression3);
	EXPECT_EQ(result3, 1);

}

TEST(TestNameVariablesOnly, TestNameOperands) {
	TPostfix calculator1;
	std::string expression1 = "a";
	calculator1.setVariable("a", 6);
	double result1 = calculator1.evaluate(expression1);
	EXPECT_EQ(result1, 6);

	TPostfix calculator2;
	std::string expression2 = "a";
	calculator2.setVariable("a", 11);
	double result2 = calculator2.evaluate(expression2);
	EXPECT_EQ(result2, 11);

	TPostfix calculator3;
	std::string expression3 = "-a";
	calculator3.setVariable("a", 4);
	double result3 = calculator3.evaluate(expression3);
	EXPECT_EQ(result3, -4);

}
TEST(TestNameTPostfixNoExeptIntegersSimple, TestNameTPostfixIntegersSimple) {
	TPostfix calculator1;
	std::string expression1 = "5+3";
	double result1 = calculator1.evaluate(expression1);
	EXPECT_EQ(result1, 8);

	TPostfix calculator2;
	std::string expression2 = "5-3";
	double result2 = calculator2.evaluate(expression2);
	EXPECT_EQ(result2, 2);

	TPostfix calculator3;
	std::string expression3 = "5*3";
	double result3 = calculator3.evaluate(expression3);
	EXPECT_EQ(result3, 15);

	TPostfix calculator4;
	std::string expression4 = "5/2";
	double result4 = calculator4.evaluate(expression4);
	EXPECT_EQ(result4, 2.5);
}

TEST(TestNameTPostfixNoExeptFloatsSimple, TestNameTPostfixFloatsSimple) {
	TPostfix calculator1;
	std::string expression1 = "5.05+3.1";
	double result1 = calculator1.evaluate(expression1);
	EXPECT_TRUE(pow(result1 - 8.15, 2) < 0.00001);

	TPostfix calculator2;
	std::string expression2 = "5.45-3.3";
	double result2 = calculator2.evaluate(expression2);
	EXPECT_TRUE(pow(result2 - 2.15, 2) < 0.00001);

	TPostfix calculator3;
	std::string expression3 = "5*3.5";
	double result3 = calculator3.evaluate(expression3);
	EXPECT_TRUE(pow(result3 - 17.5, 2) < 0.00001);

	TPostfix calculator4;
	std::string expression4 = "5/2.5";
	double result4 = calculator4.evaluate(expression4);
	EXPECT_TRUE(pow(result4 - 2, 2) < 0.00001);
}

TEST(TestNameTPostfixNoExeptIntegersComplicated, TestNameTPostfixIntegersSimple) {
	TPostfix calculator1;
	std::string expression1 = "5+3+-2*5";
	double result1 = calculator1.evaluate(expression1);
	EXPECT_EQ(result1, -2);

	TPostfix calculator2;
	std::string expression2 = "5-3/2+-1";
	double result2 = calculator2.evaluate(expression2);
	EXPECT_EQ(result2, 2.5);

	TPostfix calculator3;
	std::string expression3 = "5*-3+2-7";
	double result3 = calculator3.evaluate(expression3);
	EXPECT_EQ(result3, -20);

	TPostfix calculator4;
	std::string expression4 = "5/-2+5*2";
	double result4 = calculator4.evaluate(expression4);
	EXPECT_EQ(result4, 7.5);
}

TEST(TestNameTPostfixNoExeptFloatsComplicated, TestNameTPostfixFloatsSimple) {
	TPostfix calculator1;
	std::string expression1 = "5.05+-3.1*2.3";
	double result1 = calculator1.evaluate(expression1);
	EXPECT_TRUE(pow(result1 - -2.08, 2) < 0.00001);

	TPostfix calculator2;
	std::string expression2 = "5.45*-3.3/1.1";
	double result2 = calculator2.evaluate(expression2);
	EXPECT_TRUE(pow(result2 + 16.35, 2) < 0.00001);

	TPostfix calculator3;
	std::string expression3 = "5.1*3.5/-14";
	double result3 = calculator3.evaluate(expression3);
	EXPECT_TRUE(pow(result3 + 1.275, 2) < 0.00001);

	TPostfix calculator4;
	std::string expression4 = "5.75/2.5-9.3/3";
	double result4 = calculator4.evaluate(expression4);
	EXPECT_TRUE(pow(result4 + 0.8, 2) < 0.00001);
}

TEST(TestNameTPostfixNoExceptRoundBrackets, TestNameBracketsBothIntAndFloat) {
	TPostfix calculator1;
	std::string expression1 = "2*(5+3)+(-2*5+4)";
	double result1 = calculator1.evaluate(expression1);
	EXPECT_EQ(result1, 10);

	TPostfix calculator2;
	std::string expression2 = "(5-3)/(2+-1)";
	double result2 = calculator2.evaluate(expression2);
	EXPECT_EQ(result2, 2);

	TPostfix calculator3;
	std::string expression3 = "5.1*(3.5-1.3)";
	double result3 = calculator3.evaluate(expression3);
	EXPECT_TRUE(pow(result3 - 11.22, 2) < 0.00001);

	TPostfix calculator4;
	std::string expression4 = "5.7*(2.5-4.6)/3";
	double result4 = calculator4.evaluate(expression4);
	EXPECT_TRUE(pow(result4 + 3.99, 2) < 0.00001);
}

TEST(TestNameTPostfixExceptions, TestNameTPostfixExcept) {
	EXPECT_ANY_THROW({
		TPostfix calculator1;
		std::string expression1 = "*5+3+-2+*5";
		double result1 = calculator1.evaluate(expression1);
		});
	EXPECT_ANY_THROW({
		TPostfix calculator1;
		std::string expression1 = "5-+3+-2*5";
		double result1 = calculator1.evaluate(expression1);
		});
	EXPECT_ANY_THROW({
		TPostfix calculator1;
		std::string expression1 = "5+3+-2+5-";
		double result1 = calculator1.evaluate(expression1);
		});
	EXPECT_ANY_THROW({
		TPostfix calculator1;
		std::string expression1 = "5+3+-2*+5";
		double result1 = calculator1.evaluate(expression1);
		});
	EXPECT_ANY_THROW({
		TPostfix calculator1;
		std::string expression1 = "()5+3+-2*5";
		double result1 = calculator1.evaluate(expression1);
		});
	EXPECT_ANY_THROW({
		TPostfix calculator1;
		std::string expression1 = "5*3.2+5(";
		double result1 = calculator1.evaluate(expression1);
		});
}

TEST(TestNameVariablesNoExcept, TestNameVariablesCheck) {
	TPostfix calculator;
	std::string expression = "a+3*b";

	calculator.setVariable("a", 2);
	calculator.setVariable("b", 4);

	double result = calculator.evaluate(expression);

	EXPECT_EQ(result, 14);
	calculator.clearVariables();

	std::string expression1 = "5*a/(3*b)";

	calculator.setVariable("a", 6);
	calculator.setVariable("b", 5);

	double result1 = calculator.evaluate(expression1);

	EXPECT_EQ(result1, 2);
	calculator.clearVariables();

	std::string expression2 = "3*a-7*b+5";

	calculator.setVariable("a", 3);
	calculator.setVariable("b", 2);

	double result2 = calculator.evaluate(expression2);

	EXPECT_EQ(result2, 0);
	calculator.clearVariables();

	std::string expression3 = "((a+b)*-a)";

	calculator.setVariable("a", 3);
	calculator.setVariable("b", 2);

	double result3 = calculator.evaluate(expression3);

	EXPECT_EQ(result3, -15);
}

TEST(TestCaseNameVariablesExceptions, TestNameVarExcept) {
	TPostfix calculator;
	EXPECT_ANY_THROW({
		std::string expression = "a+3*b-";
		calculator.setVariable("a", 2);
		calculator.setVariable("b", 4);
		double result = calculator.evaluate(expression);
		});

	EXPECT_ANY_THROW({
		std::string expression = "a+3*b)";
		calculator.setVariable("a", 2);
		calculator.setVariable("b", 4);
		double result = calculator.evaluate(expression);
		});

	EXPECT_ANY_THROW({
		std::string expression = "a*+3*b";
		calculator.setVariable("a", 2);
		calculator.setVariable("b", 4);
		double result = calculator.evaluate(expression);
		});
}

TEST(TestCaseNameSinus, TestNameSin) {
	EXPECT_NO_THROW({
		TPostfix calculator;
		std::string expression = "sin(a)+b";
		calculator.setVariable("a", 2);
		calculator.setVariable("b", 4);
		double result = calculator.evaluate(expression);
		});
	EXPECT_NO_THROW({
		TPostfix calculator;
		std::string expression = "sin(1)*13";
		double result = calculator.evaluate(expression);
		});
	EXPECT_NO_THROW({
		TPostfix calculator;
		std::string expression = "sin(10)-0.11";
		double result = calculator.evaluate(expression);
		});
	EXPECT_ANY_THROW({
		TPostfix calculator;
		std::string expression = "sin*0.11";
		double result = calculator.evaluate(expression);
		});
	EXPECT_ANY_THROW({
		TPostfix calculator;
		std::string expression = "sin10-0.11";
		double result = calculator.evaluate(expression);
		std::cout << result << "\n";
		});
}

TEST(TestCaseNameUnaryMinusCheck, TestNameUnaryMinus) {
	TPostfix calculator1;
	std::string expression1 = "a*a+a*b-b";
	calculator1.setVariable("a", 2);
	calculator1.setVariable("b", 4);
	double result1 = calculator1.evaluate(expression1);
	EXPECT_EQ(result1, 8);

	TPostfix calculator2;
	std::string expression2 = "b/(a+a)+a";
	calculator2.setVariable("a", 2);
	calculator2.setVariable("b", 4);
	double result2 = calculator2.evaluate(expression2);
	EXPECT_EQ(result2, 3);

	TPostfix calculator3;
	std::string expression3 = "a*b+b*2-a*3";
	calculator3.setVariable("a", 0);
	calculator3.setVariable("b", 3);
	double result3 = calculator3.evaluate(expression3);
	EXPECT_EQ(result3, 6);
}

TEST(TestCaseNameSameVariables, TestNameSameVariables) {
	TPostfix calculator1;
	std::string expression1 = "5+-4*-1";
	double result1 = calculator1.evaluate(expression1);
	EXPECT_EQ(result1, 9);

	TPostfix calculator2;
	std::string expression2 = "-1/-2+0.5+-1";
	double result2 = calculator2.evaluate(expression2);
	EXPECT_EQ(result2, 0);

	TPostfix calculator3;
	std::string expression3 = "(9+-6)*-3";
	double result3 = calculator3.evaluate(expression3);
	EXPECT_EQ(result3, -9);
}