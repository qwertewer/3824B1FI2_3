#pragma once
#include <string>
#include <iostream>
#include "TStack.h"

class TPostfix {
private:
	std::string infix;
	std::string postfix;
	std::vector<std::string> postfix_lexems;
	std::vector<std::string> lexems;
	std::vector<std::pair<std::string, double>> operands;
	const std::vector<std::pair<char, int>> priorities; // +, -, *, /; ~ is equal to  -; ^ is equal to cos(*) 
	void Parse();
	void ToPostfix();
public:
	TPostfix(const std::string& src);
	std::string GetInfix() const;
	std::string GetPostfix() const;
	std::vector<std::string> GetOperands()const;
	double Calculate(const std::vector<std::pair<std::string, double>>& values);
	double Calculate();
};