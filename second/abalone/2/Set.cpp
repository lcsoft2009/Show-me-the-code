#include <iostream>

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
	friend class Set;

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

	void add(int value) {
		Node *ptr = new Node(value);
		ptr->next = head;
		head = ptr;
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
	Node *head;
};

class Set {
public:
	Set() {}
	~Set() { freeArray(); }

	// Make sure that there are no duplicates in list1 and list2.
	void intersect(const LinkedList &list1,
			const LinkedList &list2, LinkedList &result) {
		freeArray();
		Node *ptr1 = list1.head;
		for ( ; ptr1; ptr1 = ptr1->next)
			this->add(ptr1);

		Node *ptr2 = list2.head;
		for ( ; ptr2; ptr2 = ptr2->next)
			if (conflict(ptr2))
				result.add(ptr2->value);
	}

	void unionSet(const LinkedList &list1,
			const LinkedList &list2, LinkedList &result) {
		freeArray();
		Node *ptr1 = list1.head;
		for ( ; ptr1; ptr1 = ptr1->next)
			this->add(ptr1);
		Node *ptr2 = list2.head;
		for ( ; ptr2; ptr2 = ptr2->next)
			this->add(ptr2);
		
		for (int i=0; i<size; i++)
			if (array[i].next != NULL) {
				Node *ptr = array[i].next;
				for ( ; ptr; ptr = ptr->next)
					result.add(ptr->value);
			}
	}
	
private:
	void freeArray() {
		Node *ptr = NULL;
		for (int i=0; i<size; i++) {
			if (array[i].next != NULL) {
				ptr = array[i].next;
				while (ptr != NULL) {
					array[i].next = ptr->next;
					delete ptr;
					ptr = array[i].next;
				}
			}
		}
	}

	void add(Node* ptr) {
		if (conflict(ptr))
			return;
		size_t index = hashcode(ptr->value);
		Node *cur = new Node(ptr->value);
		cur->next = array[index].next;
		array[index].next = cur;
	}

	bool conflict(Node* ptr) {
		size_t index = hashcode(ptr->value);
		Node *cur = array[index].next;
		while (cur != NULL) {
			if (cur->value == ptr->value)
				return true;
			cur = cur->next;
		}
		return false;
	}

	size_t hashcode(int key) {
		return ((key % size) + size) % size;
	}

	const static int size = 17;
	Node array[size];
};

int main() {
	Set set;
	LinkedList list1;
	LinkedList list2;
	LinkedList unionList;
	LinkedList intersectionList;

	list1.init();
	list2.init();
	
	cout << "In list1: " << endl;
	list1.print();
	cout << "In list2: " << endl;
	list2.print();
	set.intersect(list1, list2, intersectionList);
	cout << "The intersection set: " << endl;
	intersectionList.print();
	set.unionSet(list1, list2, unionList);
	cout << "The union set: " << endl;
	unionList.print();

	return 0;
}
