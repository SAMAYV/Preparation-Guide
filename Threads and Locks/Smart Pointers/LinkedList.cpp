#include <iostream>
#include <memory>
struct Node
{
	int data;
	std::unique_ptr<Node> next;

	~Node() {
		std::cout << "Data: " << this->data << " destroyed\n";
	}
};

struct List
{
	std::unique_ptr<Node> head;

	~List()
	{
		// destroy list nodes sequentially in a loop, the default destructor
		// would have invoked its `next`'s destructor recursively, which would
		// cause stack overflow for sufficiently large lists.
		while (head)
			head = std::move(head->next);
	}

	void push(int data)
	{
		head = std::unique_ptr<Node>(new Node{data, std::move(head)});
	}

	void print() {
		Node* curr = head.get();
		while (curr) {
			std::cout << curr->data << " ";
			curr = curr->next.get();
		}
		std::cout << "\n";
	}

	void reverse() { // Nice task.
		std::unique_ptr<Node>prev = nullptr;
		std::unique_ptr<Node>curr = std::move(head);

		while (curr) {
			head = std::move(curr->next);
			curr->next = std::move(prev);
			prev = std::move(curr);
			curr = std::move(head);
		}

		head = std::move(prev);
	}
	friend std::ostream& operator<<(std::ostream& os, const List &list);
};

std::ostream& operator<< (std::ostream& os, const List &list) {
	Node* curr = list.head.get();
	while (curr) {
		os << curr->data << " ";
		curr = curr->next.get();
	}
	os << "\n";
	return os;
}

int main() {
	{
		List wall;
		for (int i = 0; i < 10; i++) {
			wall.push(i);
		}
		std::cout << wall;

		wall.reverse();

		std::cout << wall;
	}
}