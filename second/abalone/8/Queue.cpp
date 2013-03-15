#include <iostream>
#include <stack>
#include <cassert>

using namespace std;

class Queue {
public:
	Queue() {}
	int front();
	void pop();
	void push(const int item);
	inline size_t size();
	inline bool empty();

private:
	stack<int> in;
	stack<int> out;
};

int Queue::front() {
	assert(!empty());
	if (!out.empty())
		return out.top();
	else {
		while (!in.empty()) {
			out.push(in.top());
			in.pop();
		}
		return out.top();
	}
}

void Queue::pop() {
	assert(!empty());
	if (!out.empty())
		out.pop();
	else {
		while (!in.empty()) {
			out.push(in.top());
			in.pop();
		}
		out.pop();
	}
}

void Queue::push(const int item) {
	in.push(item);
}

size_t Queue::size() {
	return in.size() + out.size();
}

bool Queue::empty() {
	return in.empty() && out.empty();
}

int main() {
	Queue queue;
	assert(queue.empty());
	assert(queue.size() == 0);

	for (int i=1; i<=5; i++)
		queue.push(i);
	assert(!queue.empty());
	assert(queue.size() == 5);
	assert(queue.front() == 1);
	
	queue.pop();
	assert(queue.size() == 4);
	assert(queue.front() == 2);

	queue.push(1);
	assert(queue.size() == 5);

	for (int i=0; i<5; i++)
		queue.pop();
	assert(queue.empty());

	cout << "Pass all tests" << endl;

	return 0;
}
