# OOPS Important Points

## Constructors
* C++ declares a Default constructor with empty body if none is declared.
* When you Declare **any** constructor, it stops doing that.
* Copy constructor is called when we use _=_, pass by value, return, create temporary object
* Default Copy constuctor, does a shallow **copy** of an object. That means that it copies all the Data members, but if we have Dynamic/Runtime memory allocated through Pointers etc., we will require our own Copy constructor

## RVO
* It is a compiler optimization that involves eliminating the temporary object created to hold a function's return value.
* So the temporary variable can always be omitted.
* It works via allocating memory for the to-be-returned object in the caller's stack frame, so no destructor of the local variable is called, neither is the copy constructor to allocate to the variable, the return value is assigned to.
* It can't happen in some cases, refer to the link https://shaharmike.com/cpp/rvo/

## Destructors
* C++ declares a Default destructor if none is declared.
* If we have Dynamic memory allocated (through pointers, etc.) we will need our own destructor.
* It is automatically called when The function/block ends(Local variable), program ends or delete operator is called
* When we use the new keyword is used, we will need to explicitly use delete operator.

## Virtual Destructor
* Let's say we have an object of child class, which is being pointed by pointer of Parent class.
* If I call delete on that pointer, then since the type of that pointer is Parent* , it will only call the Parent's Destructor (due to Early binding)
* So, to fix this we make the Destructor of parent as **virtual**, which causes Late binding and it will see the content of the pointer and call the respective Destructor.



## Inheritence call of Constructors 
* Parent class's Default constructor is automatically called in the beginning of Child's constructor. If not declared, it will give an error.
* To call parametarized constructor, we have to declare it in the _Constructor declaration_.
* Similarly, after executing the child class's Destructor, it calls Parent's Destructor.
```cpp
class Animal;
class Snak: public Animal{
    Snak(u,v): Animal(v){} 
}
```

## Constuctor/Destructor call order in multiple inheritance
* Constructor - Left to right
* Destructor - Right to left
* Remains same even if virtual inheritance
---

## Friend functions
* Defined outside the class and can access all private/protected members of the class
* Usually used when we need to operate on members of 2 classes.
* Declared inside the class via a prototype of the function prefixed with **friend** keyword. The Object instances must be one of the arguments passed.

## Friend class
* Same use as functions

Both need a function with the class object as argument and then we can use the private members.

```cpp
friend void f(Student& s); // Friend fn
friend int LinkedList::search(Student& s); // search fn of LL is friend

friend class LinkedList;  // Friend class
```

---

## Prototypes
### class prototype
```cpp 
class ClassName;
```
### function prototype
```cpp 
char FuncName(int, int);
```

---
## Inheritance
### Types
* _Single-level:_ Just 1 parent and child  
* _Multi-level:_ Linear graph
* _Heirarchal:_ Rooted tree with multiple children
* _Multiple:_ Multiple parents
* _Hybrid:_ Multiple + Heirarchal

### Access Specifiers
* Private members are never inherited, thats why Protected was made (Not sure??).
* Both Public and Protected are inherited

|                       | Public    | Protected |
|-----------------------|-----------|-----------|
| Public Inheritance    | Public    | Protected |
| Protected Inheritance | Protected | Protected |
| Private   Inheritance | Private   | Private   |


### Inheritance syntax:
```cpp
class DerivedClass: public BaseClass {};
class DerviedClass: public BaseClass1, protected BaseClass2 {};
```

### Function overriding parent fn access:
* To access base class's function, use `Base::funcName()` (can do this from anywhere, keeping in mind the Access modifiers).
* This `Base::` gives us a way to referenced each and every function (both inherited and those declared in Derived class).
* If the inherited fn has different specifier than the one declared in the Derived class, then the derived class function is used.
* If we don't use the `Base::` prefix, then only the unique functions or the ones declared in the Derived class are referenced.

---

## Virtual funtions
* Constructor cannot be virtual
* Can be overrided in Derived class, not compulsory.
* Difference between normal functions and virtual function comes in Polymorphism.
* When you refer to a Derived class by a pointer to the Base class, without virtual functions, you can only access the members of the Base class. So with virtual functions, we can access the derived class function which overrides this base class function.
* Syntax : Prefix **virtual** is added to the function declaration.
```cpp
virtual void funcName(int x, int y) {} 
```

