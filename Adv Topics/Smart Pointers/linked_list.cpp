#include <iostream>
#include <memory>
using namespace std;

struct Node
{
	int data;
	unique_ptr<Node> next;
	~Node() {
		cout << "Data: " << this->data << " destroyed\n";
	}
};

struct List
{
	unique_ptr<Node> head;
	~List() {
		// destroy list nodes sequentially in a loop, the default destructor
		// would have invoked its `next`'s destructor recursively, which would
		// cause stack overflow for sufficiently large lists.
		while(head)
			head = move(head->next);
	}
	void push(int data) {
		head = unique_ptr<Node>(new Node{data, move(head)});
	}
	void print() {
		Node* curr = head.get();
		while(curr) {
			cout << curr->data << " ";
			curr = curr->next.get();
		}
		cout << "\n";
	}
	void reverse() { 
		unique_ptr<Node> prev = nullptr;
		unique_ptr<Node> curr = move(head);

		while(curr) {
			head = move(curr->next);
			curr->next = move(prev);
			prev = move(curr);
			curr = move(head);
		}
		head = move(prev);
	}
	friend ostream& operator<<(ostream& os, const List& list);
};

ostream& operator<<(ostream& os, const List& list) {
	Node* curr = list.head.get();
	while(curr) {
		os << curr->data << " ";
		curr = curr->next.get();
	}
	os << "\n";
	return os;
}

int main() 
{
	{
		List wall;
		for (int i = 0; i < 10; i++) {
			wall.push(i);
		}
		cout << wall;
		wall.reverse();
		cout << wall;
	}
	return 0;
}