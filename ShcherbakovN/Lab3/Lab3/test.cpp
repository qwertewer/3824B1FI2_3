#include "pch.h"
#include "..\..\Lab3\Lab3Code\RealizationTStackAndTPostfix.h"

//TStack:

TEST(TStack, CreateEmptyStackIsCorrect)
{
    TStack<double> stack1;
    EXPECT_EQ(stack1.isEmpty(), true);
    EXPECT_EQ(stack1.size(), 0);

    TStack<double> stack2;
    EXPECT_EQ(stack2.isEmpty(), true);
    EXPECT_EQ(stack2.size(), 0);
}

TEST(TStack, PushAndTopAndPopIsCorrectNoThrow)
{
    TStack<double> stack;

    stack.push(20.1);
    EXPECT_EQ(stack.isEmpty(), false);
    EXPECT_EQ(stack.size(), 1);
    EXPECT_NO_THROW(stack.top());
    EXPECT_EQ(stack.top(), 20.1);

    stack.push(12.4);
    EXPECT_EQ(stack.isEmpty(), false);
    EXPECT_EQ(stack.size(), 2);
    EXPECT_NO_THROW(stack.top());
    EXPECT_EQ(stack.top(), 12.4);

    EXPECT_NO_THROW(stack.pop());
    EXPECT_EQ(stack.isEmpty(), false);
    EXPECT_EQ(stack.size(), 1);
    EXPECT_NO_THROW(stack.top());
    EXPECT_EQ(stack.top(), 20.1);

    EXPECT_NO_THROW(stack.pop());
    EXPECT_EQ(stack.isEmpty(), true);
    EXPECT_EQ(stack.size(), 0);
}

TEST(TStack, PopAndTopAnyThrow)
{
    TStack<int> stack;
    EXPECT_EQ(stack.isEmpty(), true);

    EXPECT_THROW(stack.pop(), std::out_of_range);
    EXPECT_THROW(stack.top(), std::out_of_range);
}

//Postfix:

TEST(Postfix, SimpleExpressionsNoThrow)
{
    Postfix postfix1("a+b");
    EXPECT_EQ(postfix1.GetInfix(), "a+b");
    EXPECT_EQ(postfix1.GetPostfix(), "ab+");

    Postfix postfix2("a-b");
    EXPECT_EQ(postfix2.GetInfix(), "a-b");
    EXPECT_EQ(postfix2.GetPostfix(), "ab-");

    Postfix postfix3("a*b");
    EXPECT_EQ(postfix3.GetInfix(), "a*b");
    EXPECT_EQ(postfix3.GetPostfix(), "ab*");

    Postfix postfix4("a/b");
    EXPECT_EQ(postfix4.GetInfix(), "a/b");
    EXPECT_EQ(postfix4.GetPostfix(), "ab/");

    Postfix postfix5("exp(c)");
    EXPECT_EQ(postfix5.GetInfix(), "exp(c)");
    EXPECT_EQ(postfix5.GetPostfix(), "cexp");

    Postfix postfix6("-d");
    EXPECT_EQ(postfix6.GetInfix(), "-d");
    EXPECT_EQ(postfix6.GetPostfix(), "d~");
}

TEST(Postfix, SimpleExpressionsWithUnaryMinusNoThrow)
{
    Postfix postfix1("-(a+b)");
    EXPECT_EQ(postfix1.GetInfix(), "-(a+b)");
    EXPECT_EQ(postfix1.GetPostfix(), "ab+~");

    Postfix postfix2("-(a-b)");
    EXPECT_EQ(postfix2.GetInfix(), "-(a-b)");
    EXPECT_EQ(postfix2.GetPostfix(), "ab-~");

    Postfix postfix3("-(a*b)");
    EXPECT_EQ(postfix3.GetInfix(), "-(a*b)");
    EXPECT_EQ(postfix3.GetPostfix(), "ab*~");

    Postfix postfix4("-(a/b)");
    EXPECT_EQ(postfix4.GetInfix(), "-(a/b)");
    EXPECT_EQ(postfix4.GetPostfix(), "ab/~");

    Postfix postfix5("-exp(c)");
    EXPECT_EQ(postfix5.GetInfix(), "-exp(c)");
    EXPECT_EQ(postfix5.GetPostfix(), "cexp~");

    Postfix postfix6("-(-d)");
    EXPECT_EQ(postfix6.GetInfix(), "-(-d)");
    EXPECT_EQ(postfix6.GetPostfix(), "d~~");
}

