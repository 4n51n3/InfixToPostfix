#pragma once
#include <string>
#include <vector>


class RPN
{
	std::vector<char> ops;
	std::vector<std::string> output;
	const std::string strSpace = " ";
	const std::string strIsOperator = "+-/*";
	const std::string strGetPriority = "()+-*/";


	bool isDelim(const char c);
	bool isOperator(const char c);
	bool isOperand(const char c);
	int getPriority(const char c);
	std::string pop(std::vector<std::string> &operandsStack);
	double pop(std::vector<double> &operandsStack);
public:
	std::string postfix;


	double Count();
	RPN(const char* input);
	RPN(const std::string input);
	//~RPN();
};

