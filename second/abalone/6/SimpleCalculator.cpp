#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <cctype>
#include <stack>

using namespace std;

class SimpleCalculator {
public:
	SimpleCalculator() {}

	double calculate(const string &oriExp) {
		this->expression = oriExp;
		string postfixExp = in2post(oriExp);
		stack<double> operands;
		double left, right;
		for (size_t i=0; i<postfixExp.size(); i++) {
			char c = postfixExp[i];
			if (isdigit(c)) {
				operands.push(c - '0');
				continue;
			}
			right = operands.top();
			operands.pop();
			left = operands.top();
			operands.pop();
			switch (c) {
				case '^':
					operands.push(pow(left, right));
					break;
				case '*':
					operands.push(left * right);
					break;
				case '/':
					operands.push(left / right);
					break;
				case '+':
					operands.push(left + right);
					break;
				case '-':
					operands.push(left - right);
			}
		}
		cout << "************************************\n";
		cout << "Original expression: " << oriExp << endl;
		cout << "Postfix expression: " << postfixExp << endl;
		cout << "Infix expression: " << post2in(postfixExp) << endl;
		cout << "Answer: " << operands.top() << endl;
		return operands.top();
	}

private:

	string getOperand(stack<string> &operands) {
		if (operands.empty()) {
			cout << "************************************\n";
			cout << "Illegal expression: " << expression << endl;
			exit(1);
		}
		string str = operands.top();
		operands.pop();
		return str;
	}

	void toPostfix(stack<string> &operands, stack<char> &operators) {
		string op = getOperand(operands) + getOperand(operands) + operators.top();
		operators.pop();
		operands.push(op);
	}

	string in2post(const string &exp) {
		stack<string> operands;
		stack<char> operators;
		operators.push('#');
		for (size_t i=0; i<exp.size(); i++) {
			char c = exp[i];
			if (isdigit(c)) {
				operands.push(string(1, c));
				continue;
			}
			char top = operators.top();
			switch (c) {
				case '^':
					if (top == '^') 
						toPostfix(operands, operators);	
					operators.push(c);
					break;
				case '*':
				case '/':
					while (top == '^' || top == '*' || top == '/') {
						toPostfix(operands, operators);
						top = operators.top();
					}
					operators.push(c);
					break;
				case '+':
				case '-':
					while (top != '#') {
						toPostfix(operands, operators);
						top = operators.top();
					}
					operators.push(c);
			}
		}
		while (operators.top() != '#')
			toPostfix(operands, operators);

		return operands.top();
	}

	string post2in(const string &exp) {
		stack<string> expStack;
		string left, right;
		for (size_t i=0; i<exp.size(); i++) {
			char c = exp[i];
			if (isdigit(c)) {
				expStack.push(string(1, c));
				continue;
			}
			right = expStack.top();
			expStack.pop();
			left = expStack.top();
			expStack.pop();
			expStack.push("(" + left + c + right + ")");
		}
		return expStack.top();
	}

	string expression;
};

int main() {
	SimpleCalculator calculator;
	string exp;
	while (getline(cin, exp))
		calculator.calculate(exp);

	return 0;
}
