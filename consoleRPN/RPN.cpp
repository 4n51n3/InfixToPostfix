#include "RPN.h"
#include <string>
#include <vector>
#include <cmath>
using namespace std;

bool RPN::isDelim(const char c)
{
	return c == ' ';
}

bool RPN::isOperator(const char c)
{
	return strIsBinOperator.find(c) != string::npos;
}

bool RPN::isOperand(const char c)
{
	return isdigit(c) || c == '.';
}

bool RPN::isUnary(const char c)
{
	return strIsUnaryOperator.find(c) != string::npos;
}

int RPN::getPriority(const char c)
{
	return strGetPriority.find(c) / 2;
}

std::string RPN::pop(std::vector<std::string>& operandsStack)
{
	string str = operandsStack.back();
	operandsStack.pop_back();
	return str;
}

double RPN::pop(std::vector<double>& operandsStack)
{
	double str = operandsStack.back();
	operandsStack.pop_back();
	return str;
}

double RPN::Count()
{
	double d1, d2;
	vector<double> operandStack;
	for (string& a : output) {
		if (a[0] == ' ')
			continue;
		if (!isOperator(a[0]) && a[0] != '~') {
			operandStack.push_back(stod(a, nullptr));
		}
		else{
			#pragma region UnaryOperations
			if (a[0] == '~') {
				d1 = pop(operandStack);
				operandStack.push_back(-d1);
				continue;
			}
			#pragma endregion

			#pragma region BinaryOperations
			d2 = pop(operandStack);
			d1 = pop(operandStack);

			switch (a[0])
			{
			case '+':
				operandStack.push_back(d1 + d2);
				break;
			case '-':
				operandStack.push_back(d1 - d2);
				break;
			case '*':
				operandStack.push_back(d1*d2);
				break;
			case '/':
				operandStack.push_back(d1 / d2);
				break;
			case '^':
				operandStack.push_back(pow(d1, d2));
				break;
			}
			#pragma endregion
		}
	}
	return pop(operandStack);
}

RPN::RPN(const char * input)
{
	this->RPN::RPN(string(input));
}

RPN::RPN(const std::string& input)
{
	for (int i = 0; i < input.length(); i++) {
		if (isDelim(input[i]))
			continue;
		int tmp = i;
		if (isOperand(input[i])) {
		#pragma region ParseLongOperand
			while (isOperand(input[i]))
				i++;
			if ((tmp = i - tmp) > 0) {

				std::string sub = input.substr(i - tmp, tmp);
				output.push_back(sub);
				output.push_back(strSpace);
				i--;
			}
		#pragma endregion
		}else if (input[i] == '(') {
			ops.push_back(input[i]);
		}
		else if (input[i] == ')') {
			char val; 
			string push;
			while ((val = ops.back()) != '(')
			{
				ops.pop_back();
				
				push.push_back(val);
				output.push_back(push); output.push_back(strSpace);
			}
			ops.pop_back();
		}
		else if (isOperator(input[i])) {
			#pragma region UnaryParse
			if (isUnary(input[i])) {
				// If an operator is the first thing in your expression, 
				// or comes after another operator, or comes after a left 
				// parenthesis, then it's an unary operator.

				// necessary condition
				if (i == 0 || isOperator(input[i - 1]) || input[i - 1] == '(') {
					if (input[i] == '-')
					{
						ops.push_back('~');
						continue;
					}
				}
			}
			#pragma endregion
			
			#pragma region BinaryParse
			string push;
			while (ops.size() > 0 && getPriority(ops.back()) >= getPriority(input[i])) {
				push.push_back(ops.back()); ops.pop_back();
				output.push_back(push); output.push_back(strSpace);
				push.clear();
			}
			ops.push_back(input[i]);
			#pragma endregion
		}
		else {
			throw new exception("Unknown char in input string!");
		}

	}
	if (ops.size() > 0) {
		string push;
		for (int i = ops.size() - 1; i >= 0; i--) {
			char op = ops[i];
			push.push_back(op);
			output.push_back(push); output.push_back(strSpace);
			push.clear();
		}
	}
	for (string& a : output) {
		postfix.append(a);
	}
}