TEST(Postfix, ComplexExpressionsWithUnaryMinusWithNumbersNoThrow)
{
    Postfix postfix1("-(a+b/(3+c))");
    EXPECT_EQ(postfix1.GetInfix(), "-(a+b/(3+c))");
    EXPECT_EQ(postfix1.GetPostfix(), "ab3c+/+~");

    Postfix postfix2("-(a-b*(7.4-exp(c)))");
    EXPECT_EQ(postfix2.GetInfix(), "-(a-b*(7.4-exp(c)))");
    EXPECT_EQ(postfix2.GetPostfix(), "ab7.4cexp-*-~");

    Postfix postfix3("-(a+v*b)");
    EXPECT_EQ(postfix3.GetInfix(), "-(a+v*b)");
    EXPECT_EQ(postfix3.GetPostfix(), "avb*+~");

    Postfix postfix4("-(a/b-0.4+n)");
    EXPECT_EQ(postfix4.GetInfix(), "-(a/b-0.4+n)");
    EXPECT_EQ(postfix4.GetPostfix(), "ab/0.4-n+~");

    Postfix postfix5("-exp(c/3*f)");
    EXPECT_EQ(postfix5.GetInfix(), "-exp(c/3*f)");
    EXPECT_EQ(postfix5.GetPostfix(), "c3/f*exp~");

    Postfix postfix6("-(-d*k-9.12)");
    EXPECT_EQ(postfix6.GetInfix(), "-(-d*k-9.12)");
    EXPECT_EQ(postfix6.GetPostfix(), "d~k*9.12-~");

    //Выражение, содержащее все операции, операнды, числа:
    Postfix postfix7("-(a+3.5*exp(b-(-2.7)))/(c-(-(d/1.25)))+(-e*(f+0.4))");
    EXPECT_EQ(postfix7.GetInfix(), "-(a+3.5*exp(b-(-2.7)))/(c-(-(d/1.25)))+(-e*(f+0.4))");
    EXPECT_EQ(postfix7.GetPostfix(), "a3.5b2.7~-exp*+~cd1.25/~-/e~f0.4+*+");
}

TEST(Postfix, ExpressionswithMultiLetterVariablesNoThrow)
{
    Postfix postfix1("(abc+b)*ug");
    EXPECT_EQ(postfix1.GetInfix(), "(abc+b)*ug");
    EXPECT_EQ(postfix1.GetPostfix(), "abcb+ug*");

    Postfix postfix2("JfK/3-yu");
    EXPECT_EQ(postfix2.GetInfix(), "JfK/3-yu");
    EXPECT_EQ(postfix2.GetPostfix(), "JfK3/yu-");
}

