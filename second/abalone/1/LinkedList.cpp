#include <iostream>
#include <cassert>
#include <set>
#include <stack>

using namespace std;

struct Node {
	int value;
	Node *next;
	
	Node(int val=0): value(val) {
		next = NULL;
	}
};

class LinkedList {
public:
	LinkedList() {
		head = NULL;
	}

	~LinkedList() {
		while (head != NULL) {
			Node *ptr = head->next;
			delete head;
			head = ptr;
		}
	}

	void reverse() {
		if (head == NULL || head->next == NULL)
			return;
		Node *pre = head;
		Node *cur = head->next;
		do {
			Node *succ = cur->next;
			cur->next = pre;
			pre = cur;
			cur = succ;
		} while (cur != NULL);
		head->next = NULL; // important
		head = pre;
	}

	int getRightLeastK(size_t k) {
		size_t length = getLength();
		assert(length > k);
		size_t index = length - k;
		Node *ptr = head;
		for (size_t i=1; i<index; i++)
			ptr = ptr->next;
		return ptr->value;
	}

	Node* getMid() {
		size_t length = getLength();
		if (length == 0)
			return NULL;
		size_t mid = length / 2;
		Node *ptr = head;
		for (size_t i=0; i<mid; i++)
			ptr = ptr->next;
		return ptr;
	}

	void reversedPrint() {
		cout << "Reversed Print: ";
		reversedPrint(head);
		cout << endl;
	}

	bool hasCircle() {
		Node *ptr = head;
		set<Node*> collection;
		while (ptr != NULL) {
			if (!collection.insert(ptr).second)
				return true;
			ptr = ptr->next;
		}
		return false;
	}
	
	Node* circularEntry() {
		Node *ptr = head;
		set<Node*> collection;
		while (ptr != NULL) {
			if (!collection.insert(ptr).second)
				return ptr;
			ptr = ptr->next;
		}
		return NULL;
	}

	bool doesCross(const LinkedList &list) {
		if (list.head == NULL || this->head == NULL)
			return false;
		Node *pre1 = head;
		Node *cur1 = head->next;
		Node *pre2 = list.head;
		Node *cur2 = pre2->next;
		while (cur1 != NULL) {
			pre1 = cur1;
			cur1 = cur1->next;
		}
		while (cur2 != NULL) {
			pre2 = cur2;
			cur2 = cur2->next;
		}
		return pre1 == pre2 ? true : false;
	}

	Node* crossedNode(const LinkedList &list) {
		stack<Node*> stack1;
		stack<Node*> stack2;
		Node *ptr1 = head;
		Node *ptr2 = list.head;
		while (ptr1 != NULL) {
			stack1.push(ptr1);
			ptr1 = ptr1->next;
		}
		while (ptr2 != NULL) {
			stack2.push(ptr2);
			ptr2 = ptr2->next;
		}
		
		Node *firstCrossed = NULL;
		while (!stack1.empty() && !stack2.empty()) {
			if (stack1.top() != stack2.top())
				break;
			firstCrossed = stack1.top();
			stack1.pop();
			stack2.pop();
		}
		return firstCrossed;
	}

	bool deleteNode(size_t index) {
		size_t i = 0;
		Node *cur = head;
		Node *pre = head;
		while (cur != NULL) {
			if (i == index)
				break;
			pre = cur;
			cur = cur->next;
			i++;
		}
		if (cur == NULL)
			return false;
		else if (cur == head) { // delete the list head
			head = cur->next;
			delete cur;
		} else {
			pre->next = cur->next;
			delete cur;
		}
		return true;
	}

	void init() {
		int num, value;
		cin >> num;
		for (int i=0; i<num; i++) {
			cin >> value;
			Node *ptr = new Node(value);
			ptr->next = head;
			head = ptr;
		}
	}
	
	void print() {
		cout << "List: ";
		Node *ptr = head;
		while (ptr != NULL) {
			cout << ptr->value << " ";
			ptr = ptr->next;
		}
		cout << endl;
	}

private:
	void reversedPrint(Node *ptr) {
		if (ptr == NULL)
			return;
		else {
			reversedPrint(ptr->next);
			cout << ptr->value << " ";
		}
	}

	size_t getLength() {
		size_t length = 0;
		Node *ptr = head;
		while (ptr != NULL) {
			length++;
			ptr = ptr->next;
		}
		return length;
	}

	Node *head;
};

int main() {
	LinkedList list;
	list.init();

	cout << "Before reversing ..." << endl;
	list.print();
	cout << "After reversing ... " << endl;
	list.reverse();
	list.print();

	cout << endl;
	list.print();
	int k;
	cin >> k;
	cout << "k = " << k << ", itemK = " << list.getRightLeastK(k) << endl;
	cin >> k;
	cout << "k = " << k << ", itemK = " << list.getRightLeastK(k) << endl;

	cout << endl;
	list.print();
	cout << "The middle item is " << list.getMid()->value << endl;

	cout << endl;
	list.reversedPrint();

	cout << endl;
	cout << "Dose the list has a circle? " << 
		(list.hasCircle()? "Yes" : "No") << endl;
	cout << "The circular entry: " << 
		(list.circularEntry() ? "Secret" : "NULL") << endl;

	LinkedList another;
	another.init();
	cout << "\n Does these two lists cross with each other? " << 
		(list.doesCross(another) ? "Yes" : "No") << endl;
	cout << " The first corssed node is " << (list.crossedNode(another) ? "Secret" : "NULL") << endl;

	cout << "\n Delete nodes in list " << endl;
	cout << "The original list: " << endl;
	list.print();
	int num;
	cin >> num;
	for (int i=0; i<num; i++) {
		int id;
		cin >> id;
		bool flag = list.deleteNode(id);
		if (flag) {
			cout << "\n Delete No." << id << " node: " << endl;
			list.print();
		} else {
			cout << "\n Fail to delete No." << id << endl;
		}
	}

	return 0;
}

