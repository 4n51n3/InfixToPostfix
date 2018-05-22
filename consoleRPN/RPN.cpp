#include "RPN.h"
#include <string>
#include <vector>

using namespace std;

bool RPN::isDelim(const char c)
{
	return c == ' ';
}

bool RPN::isOperator(const char c)
{
	return strIsOperator.find(c) != string::npos;
}

bool RPN::isOperand(const char c)
{
	return isdigit(c) || c == '.';
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
	for (string a : output) {
		if (!isOperator(a[0]) && a[0] != ' ') {
			operandStack.push_back(stod(a, nullptr));
		}
		else if(a[0] != ' ') {
			d2 = pop(operandStack);
			d1 = pop(operandStack);
			
			switch (a[0])
			{
			case '+':
				operandStack.push_back(d1+d2);
				break;
			case '-':
				operandStack.push_back(d1-d2);
				break;
			case '*':
				operandStack.push_back(d1*d2);
				break;
			case '/':
				operandStack.push_back(d1/d2);
				break;
			default:
				throw new exception("Count() error");
			}
		}
	}
	return pop(operandStack);
}

RPN::RPN(const char * input)
{
	this->RPN::RPN(string(input));
}

RPN::RPN(const std::string input)
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
			while ((val = ops.back()) != '(')
			{
				ops.pop_back();
				string push;
				push.push_back(val);
				output.push_back(push); output.push_back(strSpace);
			}
			ops.pop_back();
		}
		else if (isOperator(input[i])) {
			while (ops.size() > 0 && getPriority(ops.back()) >= getPriority(input[i])) {
				string psh;
				psh.push_back(ops.back()); ops.pop_back();
				output.push_back(psh); output.push_back(strSpace);
				
			}
			ops.push_back(input[i]);
		}
		else {
			throw new exception("Unknown char in input string!");
		}

	}
	if (ops.size() > 0) {
		for (int i = ops.size() - 1; i >= 0; i--) {
			char op = ops[i];
			string push;
			push.push_back(op);
			output.push_back(push); output.push_back(strSpace);
		}
	}
	for (string a : output) {
		postfix.append(a);
	}
}