## Pure Virtual Functions
```cpp
virtual void funcName(int x, int y) = 0; 
```
* Don't have a body and have to be compulsorily overrided. 
* Even if it is a private function, we have to override it in the Derived class.
* Becomes an Abstract class.
* If we don't override, Derived class also becomes an abstract class.

## Abstract Class
* We can't declare an instance of this class.
* But we can create a pointers of this class.


## Refering to Child class with Parent's pointer
* We refer to child's object with Parent's pointer to implement runtime polymorphism. 
* Eg. There is a switch statement, and the result will be assigned to Parent's pointer
* But with the parent's pointer you can only access, parent's members. We can access Child's functions by using virtual functions and overriding it in the child.
* To get back the Child class's object, we can 
```cpp
Parent* ptr = new Child();
Child* ch = dynamic_cast<Child*>(ptr);
```
* _NOTE:_ For doing this, atleast 1 function (eg. Destructor) of Parent class should be virtual.

---

## Multiple Inheritance function Ambiguity
* When both parent classes have same function, and we don't give a declaration of that function in the derived class, then we get an Ambiguity Error.
* If we have overrided in derived class, then normally, the implementation of the derived class is used (No ambiguity), otherwise, we need to access the Parents' func by using their resp. prefixes.
---
## Hybrid Inheritance Diamond problem
### Problem
* This arises when we inherit from 2 Parents and they have inherited from a common GrandParent.
* The members of the GP which are inherited in the Parents and which are then inherited into the Child from both the parents. This leads to ambiguity.
* The constructor/destructors of the GP is called Twice, once from each parent. Proving that indeed there are 2 instances of it.

### Solution
* One way is to specifically specify which Parent, like in Ambiguity problem. But there's a better way ie. Virtual Inheritance.
```cpp
class Animalia;
class Reptile: virtual public Animalia;
class Amphibian: virtual public Animalia;
class Snak: public Reptile, Amphibian{
    Snak(u,v): Ambhibian(u), Reptile(v){}
};
```
* Now, the GP class's Constructor will only be called once. 
* Now the copy only from the rightmost Parent will be inherited, as it's constructor is called latest.
* But using this, only the default constructor of GP is called even if the Parents are calling the Paramatrized constructor. 
* To fix that, we can directly call the GP's Paramatrized constructor directly.
```cpp
Snak(u,v): Ambhibian(u), Reptile(v), Animalia(v){}
```
* _NOTE:_ This calling GP's constructor directly can only be done in case of virtual inheritance, otherwise it'll give an error.

---

## Execution process C++

### Step 1 - Preprocessor
* Happens before the program's execution.
* All the Macros, #defines are expanded, imports Header files.

### Step 2 - Compiler
* Checks the static errors(Compile time errors) ie. syntax, semantic errors.
* Converts into object file

### Step 3 - Linker
* Links the libraries that we might have used or other object files that we might be using.

### Step 4 - Loader
* Loads the executable file generated into the main memory. And then the Program runs

---
## Polymorphism
### Compile time (early binding / static polymorphism)
* Function overloading
* Operator overloading
* Templates

### Run time (late binding / dynamic polymorphism)
* Function overriding
---
## Static Members
They are independent of any instance of the class. Can be called without creating an object. All instances have same copy of that member.
### Data members
* Initialized to 0 if no initialization is present.
* It can't be initialized inside the class, can be done outside the class
```cpp
class ClassName { static int x; }
int ClassName::x = 1;
```
* Any function can access that data member.
### Member functions
* Can only access the class's static data members, class's static member functions, and functions from outside the class. 
* Do not have access to **this** member of the class.
```cpp
static int funcName(int x);
```
---

## Operator Overloading
Compile time Polymorphism. All can be overloaded except ` . .* sizeof :: ?: ` operators
```cpp
Complex operator +(Complex &c){}
Complex operator +(int delta){}
Complex operator ++(){} // Preincrement
Complex operator ++(int){} // Postincrement(int is not Integer)

// We can also use this notation when we want to work with 2 different classes
// Declaration inside class, definition outside
friend Complex operator+(Complex&, Complex&); 
friend Complex operator-(Complex &x); // Negetion(pre)
```


## Nested classes
We can declare another class inside a class. Then create an object of that class.
















 
