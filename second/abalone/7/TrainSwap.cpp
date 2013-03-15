#include <iostream>
#include <stack>

using namespace std;

bool check(int *seq, int length) {
	stack<int> swap;
	int from = 1;
	for (int i=0; i<length; i++) {
		while (from < seq[i])
			swap.push(from++);
		if (from == seq[i])
			from++;
		else if (from > seq[i]) {
			if (!swap.empty() && swap.top() == seq[i])
				swap.pop();
			else
				return false;
		}
	}
	return true;
}

int main() {
	int length;
	int *seq;
	while (cin >> length) {
		seq = new int[length];
		for (int i=0; i<length; i++)
			cin >> seq[i];
		cout << (check(seq, length) ? "Yes" : "No") << endl;
		delete []seq;
	}

	return 0;
}
