/*
Ref: https://docs.microsoft.com/en-us/cpp/cpp/smart-pointers-modern-cpp?view=msvc-170

Unique pointer -> constructor needs to be explicitly called.
Shared pointer
*/

#include <iostream>
#include <string>
#include <memory>

class Entity {
public:
	Entity() {
		std::cout << "Created Entity\n";
	}
	~Entity() {
		std::cout << "Destroyed Entity! \n";
	}

	void Print() {}
};

int main() {

	std::cout << "Unique ptr" << std::endl;
	{
		// std::unique_ptr<Entity>entity(new Entity()); // one way to declare
		std::unique_ptr<Entity>entity = std::make_unique<Entity>(); // preferred way
		entity->Print();
	}

	// Shared ptr
	// Works by the logic of reference counting -> keep a count of how many references are made to the ptr.
	std::cout << "---------\nShared ptr" << std::endl;

	std::shared_ptr<Entity>e0; // shared ptr has overhead.
	{
		std::shared_ptr<Entity>sharedEntity = std::make_shared<Entity>();
		e0 = sharedEntity;
	}
	return 0;
}