TEST(Postfix, IncorrectExpressionsAnyThrow)
{
    //Incorrect infix form: incorrect number input.
    EXPECT_THROW(Postfix postfix("exp2.3"), std::invalid_argument);
    EXPECT_THROW(Postfix postfix(")5.87"), std::invalid_argument);
    EXPECT_THROW(Postfix postfix("d1.3"), std::invalid_argument);
    EXPECT_THROW(Postfix postfix("dgf0.34"), std::invalid_argument);
    EXPECT_THROW(Postfix postfix("LO6.5"), std::invalid_argument);
    EXPECT_THROW(Postfix postfix("exp3"), std::invalid_argument);

    //Incorrect infix form: invalid number.
    EXPECT_THROW(Postfix postfix("5.4.6"), std::invalid_argument);

    //Incorrect infix form: incorrect input of the operand (or the exp() function).
    EXPECT_THROW(Postfix postfix("expA"), std::invalid_argument);
    EXPECT_THROW(Postfix postfix(")a"), std::invalid_argument);
    EXPECT_THROW(Postfix postfix("6.4B"), std::invalid_argument);

    //Incorrect infix form: a gap was found between the operands.
    EXPECT_THROW(Postfix postfix("a b"), std::invalid_argument);
    EXPECT_THROW(Postfix postfix("av Kj"), std::invalid_argument);

    //Incorrect infix form: incorrect entry of the opening bracket.
    EXPECT_THROW(Postfix postfix("a+5.3(b+c)"), std::invalid_argument);
    EXPECT_THROW(Postfix postfix("a+d(b+c)"), std::invalid_argument);
    EXPECT_NO_THROW(Postfix postfix("a+exp(b+c)"));
    EXPECT_NO_THROW(Postfix postfix("a+(-(b+c))"));
    EXPECT_THROW(Postfix postfix("(a+f)(b+c)"), std::invalid_argument);

    //Incorrect infix form: incorrect entry of the closing bracket.
    EXPECT_THROW(Postfix postfix(")"), std::invalid_argument);
    EXPECT_THROW(Postfix postfix("()"), std::invalid_argument);
    EXPECT_THROW(Postfix postfix("+)"), std::invalid_argument);
    EXPECT_THROW(Postfix postfix("-)"), std::invalid_argument);
    EXPECT_THROW(Postfix postfix("*)"), std::invalid_argument);
    EXPECT_THROW(Postfix postfix("/)"), std::invalid_argument);
    EXPECT_THROW(Postfix postfix("exp)"), std::invalid_argument);

    //Incorrect infix form: incorrect number of opening and closing brackets.
    EXPECT_THROW(Postfix postfix("(a+b)-c)"), std::invalid_argument);

    //Incorrect infix form: incorrect unary minus sign input.
    EXPECT_THROW(Postfix postfix("a+-b"), std::invalid_argument);
    EXPECT_THROW(Postfix postfix("a--b"), std::invalid_argument);
    EXPECT_THROW(Postfix postfix("a*-b"), std::invalid_argument);
    EXPECT_THROW(Postfix postfix("a/-b"), std::invalid_argument);

    EXPECT_THROW(Postfix postfix("a+exp-b"), std::invalid_argument);
    EXPECT_THROW(Postfix postfix("a+(--b)"), std::invalid_argument);

    //Incorrect infix form: incorrect operation input.
    EXPECT_THROW(Postfix postfix("+a"), std::invalid_argument);
    EXPECT_THROW(Postfix postfix("*a"), std::invalid_argument);
    EXPECT_THROW(Postfix postfix("/a"), std::invalid_argument);

    EXPECT_THROW(Postfix postfix("a++b"), std::invalid_argument);
    EXPECT_THROW(Postfix postfix("a-+b"), std::invalid_argument);
    EXPECT_THROW(Postfix postfix("a*+b"), std::invalid_argument);
    EXPECT_THROW(Postfix postfix("a/+b"), std::invalid_argument);
    EXPECT_THROW(Postfix postfix("a+exp+b"), std::invalid_argument);
    EXPECT_THROW(Postfix postfix("a+(+b"), std::invalid_argument);
    EXPECT_THROW(Postfix postfix("-+a"), std::invalid_argument);
    EXPECT_THROW(Postfix postfix("(-+a)"), std::invalid_argument);

    EXPECT_THROW(Postfix postfix("a+*b"), std::invalid_argument);
    EXPECT_THROW(Postfix postfix("a-*b"), std::invalid_argument);
    EXPECT_THROW(Postfix postfix("a**b"), std::invalid_argument);
    EXPECT_THROW(Postfix postfix("a/*b"), std::invalid_argument);
    EXPECT_THROW(Postfix postfix("a+exp*b"), std::invalid_argument);
    EXPECT_THROW(Postfix postfix("a+(*b"), std::invalid_argument);
    EXPECT_THROW(Postfix postfix("-*a"), std::invalid_argument);
    EXPECT_THROW(Postfix postfix("(-*a)"), std::invalid_argument);

    EXPECT_THROW(Postfix postfix("a+/b"), std::invalid_argument);
    EXPECT_THROW(Postfix postfix("a-/b"), std::invalid_argument);
    EXPECT_THROW(Postfix postfix("a*/b"), std::invalid_argument);
    EXPECT_THROW(Postfix postfix("a//b"), std::invalid_argument);
    EXPECT_THROW(Postfix postfix("a+exp/b"), std::invalid_argument);
    EXPECT_THROW(Postfix postfix("a+(/b"), std::invalid_argument);
    EXPECT_THROW(Postfix postfix("-/a"), std::invalid_argument);
    EXPECT_THROW(Postfix postfix("(-/a)"), std::invalid_argument);

    //Incorrect infix form: unknown symbol detected.
    EXPECT_THROW(Postfix postfix("a&b"), std::invalid_argument);
    EXPECT_THROW(Postfix postfix("a+b^c"), std::invalid_argument);
    EXPECT_THROW(Postfix postfix("a$b"), std::invalid_argument);

    //Incorrect infix form: the infix form cannot end with exp, +, -, *, /, (. Or: incorrect number of opening and closing brackets.
    EXPECT_THROW(Postfix postfix("a+"), std::invalid_argument);
    EXPECT_THROW(Postfix postfix("a-"), std::invalid_argument);
    EXPECT_THROW(Postfix postfix("a*"), std::invalid_argument);
    EXPECT_THROW(Postfix postfix("a/"), std::invalid_argument);
    EXPECT_THROW(Postfix postfix("a+("), std::invalid_argument);
    EXPECT_THROW(Postfix postfix("a+exp"), std::invalid_argument);

    EXPECT_THROW(Postfix postfix("(a+b-(c*d)"), std::invalid_argument);
}

