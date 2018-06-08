#include "RPN.h"
#include <iostream>

using namespace std;
int main(int argc, char** argv) {
	// output.push_back(strSpace); - dont need it
	//argument as input. Don't forget.
	string str;
	RPN* tmp = nullptr;
	while (true)
	{
		cout << "Enter infix expression: ";
		cin >> str;
		while (cin.get() != '\n') { continue; }
		
		try {
			tmp = new RPN(str);
			cout << "Rez: " << tmp->Count() << endl << "Postfix form: " << tmp->postfix << endl << endl;
		}
		catch(...){
			cout << "Error" << endl;
		}
		if(!tmp)
			delete tmp;
	}
}