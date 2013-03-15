#include <iostream>
#include <cassert>

using namespace std;

struct Node {
	int value;
	Node *next;

	Node(int val=0): value(val) { }
};

Node *head = NULL;
Node *tail = NULL;

void initCircularList(int n) {
	assert(n > 0);
	Node *ptr = NULL;

	for (int i=n-1; i>=0; i--) {
		ptr = new Node(i);
		ptr->next = head;
		if (head == NULL)
			tail = ptr;
		head = ptr;
	}
	tail->next = head;
}

// Simulate the procedure
void simulate(int m, int n) {
	assert(m > 0);
	assert(n > 0);
	
	Node *cur = head;
	Node *pre = tail;
	while (cur->next != cur) {
		for (int i=1; i<m; i++) {
			pre = cur;
			cur = cur->next;
		}
		pre->next = cur->next;
		delete cur;
		cur = pre->next;
	}
	cout << "Simulation: the last one is No." << cur->value << endl;
	delete cur;
}

// in iterative way
// x' = (x + m) % i
void calculate(int m, int n) {
	int x = 0;
	for (int i=2; i<=n; i++)
		x = (x + m) % i;
	cout << "NoSimulation: the last one is No." << x << endl;
}

int main() {
	int n, m;
	cin >> n >> m;

	initCircularList(n);
	simulate(m, n);
	calculate(m, n);

	return 0;
}