TEST(Postfix, ObtainingSequenceOfOperands)
{
    Postfix postfix("a+b+c");

    std::vector<std::string> operands_ = postfix.GetOperands();
    size_t size_op = operands_.size();
    EXPECT_EQ(size_op, 3);

    EXPECT_EQ(operands_[0], "a");
    EXPECT_EQ(operands_[1], "b");
    EXPECT_EQ(operands_[2], "c");
}

TEST(Postfix, SimpleExpressionsCalculateNoThrow)
{
    double a = 1.09, b = 2.34, c = 3.9;
    std::vector<double> values_1 = { a, b };
    std::vector<double> values_2 = { c };

    Postfix postfix1("a+b");
    EXPECT_DOUBLE_EQ(postfix1.Calculate(values_1), a + b);

    Postfix postfix2("a-b");
    EXPECT_DOUBLE_EQ(postfix2.Calculate(values_1), a - b);

    Postfix postfix3("a*b");
    EXPECT_DOUBLE_EQ(postfix3.Calculate(values_1), a * b);

    Postfix postfix4("a/b");
    EXPECT_DOUBLE_EQ(postfix4.Calculate(values_1), a / b);

    Postfix postfix5("exp(c)");
    EXPECT_DOUBLE_EQ(postfix5.Calculate(values_2), std::exp(c));

    Postfix postfix6("-d");
    EXPECT_DOUBLE_EQ(postfix6.Calculate(values_2), -c);
}

TEST(Postfix, SimpleExpressionsWithUnaryMinusCalculateNoThrow)
{
    double a = 1.09, b = 2.34, c = 3.9;
    std::vector<double> values_1 = { a, b };
    std::vector<double> values_2 = { c };

    Postfix postfix1("-(a+b)");
    EXPECT_DOUBLE_EQ(postfix1.Calculate(values_1), -(a + b));

    Postfix postfix2("-(a-b)");
    EXPECT_DOUBLE_EQ(postfix2.Calculate(values_1), -(a - b));

    Postfix postfix3("-(a*b)");
    EXPECT_DOUBLE_EQ(postfix3.Calculate(values_1), -(a * b));

    Postfix postfix4("-(a/b)");
    EXPECT_DOUBLE_EQ(postfix4.Calculate(values_1), -(a / b));

    Postfix postfix5("-exp(c)");
    EXPECT_DOUBLE_EQ(postfix5.Calculate(values_2), -std::exp(c));

    Postfix postfix6("-(-d)");
    EXPECT_DOUBLE_EQ(postfix6.Calculate(values_2), -(-c));
}

TEST(Postfix, ComplexExpressionsWithUnaryMinusWithNumbersWithMultiLetterVariablesCalculateNoThrow)
{
    double a = 1.09, bG_b = 2.34, cfh_cKL = 3.9;
    std::vector<double> values_1 = { a, bG_b, cfh_cKL };

    Postfix postfix1("-(a+bG/(3+cfh))*5.6");
    EXPECT_DOUBLE_EQ(postfix1.Calculate(values_1), -(a + bG_b / (3 + cfh_cKL)) * 5.6);

    Postfix postfix2("-(a-b*(7.4-exp(cKL)))");
    EXPECT_DOUBLE_EQ(postfix2.Calculate(values_1), -(a - bG_b * (7.4 - std::exp(cfh_cKL))));
}

TEST(Postfix, ExpressionsCalculateAnyThrow)
{
    double a = 1.09;
    std::vector<double> values_1 = { a };

    Postfix postfix1("a+b");
    //Incorrect size of the vector of variable values (operands). Mismatch between the number of operand values and the number of operands.
    EXPECT_THROW(postfix1.Calculate(values_1), std::invalid_argument);
}

//Ввод операндов (переменных) с консоли:

TEST(Postfix, ExpressionsCalculateFromTheConsole)
{
    Postfix postfix1("(a+b*c)/(-(exp(d)-f))");
    std::cout << postfix1.Calculate() << "\n";
}