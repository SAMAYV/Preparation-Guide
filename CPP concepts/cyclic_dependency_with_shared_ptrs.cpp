#include <memory>
#include <iostream>

struct B;
struct A {
  std::shared_ptr<B> b;  
  ~A() { std::cout << "~A()\n"; }
};

struct B {
  std::shared_ptr<A> a;
  ~B() { std::cout << "~B()\n"; }  
};

void useAnB() {
  auto a = std::make_shared<A>();
  auto b = std::make_shared<B>();
  a->b = b;
  b->a = a;
}

int main() {
   useAnB();
   std::cout << "Finished using A and B\n";
}

/*

Applications of weak_ptr
The following are the primary applications of the weak_ptr:

Preventing Circular References: The primary application of weak_ptr is to prevent circular references. When an object wants to reference another object without owning it, it can use weak_ptr. This ensures that no circular references are created and objects can be safely freed when they are no longer needed.
Cache Systems: weak_ptr is commonly used in cache implementations. Caches often need to temporarily store references to objects without preventing the deletion of those objects when they are no longer in use. weak_ptr provides an elegant solution for this use case.

*/