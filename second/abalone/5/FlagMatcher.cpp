#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <cstdlib>

using namespace std;

class FlagMatcher {
public:
	FlagMatcher() {}

	bool matchCheck(const string &filename) {
		readInCode(filename);

		stack<char> flagStack;
		bool inComment = false;
		for (size_t i=0; i<code.size(); i++) {
			char c = code[i];
			if (c == '/') {
				if (i+1<code.size() && code[++i]=='*')
					inComment = true;
				continue;
			} else if (c == '*') {
				if (i+1<code.size() && code[++i]=='/')
					inComment = false;
				continue;
			}

			if (!inComment) {
				switch (c) {
					case '[': 
					case '(':
					case '{':
						flagStack.push(c); 
						break;
					case ']':
						if (getTop(flagStack, i) != '[')
							error(i);
						break;
					case ')':
						if (getTop(flagStack, i) != '(')
							error(i);
						break;
					case '}':
						if (getTop(flagStack, i) != '{')
							error(i);
						break;
				}
			}

		}
		if (inComment)
			error(code.size(), "/* */");
		return true;
	}

private:
	void error(size_t pos, string msg = "") {
		if (pos < code.size()) {
			cout << "NO MATCH FOR " << code[pos] << ". \nError codes: " << endl;
			size_t start = (pos >= 40 ? pos-40 : 0);
			cout << code.substr(start, 41) << endl;
		} else
			cout << msg << " DOES NOT MATCH!!!! " << endl;
		exit(1);
	}

	char getTop(stack<char> &flagStack, size_t pos) {
		if (flagStack.empty()) 
			error(pos);	
		char c = flagStack.top();
		flagStack.pop();
		return c;
	}

	void readInCode(const string &filename) {
		ifstream input(filename.c_str());
		string line;
		code = "";
		while (getline(input, line)) {
			code += line + "\n";
		}
		input.close();
	}

	string code;
};

int main(int argc, char *argv[]) {
	if (argc != 2) {
		cout << "Usage: " << argv[0] << " filename" << endl;
		exit(0);
	}

	FlagMatcher matcher;
	if (matcher.matchCheck(argv[1]))
		cout << "Correct! Congratulations" << endl;

	return 0;
}
