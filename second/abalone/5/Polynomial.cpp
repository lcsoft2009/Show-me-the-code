#include <iostream>

using namespace std;

struct Node {
	int coe;
	int exp;
	Node *next;

	Node (int coe=0, int exp=0) {
		this->coe = coe;
		this->exp = exp;
		next = NULL;
	}
};

class Polynomial {
public:
	Polynomial() {
		head = new Node();
		tail = head;
	}
	
	~Polynomial() {
		while (head != NULL) {
			Node *ptr = head->next;
			delete head;
			head = ptr;
		}
	}

	void init() {
		int num, coe, exp;
		cin >> num;
		for (int i=0; i<num; i++) {
			cin >> coe >> exp;
			append(new Node(coe, exp));
		}
	}

	void print() {
		Node *ptr = head->next;
		while (ptr) {
			cout << "(coe=" << ptr->coe << ",exp=" << ptr->exp << ") ";
			ptr = ptr->next;
		}
		cout << endl;
	}

	friend void add(const Polynomial &left, const Polynomial &right,
			Polynomial &result);
	friend void multiply(const Polynomial &left, const Polynomial &right,
			Polynomial &result);

private:
	void append(Node *ptr) {
		tail->next = ptr;
		tail = ptr;
	}

	void add(const Polynomial &right) {
		Node *leftPtr = head->next;
		Node *pre = head;
		Node *rightPtr = right.head->next;
		while (leftPtr && rightPtr) {
			if (leftPtr->exp > rightPtr->exp) {
				pre = leftPtr;
				leftPtr = leftPtr->next;
			} else if (leftPtr->exp < rightPtr->exp) {
				Node *ptr = new Node(rightPtr->coe, rightPtr->exp);
				ptr->next = leftPtr;
				pre->next = ptr;
				rightPtr = rightPtr->next;
			} else {
				leftPtr->coe += rightPtr->coe;
				if (leftPtr->coe == 0) {
					pre->next = leftPtr->next;
					if (tail == leftPtr)
						tail = pre; // important
					delete leftPtr;
					leftPtr = pre->next;
				} else {
					pre = leftPtr;
					leftPtr = leftPtr->next;
				}
				rightPtr = rightPtr->next;
			}
		}
		while (rightPtr) {
			append(new Node(rightPtr->coe, rightPtr->exp));
			rightPtr = rightPtr->next;
		}
	}

	Node *head;
	Node *tail;
};

void multiply(const Polynomial &left, const Polynomial &right,
		Polynomial &result) {
	for (Node *leftPtr = left.head->next; leftPtr; leftPtr = leftPtr->next) {
		Polynomial temp;
		for (Node *rightPtr = right.head->next; rightPtr; rightPtr = rightPtr->next) {
			temp.append(new Node(leftPtr->coe*rightPtr->coe, leftPtr->exp+rightPtr->exp));
		}
		result.add(temp);
	}
}

void add(const Polynomial &left, const Polynomial &right,
		Polynomial &result) {
	result.add(left);
	result.add(right);
	/*Node *leftPtr = left.head->next;
	Node *rightPtr = right.head->next;
	while (leftPtr && rightPtr) {
		if (leftPtr->exp > rightPtr->exp) {
			Node *ptr = new Node(leftPtr->coe, leftPtr->exp);
			result.append(ptr);
			leftPtr = leftPtr->next;
		} else if (leftPtr->exp < rightPtr->exp) {
			Node *ptr = new Node(rightPtr->coe, rightPtr->exp);
			result.append(ptr);
			rightPtr = rightPtr->next;
		} else {
			if (leftPtr->coe + rightPtr->coe != 0) {
				Node *ptr = new Node(leftPtr->coe + rightPtr->coe, leftPtr->exp);
				result.append(ptr);
			}
			leftPtr = leftPtr->next;
			rightPtr = rightPtr->next;
		}
	}
	Node *ptr = (leftPtr ? leftPtr : rightPtr);
	while (ptr) {
		result.append(new Node(ptr->coe, ptr->exp));
		ptr = ptr->next;
	}*/
}

int main() {
	Polynomial poly1, poly2;
	poly1.init();
	poly2.init();

	Polynomial result1, result2;
	add(poly1, poly2, result1);
	multiply(poly1, poly2, result2);
	cout << "The left polynomial: ";
	poly1.print();
	cout << "The right polynomial: ";
	poly2.print();
	cout << "left + right = ";
	result1.print();
	cout << "left * right = ";
	result2.print();

	return 0;
}
