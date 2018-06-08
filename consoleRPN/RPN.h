#pragma once
#include <string>
#include <vector>
#include <cmath>
#include <sstream>

class RPN
{
	std::vector<char> ops;
	std::vector<std::string> output;
	const std::string strSpace = " ";
	const std::string strIsBinOperator = "+-/*^L";
	const std::string strIsUnaryOperator = "-";
	const std::string strGetPriority = "()+-*/~^L";

	bool isDelim(const char c);
	bool isOperator(const char c);
	bool isOperand(const char c);
	bool isUnary(const char c);
	int parseLogarithm(std::string::const_iterator begin);
	int getPriority(const char c);
	std::string pop(std::vector<std::string> &operandsStack);
	double pop(std::vector<double> &operandsStack);
	double log(double base, double x);
public:
	std::string postfix;


	double Count();

	RPN(std::string& input);
	//~RPN();
};

